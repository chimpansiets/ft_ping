/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/10 10:49:33 by svoort         #+#    #+#                */
/*   Updated: 2019/01/18 13:58:58 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	i;
	int		i2;
	size_t	destlen;
	size_t	maxlen;

	i = ft_strlen(dest);
	i2 = 0;
	destlen = i;
	maxlen = ft_strlen(src) + ft_strlen(dest);
	while (i < maxlen && i < (destlen + n))
	{
		dest[i] = src[i2];
		i++;
		i2++;
	}
	dest[i] = '\0';
	return (dest);
}
