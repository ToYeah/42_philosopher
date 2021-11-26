/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:06:03 by totaisei          #+#    #+#             */
/*   Updated: 2021/11/26 20:15:10 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_routine(t_philo *philo)
{
	if (pthread_create(&(philo->nurse), NULL, nurse_routine, philo)
		|| pthread_create(&(philo->doctor), NULL, doctor_routine, philo))
	{
		exit(EXIT_FAILURE);
	}
	if (philo->num % 2 == 0)
	{
		philo_usleep(1, philo->rule);
	}
	write_meal_time(philo, get_time_in_ms());
	while (philo->rule->dead_exists == FALSE
		&& philo->rule->full_philo_count != philo->rule->num)
	{
		take_fork(philo);
		eat_meal(philo);
		put_fork(philo);
		sleep_philo(philo);
		think_philo(philo);
	}
	exit(EXIT_SUCCESS);
}
