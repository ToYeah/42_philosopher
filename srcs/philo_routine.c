#include "philo.h"

void take_fork(t_philo *philo, t_bool is_bigger)
{

	if (is_bigger == TRUE)
		pthread_mutex_lock(&(philo->bigger->mutex));
	else
		pthread_mutex_lock(&(philo->smaller->mutex));
	record_philo_action(philo, MSG_FORK);
}

void put_fork(t_philo *philo, t_bool is_bigger)
{
	if (is_bigger == TRUE)
		pthread_mutex_unlock(&(philo->bigger->mutex));
	else
		pthread_mutex_unlock(&(philo->smaller->mutex));
}

void eat_meal(t_philo *philo)
{
	philo->last_meal_time = record_philo_action(philo, MSG_EAT);
	philo_usleep(philo->rule->time_to_eat);
}

void sleep_philo(t_philo *philo)
{
	record_philo_action(philo, MSG_SLEEP);
	philo_usleep(philo->rule->time_to_sleep);
}

void think_philo(t_philo *philo)
{
	record_philo_action(philo, MSG_THINK);
}

void *philo_routine(void *p)
{
	t_philo *philo = (t_philo *)p;

	philo->last_meal_time = get_time_in_ms();
	while (philo->rule->dead_exists == FALSE)
	{
		take_fork(philo, TRUE);
		take_fork(philo, FALSE);
		eat_meal(philo);
		put_fork(philo, FALSE);
		put_fork(philo, TRUE);
		sleep_philo(philo);
		think_philo(philo);
	}
	return (NULL);
}
