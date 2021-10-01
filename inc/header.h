/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: chimpansiets <chimpansiets@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 16:01:06 by chimpansiet   #+#    #+#                 */
/*   Updated: 2021/09/30 20:17:02 by chimpansiet   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdint.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct  s_flags {
    int         h;
    int         v;
}               t_flags;

typedef struct  s_packet {
    // HEADER
    u_int8_t    version_ihl;
    u_int8_t    tos;
    u_int16_t   length;
    u_int16_t   identification;
    u_int16_t   flags_offset;
    u_int8_t    ttl;
    u_int8_t    protocol;
    u_int16_t   header_checksum;
    u_int32_t   source_ip;
    u_int32_t   destination_ip;

    // ICMP HEADER
    u_int8_t    type;
    u_int8_t    code;
    u_int16_t   checksum;
    u_int16_t   identifier;
    u_int16_t   sequence_number;
}               t_packet;

void            format_packet(t_packet *packet);

#endif
