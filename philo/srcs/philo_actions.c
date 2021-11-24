/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:02:39 by totaisei          #+#    #+#             */
/*   Updated: 2021/11/24 20:43:39 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->smaller->mutex));
	record_philo_action(philo, MSG_FORK);
	pthread_mutex_lock(&(philo->bigger->mutex));
	record_philo_action(philo, MSG_FORK);
}

void	put_fork(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->bigger->mutex));
	pthread_mutex_unlock(&(philo->smaller->mutex));
}

void	eat_meal(t_philo *philo)
{
	write_meal_time(philo, record_philo_action(philo, MSG_EAT));
	philo_usleep(philo->rule->time_to_eat, philo->rule);
	philo->eat_count += 1;
	if (philo->rule->option_exists && philo->eat_count == philo->rule->option)
		philo->rule->full_philo_count += 1;
}

void	sleep_philo(t_philo *philo)
{
	record_philo_action(philo, MSG_SLEEP);
	philo_usleep(philo->rule->time_to_sleep, philo->rule);
}

void	think_philo(t_philo *philo)
{
	record_philo_action(philo, MSG_THINK);
	if (philo->rule->odd_flag)
		philo_usleep(philo->rule->time_to_eat, philo->rule);
}
