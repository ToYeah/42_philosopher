#include "philo.h"

t_time record_philo_action(t_philo *philo, const char *str)
{
	t_time time;

	if (gettimeofday(&time, NULL) != 0)
	{
		//error
		exit(1);
	}
	printf("%ld%d %d %s\n", time.tv_sec, time.tv_usec, philo->num, str);
	return time;
}

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
	if (usleep(philo->rule->time_to_eat) != 0)
	{
		//errpr
		exit(1);
	}
}

void sleep_philo(t_philo *philo)
{
	record_philo_action(philo, MSG_SLEEP);
	if (usleep(philo->rule->time_to_sleep) != 0)
	{
		//errpr
		exit(1);
	}
}

void think_philo(t_philo *philo)
{
	record_philo_action(philo, MSG_THINK);
}

void *philo_routine(void *p)
{
	t_philo *philo = (t_philo *)p;

	while (1)
	{
		set_last_meal_time(philo);
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
