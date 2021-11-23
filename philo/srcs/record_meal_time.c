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
