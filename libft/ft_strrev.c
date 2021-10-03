/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrev.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/10 16:45:06 by svoort         #+#    #+#                */
/*   Updated: 2019/01/18 13:57:46 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strrev(char *str)
{
	char	*temp;
	int		i;
	int		i2;

	i = 0;
	i2 = 0;
	temp = (char*)malloc(sizeof(char) * ft_strlen(str));
	while (str[i] != '\0')
		i++;
	i--;
	while (i >= 0)
	{
		temp[i2] = str[i];
		i2++;
		i--;
	}
	i = 0;
	while (i < i2)
	{
		str[i] = temp[i];
		i++;
	}
	free(temp);
}
