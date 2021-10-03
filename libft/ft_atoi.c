/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 16:22:51 by svoort         #+#    #+#                */
/*   Updated: 2019/01/20 13:27:24 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int i;
	int ret;
	int	min_or_pos;

	i = 0;
	ret = 0;
	min_or_pos = 1;
	while (str[i] <= 32 && str[i] != '\e' && str[i] != '\0')
	{
		if (str[i] < 0)
			return (ret * min_or_pos);
		i++;
	}
	if (str[i] == '-')
		min_or_pos = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]) && str[i] != '\e')
	{
		ret = (ret * 10) + str[i] - '0';
		i++;
	}
	return (ret * min_or_pos);
}
