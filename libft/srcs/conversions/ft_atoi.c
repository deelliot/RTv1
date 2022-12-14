/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:16:53 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/09 15:40:10 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The atoi() function converts the initial portion of the string pointed to
by str to int representation.*/

#include "libft.h"

static int	ft_check_sign(const char *str, int i)
{
	if (str[i] == '-')
		return (-1);
	else
		return (1);
}

static int	ft_clear_sign(const char *str, int i)
{
	if (str[i] == '+' || str[i] == '-')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	x;
	int	sign;

	i = ft_clear_whitespace(str);
	sign = ft_check_sign (str, i);
	i = ft_clear_sign(str, i);
	x = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			break ;
		x = (x * 10) + (str[i] - '0');
		i++;
	}
	return (sign * x);
}
