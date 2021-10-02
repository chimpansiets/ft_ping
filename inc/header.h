/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: chimpansiets <chimpansiets@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 16:01:06 by chimpansiet   #+#    #+#                 */
/*   Updated: 2021/10/01 15:44:32 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <stdbool.h>
# include <math.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/time.h>
# include <netdb.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <arpa/inet.h>
# include "../libft/libft.h"

# define IP_HDR_SIZE			20
# define ICMP_HDR_SIZE			ICMP_MINLEN
# define ICMP_PAYLOAD_SIZE		56
# define PACKET_SIZE			(IP_HDR_SIZE + ICMP_HDR_SIZE + ICMP_PAYLOAD_SIZE)
# define ALIGN_TIMESTAMP		4

typedef struct  s_flags {
    int             h;
    int             v;
}               t_flags;

typedef struct  s_ping {
    struct sockaddr_in  dest;
    char                *dest_addr;
    int                 socket;
    u_int16_t           sequence;
    t_flags             *flags;
}               t_ping;

typedef struct			s_stats
{
	suseconds_t			rtt_min;
	suseconds_t			rtt_max;
	suseconds_t			rtt_total;
	suseconds_t			rtt_sq_total;
	suseconds_t			start_time;
	uint				packets_recvd;
	uint				nb_errors;
}						t_stats;


void			        fatal(const char * const message);
void			        warn(const char * const message);
int                     init_socket(void);
void				    set_stats_timer(void);

#endif
