#include "philo.h"

void take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->smaller->mutex));
	record_philo_action(philo, MSG_FORK);
	pthread_mutex_lock(&(philo->bigger->mutex));
	record_philo_action(philo, MSG_FORK);
}

void put_fork(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->bigger->mutex));
	pthread_mutex_unlock(&(philo->smaller->mutex));
}

void eat_meal(t_philo *philo)
{
	write_meal_time(philo, record_philo_action(philo, MSG_EAT));
	philo_usleep(philo->rule->time_to_eat);
	philo->eat_count += 1;
	if (philo->eat_count == philo->rule->option)
		philo->rule->full_philo_count += 1;
}

void sleep_philo(t_philo *philo)
{
	record_philo_action(philo, MSG_SLEEP);
	philo_usleep(philo->rule->time_to_sleep);
}

void think_philo(t_philo *philo)
{
	record_philo_action(philo, MSG_THINK);
	if (philo->rule->odd_flag)
		philo_usleep(philo->rule->time_to_eat);
}

void *philo_routine(void *p)
{
	t_philo *philo = (t_philo *)p;

	if (philo->num % 2 == 0)
	{
		philo_usleep(1);
	}
	write_meal_time(philo,  get_time_in_ms());
	while (philo->rule->dead_exists == FALSE && philo->rule->full_philo_count != philo->rule->num)
	{
		take_fork(philo);
		eat_meal(philo);
		put_fork(philo);
		sleep_philo(philo);
		think_philo(philo);
	}
	return (NULL);
}
