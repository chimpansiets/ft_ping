/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   in_cksum.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: chimpansiets <chimpansiets@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/03 10:14:57 by chimpansiet   #+#    #+#                 */
/*   Updated: 2021/10/03 10:15:04 by chimpansiet   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

uint16_t    in_cksum(u_int16_t *addr, int len)
{

    int         nleft;
    uint16_t    *w;
    uint16_t    answer;
    uint32_t    sum;

    nleft = len;
    sum = 0;
    w = addr;
    answer = 0;

    /*
    **  Our algorithm is simple, using a 32 bit accumulator (sum), we add
    **  sequential 16 bit words to it, and at the end, fold back all the
    **  carry bits from the top 16 bits into the lower 16 bits.
    */

    while (nleft > 1)
    {

        /*
        **
        */

        sum += *w++;

        /*
        **
        */

        nleft -= 2;

    }

    /*
    ** mop up an odd byte, if necessary
    */

    if (nleft == 1)
    {

        /*
        **
        */

        * (unsigned char *) (&answer) = * (unsigned char *) w;

        /*
        **
        */

        sum += answer;

    }

    /*
    ** Add back carry outs from top 16 bits to low 16 bits
    ** add hi 16 to low 16
    */

    sum = (sum >> 16) + (sum & 0xffff);

    /*
    ** Add carry
    */

    sum += (sum >> 16);

    /*
    ** truncate to 16 bits
    */

    answer = ~sum;

    /*
    **
    */

    return (answer);

}