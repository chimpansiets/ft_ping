/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/12 12:58:27 by svoort         #+#    #+#                */
/*   Updated: 2019/01/18 15:20:52 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		i2;
	char	*ret;

	if (s1 != NULL && s2 != NULL)
	{
		i = 0;
		i2 = 0;
		ret = (char*)ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (ret == NULL)
			return (NULL);
		while (s1[i] != '\0')
		{
			ret[i] = s1[i];
			i++;
		}
		while (s2[i2] != '\0')
			ret[i++] = s2[i2++];
		ret[i] = '\0';
		return (ret);
	}
	return (NULL);
}
