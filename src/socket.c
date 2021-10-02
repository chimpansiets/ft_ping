/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   socket.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 21:02:31 by svoort        #+#    #+#                 */
/*   Updated: 2021/10/02 21:02:31 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int     init_socket(void) {
    int     icmp_socket;

    /*
    **  Once a long time ago, it was thought that maybe a address family 
    **  (what the "AF" in "AF_INET" stands for) might support several protocols 
    **  that were referenced by their protocol family
    **  (what the "PF" in "PF_INET" stands for).
    **  That didn't happen. Oh well. So the correct thing to do is to use 
    **  AF_INET in your struct sockaddr_in and PF_INET in your call to 
    **  socket()
    */

    icmp_socket = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (icmp_socket < 0)
        fatal("failed opening ICMP socket");

    /*
    **  The IPv4 layer generates an IP header when sending a packet unless 
    **  the IP_HDRINCL socket option is enabled on the socket. 
    **  When it is enabled, the packet must contain an IP header.
    **  For receiving the IP header is always included in the packet.
    */

    if (setsockopt(icmp_socket, IPPROTO_IP, IP_HDRINCL, \
        (int[1]){1}, sizeof(int)) == -1)
        fatal("failed to set socket option");
    
    return (icmp_socket);
}