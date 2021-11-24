/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:06:03 by totaisei          #+#    #+#             */
/*   Updated: 2021/11/24 19:06:24 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_fork(t_philo *philo)
{
	sem_wait(philo->rule->fork_sem);
	record_philo_action(philo, MSG_FORK);
	sem_wait(philo->rule->fork_sem);
	record_philo_action(philo, MSG_FORK);
}

void	put_fork(t_philo *philo)
{
	sem_post(philo->rule->fork_sem);
	sem_post(philo->rule->fork_sem);
}

void	eat_meal(t_philo *philo)
{
	philo->last_meal_time = record_philo_action(philo, MSG_EAT);
	philo_usleep(philo->rule->time_to_eat);
	philo->eat_count += 1;
	if (philo->rule->option_exists && philo->eat_count == philo->rule->option)
		sem_post(philo->rule->option_sem);
}

void	sleep_philo(t_philo *philo)
{
	record_philo_action(philo, MSG_SLEEP);
	philo_usleep(philo->rule->time_to_sleep);
}

void	think_philo(t_philo *philo)
{
	record_philo_action(philo, MSG_THINK);
	if (philo->rule->odd_flag)
		philo_usleep(philo->rule->time_to_eat);
}
