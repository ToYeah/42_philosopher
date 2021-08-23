#include "philo.h"

t_bool is_philo_arive(t_philo *philo)
{
	long now;
	
	now = get_time_in_ms();
	if (now - philo->last_meal_time >= philo->rule->time_to_die)
		return FALSE;
	return TRUE;
}
