/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_meal_time_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:02:39 by totaisei          #+#    #+#             */
/*   Updated: 2021/11/26 20:11:58 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_meal_time(t_philo *philo, long time)
{
	sem_wait(philo->rule->time_sem);
	philo->last_meal_time = time;
	sem_post(philo->rule->time_sem);
}

long	read_meal_time(t_philo *philo)
{
	long	res;

	sem_wait(philo->rule->time_sem);
	res = philo->last_meal_time;
	sem_post(philo->rule->time_sem);
	return (res);
}
