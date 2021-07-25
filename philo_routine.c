#include "philo.h"

void set_last_meal_time(t_philo *philo)
{
	if (gettimeofday(&(philo->last_meal_time), NULL) != 0)
	{
		//error
		exit(1);
	}
}

void take_fork(t_philo *philo, t_bool is_bigger)
{
	t_time time;

	if (is_bigger == TRUE)
		pthread_mutex_lock(&(philo->bigger->mutex));
	else
		pthread_mutex_lock(&(philo->smaller->mutex));
	gettimeofday(&time, NULL);
	printf("%d %d has taken a fork\n", time.tv_usec, philo->num);
}

void put_fork(t_philo *philo, t_bool is_bigger)
{
	if (is_bigger == TRUE)
		pthread_mutex_unlock(&(philo->bigger->mutex));
	else
		pthread_mutex_unlock(&(philo->smaller->mutex));
}

void *philo_routine(void *p)
{
	t_philo *philo = (t_philo *)p;

	while (1)
	{
		set_last_meal_time(philo);
		take_fork(philo, TRUE);
		take_fork(philo, FALSE);
		printf("%d hello, philo %d\n", philo->last_meal_time.tv_usec, philo->num);
		usleep(500000);
		put_fork(philo, FALSE);
		put_fork(philo, TRUE);
		usleep(500000);
	}
	return (NULL);
}
