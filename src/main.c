/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: chimpansiets <chimpansiets@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 16:00:47 by chimpansiet   #+#    #+#                 */
/*   Updated: 2021/09/30 20:19:21 by chimpansiet   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_flags *parse_flags(int argc, char **argv) {
    t_flags *flags = ft_memalloc(sizeof(int) * 2);
    
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0)
            flags->h = 1;
        else if (strcmp(argv[i], "-v") == 0)
            flags->v = 1;
    }
    return (flags);
}

int	main(int argc, char **argv)
{
    t_flags *flags = parse_flags(argc, argv);
    t_packet *packet = ft_memalloc(sizeof(u_int8_t) * 28);

    format_packet(packet);
    printf("type: %i\ncode: %i\nchecksum: %i\nidentfier: %i\nsequence number: %i\n", packet->type, packet->code, packet->checksum, packet->identifier, packet->sequence_number);
    return (0);
}
