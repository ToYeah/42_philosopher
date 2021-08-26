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

void init_philosophers_fork(t_philo *philo, t_fork *forks)
{
	if (philo->num == 1)
	{
		philo->smaller = &(forks[philo->num - 1]);
		philo->bigger = &(forks[philo->rule->num - 1]);
	}
	else
	{
		philo->smaller = &(forks[philo->num - 2]);
		philo->bigger = &(forks[philo->num - 1]);
	}
}

t_philo *init_philosophers(long count, t_fork *forks, t_rule *rule)
{
	t_philo *res;
	long i;
	int create_res;

	res = malloc(sizeof(t_philo) * count);
	create_res = 0;
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
		res[i].last_meal_time = get_time_in_ms();
		init_philosophers_fork(&(res[i]), forks);
		create_res += pthread_create(&(res[i].thread), NULL, philo_routine, &(res[i]));
		create_res += pthread_create(&(res[i].doctor), NULL, doctor_routine, &(res[i]));
		if (create_res != 0)
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
	int create_res;

	create_res = 0;
	input_arg(rule, argc, argv);
	rule->odd_flag = TRUE;
	if (rule->num % 2 == 0)
		rule->odd_flag = FALSE;
	create_res += pthread_mutex_init(&(rule->right_to_output), NULL);
	create_res += pthread_mutex_init(&(rule->right_to_consultation), NULL);
	if (create_res != 0)
	{
		//error
		exit(1);
	}
	rule->dead_exists = FALSE;
}

void join_philosophers(t_philo *philos, long count)
{
	long i;

	i = 0;
	while (i < count)
	{
		pthread_join(philos[i].thread, NULL);
		pthread_join(philos[i].doctor, NULL);
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