#include "philo.h"

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

	pthread_mutex_lock(&(philo->rule->right_to_output));
	time = get_time_in_ms();
	printf("%ld %ld %s\n", time, philo->num, str);
	pthread_mutex_unlock(&(philo->rule->right_to_output));
	return time;
}