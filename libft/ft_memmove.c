/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 11:38:36 by svoort         #+#    #+#                */
/*   Updated: 2019/01/18 10:24:44 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void *src, size_t len)
{
	unsigned char	*csrc;
	unsigned char	*cdst;
	size_t			i;

	i = 0;
	if (&dst[0] < &src[0])
		while (i < len)
		{
			cdst = (unsigned char*)&dst[i];
			csrc = (unsigned char*)&src[i];
			*cdst = *csrc;
			i++;
		}
	else
		while (i < len)
		{
			len--;
			cdst = (unsigned char*)&dst[len];
			csrc = (unsigned char*)&src[len];
			*cdst = *csrc;
		}
	return (dst);
}
