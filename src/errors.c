/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 21:08:07 by svoort        #+#    #+#                 */
/*   Updated: 2021/10/02 21:08:07 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

# define FT_PING_FATAL				"\033[31m[FATAL ERROR] \033[0m"
# define FT_PING_WARN				"\033[33m[WARNING] \033[0m"

void			fatal(const char * const message)
{
	dprintf(2, FT_PING_FATAL);
	perror(message);

	exit(EXIT_FAILURE);
}

void			warn(const char * const message)
{
	dprintf(2, FT_PING_WARN);
	perror(message);
}
