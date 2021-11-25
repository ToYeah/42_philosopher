/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctor_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:06:03 by totaisei          #+#    #+#             */
/*   Updated: 2021/11/25 13:15:13 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_bool	is_philo_arive(t_philo *philo)
{
	long	now;

	now = get_time_in_ms();
	if (now - philo->last_meal_time >= philo->rule->time_to_die)
		return (FALSE);
	return (TRUE);
}

void	*doctor_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (philo->rule->dead_exists == FALSE)
	{
		usleep(1000);
		sem_wait(philo->rule->consul_sem);
		sem_wait(philo->rule->output_sem);
		if (is_philo_arive(philo) == FALSE)
		{
			sem_post(philo->rule->dead_sem);
			printf("%ld %ld %s\n", get_time_in_ms(), philo->num, MSG_DIE);
			exit(EXIT_SUCCESS);
		}
		sem_post(philo->rule->consul_sem);
		sem_post(philo->rule->output_sem);
	}
	return (NULL);
}

void	*nurse_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	sem_wait(philo->rule->dead_sem);
	sem_post(philo->rule->dead_sem);
	exit(EXIT_SUCCESS);
}
