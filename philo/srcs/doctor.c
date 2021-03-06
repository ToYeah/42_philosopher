/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:02:39 by totaisei          #+#    #+#             */
/*   Updated: 2021/12/03 10:22:47 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	is_philo_arive(t_philo *philo)
{
	long	now;

	now = get_time_in_ms();
	if (now - read_meal_time(philo) >= philo->rule->time_to_die)
		return (FALSE);
	return (TRUE);
}

void	*doctor_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (is_continue_simulation(philo->rule))
	{
		usleep(1000);
		pthread_mutex_lock(&(philo->rule->right_to_output));
		if (is_philo_arive(philo) == FALSE
			&& read_dead_exists(philo->rule) == FALSE)
		{
			write_dead_exists(philo->rule);
			printf("%ld %ld %s\n", get_time_in_ms(), philo->num, MSG_DIE);
		}
		pthread_mutex_unlock(&(philo->rule->right_to_output));
	}
	return (NULL);
}
