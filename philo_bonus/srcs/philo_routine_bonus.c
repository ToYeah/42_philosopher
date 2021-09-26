#include "philo_bonus.h"

void take_fork(t_philo *philo)
{
	sem_wait(philo->rule->fork_sem);
	record_philo_action(philo, MSG_FORK);
	sem_wait(philo->rule->fork_sem);
	record_philo_action(philo, MSG_FORK);
}

void put_fork(t_philo *philo)
{
	sem_post(philo->rule->fork_sem);
	sem_post(philo->rule->fork_sem);
}

void eat_meal(t_philo *philo)
{
	philo->last_meal_time = record_philo_action(philo, MSG_EAT);
	philo_usleep(philo->rule->time_to_eat);
	philo->eat_count += 1;
	if (philo->rule->option_exists && philo->eat_count == philo->rule->option)
		sem_post(philo->rule->option_sem);
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

void philo_routine(t_philo *philo)
{
	if (pthread_create(&(philo->nurse), NULL, nurse_routine, philo))
	{
		//error
		exit(1);
	}
	if (pthread_create(&(philo->doctor), NULL, doctor_routine, philo))
	{
		//error
		exit(1);
	}
	if (philo->num % 2 == 0)
	{
		philo_usleep(1);
	}
	philo->last_meal_time = get_time_in_ms();
	while (1)
	{
		take_fork(philo);
		eat_meal(philo);
		put_fork(philo);
		sleep_philo(philo);
		think_philo(philo);
	}
	exit(0);
}
