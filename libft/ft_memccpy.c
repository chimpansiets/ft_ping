/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 11:32:44 by svoort         #+#    #+#                */
/*   Updated: 2019/01/18 13:55:05 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	size_t			i;
	unsigned char	*ret;
	unsigned char	*src;

	if (s1 == s2 || n <= 0)
		return (NULL);
	i = 0;
	ret = (unsigned char*)s1;
	src = (unsigned char*)s2;
	while (i < n)
	{
		ret[i] = src[i];
		if (src[i] == (unsigned char)c)
			return (ret + i + 1);
		i++;
	}
	return (NULL);
}
