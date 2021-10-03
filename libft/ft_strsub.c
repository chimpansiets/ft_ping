/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsub.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/12 13:22:57 by svoort         #+#    #+#                */
/*   Updated: 2019/01/18 14:07:48 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;

	if (s != NULL)
	{
		ret = (char*)ft_memalloc(len + 1);
		if (ret == NULL)
			return (NULL);
		i = 0;
		while (i < len && s[start] != '\0')
		{
			ret[i] = s[start];
			start++;
			i++;
		}
		ret[i] = '\0';
		return (ret);
	}
	return (NULL);
}
