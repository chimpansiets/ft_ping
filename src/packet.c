/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   packet.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: chimpansiets <chimpansiets@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 18:29:03 by chimpansiet   #+#    #+#                 */
/*   Updated: 2021/09/30 20:21:54 by chimpansiet   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

u_int16_t calculate_icmp_checksum(void *packet) {
	u_int16_t	*addr = (u_int16_t*)packet;
	u_int16_t	checksum = 0;
	int			byte_count = 8;

	while (byte_count > 1) {
		checksum += (u_int16_t)*addr++;
		byte_count -= 2;
	}

	printf("%i", checksum);
	return (checksum);
}

void format_packet(t_packet *packet) {
	packet->version_ihl |= 64;
	packet->version_ihl |= 5;

	// ICMP formatting
	packet->type = 8;
	packet->code = 0;
	packet->identifier = getuid();
	packet->sequence_number = getpid();
	packet->checksum = calculate_icmp_checksum((void*)&packet->type);
}