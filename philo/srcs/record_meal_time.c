/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_meal_time.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:02:39 by totaisei          #+#    #+#             */
/*   Updated: 2021/11/28 10:01:00 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_meal_time(t_philo *philo, long time)
{
	pthread_mutex_lock(&(philo->right_to_meal_time));
	philo->last_meal_time = time;
	pthread_mutex_unlock(&(philo->right_to_meal_time));
}

long	read_meal_time(t_philo *philo)
{
	long	res;

	pthread_mutex_lock(&(philo->right_to_meal_time));
	res = philo->last_meal_time;
	pthread_mutex_unlock(&(philo->right_to_meal_time));
	return (res);
}
