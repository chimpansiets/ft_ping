/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/10 11:34:10 by svoort         #+#    #+#                */
/*   Updated: 2019/01/20 13:59:06 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	ctr1;
	size_t	ctr2;
	size_t	temp_ctr;

	ctr1 = 0;
	ctr2 = 0;
	temp_ctr = 0;
	if (needle[0] == '\0')
		return ((char*)haystack);
	while (haystack[ctr1] != '\0' && ctr1 < len)
	{
		while (haystack[ctr1] == needle[ctr2] && haystack[ctr1] != '\0'
				&& ctr1 < len)
		{
			ctr1++;
			ctr2++;
		}
		if (needle[ctr2] == '\0' && (needle[ctr2 - 1]) == (haystack[ctr1 - 1]))
			return ((char*)&haystack[ctr1 - ctr2]);
		ctr2 = 0;
		temp_ctr++;
		ctr1 = temp_ctr;
	}
	return (NULL);
}
