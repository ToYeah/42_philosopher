#include "philo_bonus.h"

void wait_philos(t_rule *rule)
{
	
	int i;
	int status;

	i = 0;
	while(i < rule->num)
	{
		waitpid(0, &status, 0);
		if (WEXITSTATUS(status))
		{
			printf("Child process has error\n");
			exit(1);
		}
		i++;
	}
}

void *observe_option(void *p)
{
	t_rule *rule;
	long i;

	rule = (t_rule *)p;
	i = 0;
	while(i < rule->num)
	{
		sem_wait(rule->option_sem);
		i++;
	}
	sem_wait(rule->output_sem);
	sem_post(rule->dead_sem);
	return (NULL);
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
	if (rule->option_exists)
	{
		if (pthread_create(&(rule->option_observer), NULL, observe_option, rule))
		{
			//error
			exit(1);
		}
	}
	wait_philos(rule);
}