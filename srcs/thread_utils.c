#include "philo.h"

long get_time_in_us()
{
	t_time now;

	if (gettimeofday(&now, NULL))
	{
		//error
		exit(1);
	}
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

	start = get_time_in_ms();
	while(1)
	{
		now = get_time_in_ms();
		if (now - start >= time)
			break;
		if (usleep(1000) != 0)
		{
				//errpr
			exit(1);
		}
	}
}