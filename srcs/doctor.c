#include "philo.h"

t_bool is_philo_arive(t_philo *philo)
{
	long now;
	
	now = get_time_in_ms();
	//printf("%ld, %ld, %ld\n", philo->num, now - philo->last_meal_time, philo->rule->time_to_die);
	if (now - philo->last_meal_time >= philo->rule->time_to_die)
		return FALSE;
	return TRUE;
}

void *doctor_routine(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;

	while (philo->rule->dead_exists == FALSE)
	{
		pthread_mutex_lock(&(philo->rule->right_to_consultation));
		pthread_mutex_lock(&(philo->rule->right_to_output));
		if (is_philo_arive(philo) == FALSE)
		{
			philo->rule->dead_exists = TRUE;
			printf("%ld %ld %s\n", get_time_in_ms(), philo->num, MSG_DIE);
			exit(1);
		}
		else{

		if (usleep(1000) != 0)
		{
				//error
			exit(1);
		}
		}
		pthread_mutex_unlock(&(philo->rule->right_to_output));
		pthread_mutex_unlock(&(philo->rule->right_to_consultation));
	}
	return (NULL);
} 