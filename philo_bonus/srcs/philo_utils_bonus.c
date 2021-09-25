#include "philo_bonus.h"

long get_time_in_us()
{
	t_time now;

	gettimeofday(&now, NULL);
	return ((long)(now.tv_sec * 1000000 + now.tv_usec));
}

long get_time_in_ms()
{
	return(get_time_in_us() / 1000);
}

void philo_usleep(long time)
{
	long start;
	long now;

	start = get_time_in_us();
	while(1)
	{
		now = get_time_in_us();
		if (now - start >= time * 1000)
			break;
		usleep(1000);
	}
}

long record_philo_action(t_philo *philo, const char *str)
{
	long time;

	sem_wait(philo->rule->output_sem);
	time = get_time_in_ms();
	if (philo->rule->dead_exists == FALSE && philo->rule->full_philo_count != philo->rule->num)
		printf("%ld %ld %s\n", time, philo->num, str);
	sem_post(philo->rule->output_sem);
	return time;
}