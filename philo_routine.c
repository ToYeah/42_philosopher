#include "philo.h"

void *philo_routine(void *p)
{
	t_philo *philo = (t_philo *)p;
	printf("hello, philo%d", philo->num);
	return (NULL);
}
