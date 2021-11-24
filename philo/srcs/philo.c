/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:02:39 by totaisei          #+#    #+#             */
/*   Updated: 2021/11/24 19:03:17 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*init_forks(long count)
{
	t_fork	*res;
	long	i;

	res = malloc(sizeof(t_fork) * count);
	if (!res)
		return (NULL);
	i = 0;
	while (i < count)
	{
		res[i].weight = i;
		if (pthread_mutex_init(&(res[i].mutex), NULL) != 0)
		{
			free(res);
			return (NULL);
		}
		i++;
	}
	return (res);
}

void	init_philosophers_fork(t_philo *philo, t_fork *forks)
{
	if (philo->num == 1)
	{
		philo->smaller = &(forks[philo->num - 1]);
		philo->bigger = &(forks[philo->rule->num - 1]);
	}
	else
	{
		philo->smaller = &(forks[philo->num - 2]);
		philo->bigger = &(forks[philo->num - 1]);
	}
}

t_philo	*init_philosophers(long count, t_fork *forks, t_rule *rule)
{
	t_philo	*res;
	long	i;

	res = malloc(sizeof(t_philo) * count);
	if (!res)
		return (NULL);
	i = 0;
	while (i < count)
	{
		res[i].num = i + 1;
		res[i].rule = rule;
		res[i].eat_count = 0;
		res[i].last_meal_time = get_time_in_ms();
		init_philosophers_fork(&(res[i]), forks);
		if (pthread_mutex_init(&(res[i].right_to_meal_time), NULL)
			|| pthread_create(&(res[i].thread), NULL, philo_routine, &(res[i]))
			|| pthread_create(&(res[i].doctor),
				NULL, doctor_routine, &(res[i])))
		{
			free(res);
			return (NULL);
		}
		i++;
	}
	return (res);
}

t_bool	init_rule(t_rule *rule, int argc, char **argv)
{
	if (!input_arg(rule, argc, argv)
		|| pthread_mutex_init(&(rule->right_to_output), NULL)
		|| pthread_mutex_init(&(rule->right_to_consultation), NULL))
	{
		return (FALSE);
	}
	rule->dead_exists = FALSE;
	rule->full_philo_count = 0;
	rule->odd_flag = TRUE;
	if (rule->num % 2 == 0)
		rule->odd_flag = FALSE;
	return (TRUE);
}

void	join_philosophers(t_philo *philos, long count)
{
	long	i;

	i = 0;
	while (i < count)
	{
		pthread_join(philos[i].thread, NULL);
		pthread_join(philos[i].doctor, NULL);
		i++;
	}
}
