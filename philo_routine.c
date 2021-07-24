#include "philo.h"

void set_last_meal_time(t_philo *philo)
{
	if (gettimeofday(&(philo->last_meal_time), NULL) != 0)
	{
		//error
		exit(1);
	}
}

void *philo_routine(void *p)
{
	t_philo *philo = (t_philo *)p;

	while (1)
	{
		set_last_meal_time(philo);
		printf("%ld hello, philo %d\n", philo->last_meal_time.tv_sec, philo->num);
	}
	return (NULL);
}
