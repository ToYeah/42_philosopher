/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_arg_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:06:03 by totaisei          #+#    #+#             */
/*   Updated: 2021/11/24 19:06:16 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_bool	input_num_arg(long *dest, char *str)
{
	if (is_num_str(str) && ft_atol_limit(str, dest)
		&& *dest <= UINT_MAX)
	{
		return (TRUE);
	}
	return (FALSE);
}

t_bool	input_option_arg(t_rule *rule, long argc, char **argv)
{
	rule->option = 0;
	if (argc != 6)
	{
		rule->option_exists = FALSE;
		return (TRUE);
	}
	rule->option_exists = TRUE;
	return (input_num_arg(&(rule->option), argv[5]));
}

t_bool	input_arg(t_rule *rule, int argc, char **argv)
{
	if ((argc != 5 && argc != 6)
		|| !input_num_arg(&(rule->num), argv[1])
		|| !input_num_arg(&(rule->time_to_die), argv[2])
		|| !input_num_arg(&(rule->time_to_eat), argv[3])
		|| !input_num_arg(&(rule->time_to_sleep), argv[4])
		|| !input_option_arg(rule, argc, argv))
	{
		printf("Invalid argument format.\n");
		return (FALSE);
	}
	return (TRUE);
}
