/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ip_header.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: chimpansiets <chimpansiets@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/03 10:10:38 by chimpansiet   #+#    #+#                 */
/*   Updated: 2021/10/03 10:11:22 by chimpansiet   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#ifdef __linux__

static inline void	fill_ip_header(struct iphdr *ip, u_int32_t dest)
{
	ip->version = 4;
	ip->ihl = IP_HDR_SIZE / 4;
	ip->tos = 0;
	ip->tot_len = htons(PACKET_SIZE);
	ip->id = htons(0);
	ip->frag_off = htons(0);
	ip->ttl = FT_PING_TTL;
	ip->protocol = IPPROTO_ICMP;
	ip->check = 0;
	ip->saddr = INADDR_ANY;
	ip->daddr = dest;
}

#elif __APPLE__

static inline void	fill_ip_header(struct ip *ip, u_int32_t dest)
{
	ip->ip_v = 4;
	ip->ip_hl = IP_HDR_SIZE / 4;
	ip->ip_tos = 0;
	ip->ip_len = PACKET_SIZE;
	ip->ip_id = htons(0);
	ip->ip_off = 0;
	ip->ip_ttl = FT_PING_TTL;
	ip->ip_p = IPPROTO_ICMP;
	ip->ip_sum = 0;
	ip->ip_src.s_addr = INADDR_ANY;
	ip->ip_dst.s_addr = dest;
}

#endif

/*
** gen_ip_header
**   provide dest address in network byte order
*/

void			gen_ip_header(void *packet, u_int32_t dest)
{
	fill_ip_header(packet, dest);
}
