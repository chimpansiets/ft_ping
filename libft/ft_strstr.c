/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/10 08:51:06 by svoort         #+#    #+#                */
/*   Updated: 2019/01/20 14:43:34 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		ctr1;
	int		ctr2;

	ctr1 = 0;
	ctr2 = 0;
	if (needle[0] == '\0')
		return ((char*)haystack);
	while (haystack[ctr1] != '\0')
	{
		while (haystack[ctr1] == needle[ctr2] && haystack[ctr1] != '\0')
		{
			ctr1++;
			ctr2++;
		}
		if (needle[ctr2] == '\0' && (needle[ctr2 - 1]) == (haystack[ctr1 - 1]))
			return ((char*)&haystack[ctr1 - ctr2]);
		ctr1 = ctr1 - ctr2;
		ctr2 = 0;
		ctr1++;
	}
	return (NULL);
}
