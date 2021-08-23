#include "philo.h"

t_fork *init_forks(long count)
{
	t_fork *res;
	long i;

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

void init_philosophers_fork(t_philo *philo, t_fork *forks, long count)
{
	long fork_index;

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

t_philo *init_philosophers(long count, t_fork *forks, t_rule *rule)
{
	t_philo *res;
	long i;

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
		i++;
	}
	return res;
}

void init_rule(t_rule *rule, int argc, char **argv)
{
	input_arg(rule, argc, argv);
	if (pthread_mutex_init(&(rule->right_to_output), NULL) != 0)
	{
		//error
		exit(1);
	}
}

void join_philosophers(t_philo *philos, long count)
{
	long i;

	i = 0;
	while (i < count)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_philo *philosophers;
	t_fork *forks;
	t_rule rule;

	init_rule(&rule, argc, argv);
	forks = init_forks(rule.num);
	philosophers = init_philosophers(rule.num, forks, &(rule));
	join_philosophers(philosophers, rule.num);
}