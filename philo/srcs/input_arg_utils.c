/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_arg_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:02:39 by totaisei          #+#    #+#             */
/*   Updated: 2021/11/24 19:03:06 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	judge_sign(const char c)
{
	if (c == '-')
		return (-1);
	return (1);
}

t_bool	ft_atol_limit(const char *str, long *return_value)
{
	int				i;
	int				sign;
	unsigned long	div;
	unsigned long	res;

	i = 0;
	res = 0;
	div = LONG_MAX / 10;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	sign = judge_sign(str[i]);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ('0' <= str[i] && str[i] <= '9'))
	{
		if ((div < res || (div == res && str[i] > '7')) && sign == 1)
			return (FALSE);
		else if ((div < res || (div == res && str[i] > '8')) && sign == -1)
			return (FALSE);
		res *= 10;
		res += str[i++] - '0';
	}
	*return_value = (long)res * sign;
	return (TRUE);
}

t_bool	is_num_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
