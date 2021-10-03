/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   socket_io.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: chimpansiets <chimpansiets@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/03 10:16:17 by chimpansiet   #+#    #+#                 */
/*   Updated: 2021/10/03 10:20:29 by chimpansiet   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	send_echo_request(int icmp_sock, const struct sockaddr *dest, \
				char *packet, bool verbose_mode)
{
	ssize_t	ret;

	ret = sendto(icmp_sock, packet, PACKET_SIZE, 0, dest, sizeof(*dest));
	if (ret == -1)
		warn("sendto failed");

	if (verbose_mode)
	{
		printf("sending request:\n");
		print_ip_icmp_packet(packet);
	}
}

void	receive_echo_reply(int icmp_sock, struct sockaddr_in sockaddr, \
			char *packet, bool verbose_mode)
{
	char			buffer[512];
	ssize_t			ret;
	struct iovec	io =
	{
		.iov_base = packet,
		.iov_len = PACKET_SIZE
	};
	struct msghdr	msg =
	{
		.msg_name = &sockaddr,
		.msg_namelen = sizeof(sockaddr),
		.msg_iov = &io,
		.msg_iovlen = 1,
		.msg_control = buffer,
		.msg_controllen = sizeof(buffer),
		.msg_flags = 0
	};
	ret = recvmsg(icmp_sock, &msg, 0);
	if (ret == -1)
		warn("recvmsg failed");

	if (verbose_mode)
	{
		printf("recieved answer:\n");
		print_ip_icmp_packet(packet);
	}
}
