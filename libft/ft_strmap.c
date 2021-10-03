/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/11 11:07:19 by svoort         #+#    #+#                */
/*   Updated: 2019/01/20 13:33:25 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*ret;
	size_t	i;

	if (s != NULL && f != NULL)
	{
		ret = (char*)ft_memalloc(ft_strlen(s) + 1);
		if (ret == NULL)
			return (NULL);
		i = 0;
		while (i < ft_strlen(s))
		{
			ret[i] = f(s[i]);
			i++;
		}
		ret[i] = '\0';
		return (ret);
	}
	return (NULL);
}
