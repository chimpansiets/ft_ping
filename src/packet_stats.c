/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   packet_stats.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 21:20:41 by svoort        #+#    #+#                 */
/*   Updated: 2021/10/02 21:20:41 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_stats      g_stats;

static suseconds_t	get_time(void)
{
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL) == -1)
	{
		warn("failed getting time of day");
		return (0);
	}
	return (curr_time.tv_sec * 1000000 + curr_time.tv_usec);
}

void				set_stats_timer(void)
{
	g_stats.start_time = get_time();
}