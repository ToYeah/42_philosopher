/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:02:39 by totaisei          #+#    #+#             */
/*   Updated: 2021/11/28 11:26:18 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->num % 2 == 0)
	{
		philo_usleep(1, philo->rule);
	}
	write_meal_time(philo, get_time_in_ms());
	if (philo->rule->num == 1)
	{
		record_philo_action(philo, MSG_FORK);
		return (NULL);
	}
	while (is_continue_simulation(philo->rule))
	{
		take_fork(philo);
		eat_meal(philo);
		put_fork(philo);
		sleep_philo(philo);
		think_philo(philo);
	}
	return (NULL);
}
