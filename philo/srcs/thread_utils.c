/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:02:39 by totaisei          #+#    #+#             */
/*   Updated: 2021/11/28 11:52:08 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_in_us(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((long)(now.tv_sec * 1000000 + now.tv_usec));
}

long	get_time_in_ms(void)
{
	return (get_time_in_us() / 1000);
}

void	philo_usleep(long time, t_rule *rule)
{
	long	start;
	long	now;

	start = get_time_in_us();
	while (is_continue_simulation(rule))
	{
		now = get_time_in_us();
		if ((now - start) / 1000 >= time)
			break ;
		usleep(1000);
	}
}

long	record_philo_action(t_philo *philo, const char *str)
{
	long	time;

	pthread_mutex_lock(&(philo->rule->right_to_output));
	time = get_time_in_ms();
	if (philo->rule->dead_exists == FALSE
		&& philo->rule->full_philo_count != philo->rule->num)
		printf("%ld %ld %s\n", time, philo->num, str);
	pthread_mutex_unlock(&(philo->rule->right_to_output));
	return (time);
}

t_bool	is_continue_simulation(t_rule *rule)
{
	t_bool	res;

	pthread_mutex_lock(&(rule->right_to_output));
	res = rule->dead_exists == FALSE && rule->full_philo_count != rule->num;
	pthread_mutex_unlock(&(rule->right_to_output));
	return (res);
}
