#include "philo.h"

void set_last_meal_time(t_philo *philo)
{
	if (gettimeofday(&(philo->last_meal_time), NULL) != 0)
	{
		//error
		exit(1);
	}
}

void take_two_forks(t_philo *philo)
{
	t_time time;

	pthread_mutex_lock(&(philo->smaller->mutex));
	pthread_mutex_lock(&(philo->bigger->mutex));
	gettimeofday(&time, NULL);
	printf("%d %d has taken a fork\n", time.tv_usec, philo->num);
}

void put_two_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->bigger->mutex));
	pthread_mutex_unlock(&(philo->smaller->mutex));
}

void *philo_routine(void *p)
{
	t_philo *philo = (t_philo *)p;

	while (1)
	{
		set_last_meal_time(philo);
		take_two_forks(philo);
		printf("%d hello, philo %d\n", philo->last_meal_time.tv_usec, philo->num);
		usleep(500000);
		put_two_forks(philo);
		usleep(500000);
	}
	return (NULL);
}
