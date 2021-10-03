/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memalloc_2d.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/14 14:07:41 by svoort         #+#    #+#                */
/*   Updated: 2019/01/18 14:08:52 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_memalloc_2d(size_t n1, size_t n2)
{
	void	**area;
	int		i;

	area = (void**)malloc(sizeof(char*) * n1);
	i = 0;
	while (i < (int)n1)
		area[i++] = (char*)malloc(sizeof(char) * n2);
	return (area);
}
