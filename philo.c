#include "philo.h"

t_fork *init_forks(int count)
{
	t_fork *res;
	int i;

	res = malloc(sizeof(t_fork) * count);
	if (!res)
	{
		//error
		exit(1);
	}
	i = 0;
	while (i < count)
	{
		res[i].weight = i;
		if (pthread_mutex_init(&(res[i].mutex), NULL) != 0)
		{
			//error
			exit(1);
		}
		i++;
	}
	return res;
}

void init_philosophers_fork(t_philo *philo, t_fork *forks, int count)
{
	int fork_index;

	fork_index = philo->num - 1;
	if (fork_index < 0)
		fork_index = count;
	if (fork_index < philo->num)
	{
		philo->bigger = &(forks[philo->num]);
		philo->smaller = &(forks[fork_index]);
	}
	else
	{
		philo->bigger = &(forks[fork_index]);
		philo->smaller = &(forks[philo->num]);
	}
}

t_philo *init_philosophers(int count, t_fork *forks, t_rule *rule)
{
	t_philo *res;
	int i;

	res = malloc(sizeof(t_philo) * count);
	if (!res)
	{
		//error
		exit(1);
	}
	i = 0;
	while (i < count)
	{
		res[i].num = i + 1;
		res[i].rule = rule;
		init_philosophers_fork(&(res[i]), forks, count);
		if (pthread_create(&(res[i].thread), NULL, philo_routine, &(res[i])) != 0)
		{
			//error
			exit(1);
		}
		pthread_detach(res[i].thread);
		i++;
	}
	return res;
}

int main(int argc, char **argv)
{
	int num_of_philo = 3;

	t_philo *philosophers;
	t_fork *forks;
	t_rule rule;

	input_arg(&rule, argc, argv);
	forks = init_forks(rule.num);
	philosophers = init_philosophers(rule.num, forks, &(rule));
	while (1)
		;
}