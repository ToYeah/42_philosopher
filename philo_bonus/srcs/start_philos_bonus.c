#include "philo_bonus.h"


void philo_routine(t_philo *philo)
{
	printf("hello %ld\n", philo->num);
	exit(0);
}

void wait_philos(t_rule *rule, t_philo *philo)
{
	
	int i;
	int status;

	i = 0;
	while(i < rule->num)
	{
		waitpid(philo->pid, &status, 0);
		i++;
	}
}

void start_philos(t_rule *rule, t_philo *philo)
{
	int i;

	i = 0;
	while(i < rule->num)
	{
		philo[i].pid = fork();
		if (philo[i].pid == -1)
		{
			//error
			exit(1);
		}
		if (philo[i].pid == 0)
		{
			philo_routine(&(philo[i]));
		}
		i++;
	}
	wait_philos(rule, philo);
}
