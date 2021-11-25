/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:06:03 by totaisei          #+#    #+#             */
/*   Updated: 2021/11/25 13:31:49 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	while (rule->dead_exists == FALSE
		&& rule->full_philo_count != rule->num)
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

	sem_wait(philo->rule->output_sem);
	time = get_time_in_ms();
	if (philo->rule->dead_exists == FALSE
		&& philo->rule->full_philo_count != philo->rule->num)
		printf("%ld %ld %s\n", time, philo->num, str);
	sem_post(philo->rule->output_sem);
	return (time);
}
