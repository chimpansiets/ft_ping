/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: chimpansiets <chimpansiets@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 16:00:47 by chimpansiet   #+#    #+#                 */
/*   Updated: 2021/10/03 10:45:01 by chimpansiet   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_ping	g_ping =
{
	.sequence = 0,
	.socket = 0,
	.dest_addr = NULL,
	.dest =
	{
		.sin_family = AF_INET,
		.sin_port = 0
	},
    .flags = NULL,
};

t_flags *parse_args(int argc, char **argv) {
    struct addrinfo			hints = {.ai_family = AF_INET};
	struct addrinfo			*res;
    t_flags                 *flags = ft_memalloc(sizeof(int) * 2 + sizeof(struct in_addr));
    unsigned char           accept_flags = 1;
    
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && accept_flags == 1) {
            if (ft_strcmp(argv[i], "-h") == 0)
                flags->h = 1;
            else if (ft_strcmp(argv[i], "-v") == 0)
                flags->v = 1;
        } else {
            accept_flags = 0;
            if (argv[i][0] == '-') {
                dprintf(2, "ping: can't give flags after destination\n");
                return (NULL);
            }
            if (getaddrinfo(argv[i], NULL, &hints, &res)) {
                dprintf(2, "ping: failed to get address from %s\n", argv[i]);
		        return (NULL);
            }
            g_ping.dest.sin_addr.s_addr = ((struct sockaddr_in*)res->ai_addr)->sin_addr.s_addr;
            g_ping.dest_addr = argv[i];
            freeaddrinfo(res);
        }
    }
    return (flags);
}

static void	signal_exit(int sig)
{
	close(g_ping.socket);
	print_stats(g_ping.sequence, g_ping.dest_addr);
	exit(EXIT_SUCCESS);
}

static void	send_ping(int sig)
{
	char		sent_packet[PACKET_SIZE];

	g_ping.sequence++;

	gen_ip_header(sent_packet, g_ping.dest.sin_addr.s_addr);
	gen_icmp_msg(sent_packet + IP_HDR_SIZE, g_ping.sequence);

	send_echo_request(g_ping.socket, (const struct sockaddr *)&g_ping.dest, \
		sent_packet, g_ping.flags->v);

	alarm(FT_PING_DELAY);
}

static void	recv_pong(void)
{
	char		rcvd_packet[PACKET_SIZE];

	while (true)
	{
		receive_echo_reply(g_ping.socket, g_ping.dest, rcvd_packet, g_ping.flags->v);
		check_reply(rcvd_packet, g_ping.sequence);
	}
}


int	main(int argc, char **argv)
{
    g_ping.flags = parse_args(argc, argv);

    if (g_ping.flags == NULL)
        return (EXIT_FAILURE);
    if (argc < 2 || (g_ping.flags->h == 1))
	{
		dprintf(2, "Usage: %s [-h] [-v] destination\n", argv[0]);
		return (EXIT_FAILURE);
	}
    if (signal(SIGALRM, &send_ping) == SIG_ERR
	|| signal(SIGINT, &signal_exit) == SIG_ERR)
		fatal("alarm failed");

    g_ping.socket = init_socket();
    set_stats_timer();

    printf("PING %s %d(%d) bytes of data.\n", g_ping.dest_addr, ICMP_PAYLOAD_SIZE, PACKET_SIZE);
    
    send_ping(0);
    recv_pong();

    return (0);
}
