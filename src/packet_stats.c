/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   packet_stats.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 21:20:41 by svoort        #+#    #+#                 */
/*   Updated: 2021/10/03 10:55:53 by chimpansiet   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_stats      g_stats;

static suseconds_t	get_time(void)
{
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL) == -1)
	{
		warn("failed getting time of day");
		return (0);
	}
	return (curr_time.tv_sec * 1000000 + curr_time.tv_usec);
}

void				set_stats_timer(void)
{
	g_stats.start_time = get_time();
}

void				print_stats(uint packets_sent, const char *dest_addr)
{
	printf("\n--- %s ping statistics ---\n", dest_addr);
	printf("%u packets transmitted, ", packets_sent);
	printf("%u received, ", g_stats.packets_recvd);

	if (g_stats.nb_errors)
		printf("+%u errors, ", g_stats.nb_errors);

	float loss = 1.0f - g_stats.packets_recvd / (float)packets_sent;
	printf("%d%% packet loss, ", (int)(loss * 100.0f));

	suseconds_t timediff = get_time() - g_stats.start_time;
	printf("time %ld.%03ldms\n", timediff / 1000l, timediff % 1000l);

	if (g_stats.packets_recvd > 0)
	{
		suseconds_t	mdev;
		mdev = g_stats.rtt_total / g_stats.packets_recvd;
		g_stats.rtt_sq_total /= g_stats.packets_recvd;
		mdev = sqrtl(g_stats.rtt_sq_total - mdev * mdev);

		printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n",
			g_stats.rtt_min / 1000.0f,
			g_stats.rtt_total / (float) g_stats.packets_recvd / 1000.0f,
			g_stats.rtt_max / 1000.0f,
			mdev / 1000.0f);
	}
}

static const char		*packet_format = \
"\e[36m IP HEADER\n" \
"\e[37m*****************************************************************\n" \
"\e[36m| IPv  %x | IHL %x |    TOS %hhx     |          Total Length    %hx   |\n" \
"\e[37m*****************************************************************\n" \
"\e[36m|         Identification    %04hx      |   Fragment Offset  %hx    |\n" \
"\e[37m*****************************************************************\n" \
"\e[36m|   TTL   %hhx    |   Protocol %hhx  |       Header Checksum %04hx    |\n" \
"\e[37m*****************************************************************\n" \
"\e[36m|                     Source Address    %08x                |\n" \
"\e[37m*****************************************************************\n" \
"\e[36m|                  Destination Address  %08x                |\n" \
"\e[37m*****************************************************************\n" \
"\e[36m ICMP HEADER\n" \
"\e[37m*****************************************************************\n" \
"\e[36m|    Type %hhx     |    Code %hhx     |        Checksum %04hx          |\n" \
"\e[37m*****************************************************************\n" \
"\e[36m|           Identifier %x       |        Sequence Number %x      |\n" \
"\e[37m*****************************************************************\e[0m\n";

#ifdef __linux__

void	print_ip_icmp_packet(void *packet)
{
	struct iphdr *ip = packet;
	struct icmphdr *icmp = packet + IP_HDR_SIZE;

	printf(packet_format, ip->version, ip->ihl, ip->tos, ntohs(ip->tot_len), \
		ntohs(ip->id), ntohs(ip->frag_off), ip->ttl, ip->protocol, ip->check, \
		ip->saddr, ip->daddr, icmp->type, icmp->code, \
		icmp->checksum, ntohs(icmp->un.echo.id), ntohs(icmp->un.echo.sequence));
}

#elif __APPLE__

void	print_ip_icmp_packet(void *packet)
{
	struct ip *ip = packet;
	struct icmp *icmp = packet + IP_HDR_SIZE;

	printf(packet_format, ip->ip_v, ip->ip_hl, ip->ip_tos, ip->ip_len, \
		ntohs(ip->ip_id), ip->ip_off, ip->ip_ttl, ip->ip_p, ip->ip_sum, \
		ip->ip_src.s_addr, ip->ip_dst.s_addr, icmp->icmp_type, icmp->icmp_code, \
		icmp->icmp_cksum, ntohs(icmp->icmp_id), ntohs(icmp->icmp_seq));
}

#endif

static char			*net_ntoa(struct in_addr in)
{
	static char		buffer[18];
	unsigned char	*bytes = (unsigned char *) &in;

	snprintf(buffer, sizeof(buffer), "%d.%d.%d.%d", \
		bytes[0], bytes[1], bytes[2], bytes[3]);

	return (buffer);
}

static suseconds_t	get_rtt(struct timeval *send_time)
{
	suseconds_t		curr_time = get_time();

	return (curr_time - send_time->tv_sec * 1000000 - send_time->tv_usec);
}

# define RTT_MIN(old, sample)		(old < sample ? old : sample)
# define RTT_MAX(old, sample)		(old > sample ? old : sample)

static void			update_rtt_stats(suseconds_t rtt, uint16_t seq)
{
	// if first packet init all
	if (seq == 1)
	{
		g_stats.rtt_min = rtt;
		g_stats.rtt_max = rtt;
		g_stats.rtt_total = rtt;
		g_stats.rtt_sq_total += rtt * rtt;
	}
	else
	{
		g_stats.rtt_min = RTT_MIN(g_stats.rtt_min, rtt);
		g_stats.rtt_max = RTT_MAX(g_stats.rtt_max, rtt);
		g_stats.rtt_total += rtt;
		g_stats.rtt_sq_total += rtt * rtt;
	}
}


#ifdef __linux__

static const char	*icmp_responses[] =
{
	[ICMP_DEST_UNREACH]		= "Destination Unreachable",
	[ICMP_SOURCE_QUENCH]	= "Source Quench",
	[ICMP_REDIRECT]			= "Redirect (change route)",
	[ICMP_ECHO]				= "Echo Request",
	[ICMP_TIME_EXCEEDED]	= "Time to live exceeded",
	[ICMP_PARAMETERPROB]	= "Parameter Problem",
	[ICMP_TIMESTAMP]		= "Timestamp Request",
	[ICMP_TIMESTAMPREPLY]	= "Timestamp Reply",
	[ICMP_INFO_REQUEST]		= "Information Request",
	[ICMP_INFO_REPLY]		= "Information Reply",
	[ICMP_ADDRESS]			= "Address Mask Request",
	[ICMP_ADDRESSREPLY]		= "Address Mask Reply"
};

#elif __APPLE__

static const char	*icmp_responses[] =
{
	[ICMP_UNREACH]			= "Destination Unreachable",
	[ICMP_SOURCEQUENCH]		= "Source Quench",
	[ICMP_REDIRECT]			= "Redirect (change route)",
	[ICMP_ECHO]				= "Echo Request",
	[ICMP_TIMXCEED]			= "Time to live exceeded",
	[ICMP_PARAMPROB]		= "Parameter Problem",
	[ICMP_TSTAMP]			= "Timestamp Request",
	[ICMP_TSTAMPREPLY]		= "Timestamp Reply",
	[ICMP_IREQ]				= "Information Request",
	[ICMP_IREQREPLY]		= "Information Reply",
	[ICMP_MASKREQ]			= "Address Mask Request",
	[ICMP_MASKREPLY]		= "Address Mask Reply"
};

#endif

#ifdef __linux__

void		check_reply(void *packet, uint16_t seq)
{
	struct iphdr	*ip = packet;
	struct icmphdr	*icmp = packet + IP_HDR_SIZE;
	const char		*error_str;
	char			*sender = net_ntoa((struct in_addr){.s_addr = ip->saddr});
	suseconds_t		rtt;
	u_int16_t		recvd_seq = ntohs(icmp->un.echo.sequence);

	if (icmp->type != ICMP_ECHOREPLY)
	{
		if (icmp->type == ICMP_ECHO)
			return ;
		if (icmp->type < sizeof(icmp_responses))
			error_str = icmp_responses[icmp->type];
		else
			error_str = NULL;
		printf("From %s icmp_seq=%hu %s\n", sender, recvd_seq, error_str);

		g_stats.nb_errors++;
	}
	else
	{
		rtt = get_rtt(packet + IP_HDR_SIZE + ICMP_HDR_SIZE + ALIGN_TIMESTAMP);
		printf("%hu bytes from %s: icmp_seq=%hu ttl=%hhu time=%ld.%02ld ms\n", \
			(uint16_t)(ntohs(ip->tot_len) - IP_HDR_SIZE), \
			sender, recvd_seq, ip->ttl, rtt / 1000l, rtt % 1000l);

		update_rtt_stats(rtt, seq);
	}

	g_stats.packets_recvd++;
}

#elif __APPLE__

void		check_reply(void *packet, uint16_t seq)
{
	struct ip		*ip = packet;
	struct icmp		*icmp = packet + IP_HDR_SIZE;
	const char		*error_str;
	char			*sender = net_ntoa((struct in_addr){.s_addr = ip->ip_src.s_addr});
	suseconds_t		rtt;
	u_int16_t		recvd_seq = ntohs(icmp->icmp_seq);

	if (icmp->icmp_type != ICMP_ECHOREPLY)
	{
		if (icmp->icmp_type == ICMP_ECHO)
			return ;
		if (icmp->icmp_type < sizeof(icmp_responses))
			error_str = icmp_responses[icmp->icmp_type];
		else
			error_str = NULL;
		printf("From %s icmp_seq=%hu %s\n", sender, recvd_seq, error_str);

		g_stats.nb_errors++;
	}
	else
	{
		rtt = get_rtt(packet + IP_HDR_SIZE + ICMP_HDR_SIZE + ALIGN_TIMESTAMP);
		printf("%hu bytes from %s: icmp_seq=%hu ttl=%hhu time=%ld.%02ld ms\n", \
			(uint16_t)(ip->ip_len - IP_HDR_SIZE), \
			sender, recvd_seq, ip->ip_ttl, rtt / 1000l, rtt % 1000l);

		update_rtt_stats(rtt, seq);
	}

	g_stats.packets_recvd++;
}

#endif

