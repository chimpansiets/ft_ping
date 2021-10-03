/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/10 16:02:13 by svoort         #+#    #+#                */
/*   Updated: 2019/01/18 16:19:36 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*u_s1;
	unsigned char	*u_s2;
	size_t			i;

	i = 0;
	if (n == 0)
		return (0);
	if ((*s1) == '\0' && (*s2) == '\0')
		return (0);
	u_s1 = (unsigned char*)s1;
	u_s2 = (unsigned char*)s2;
	if ((*s1) == '\0' || (*s2) == '\0')
		return (u_s1[i] - u_s2[i]);
	while (u_s1[i] != '\0' && u_s2[i] != '\0')
	{
		if (u_s1[i] < u_s2[i] || u_s1[i] > u_s2[i])
			return (u_s1[i] - u_s2[i]);
		i++;
		if (i >= n)
			return (u_s1[i - 1] - u_s2[i - 1]);
	}
	return (u_s1[i] - u_s2[i]);
}
