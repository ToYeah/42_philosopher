#include "philo_bonus.h"

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
