#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct s_philo t_philo;

typedef struct s_fork t_fork;

struct s_fork
{
	int weight;
	pthread_mutex_t mutex;
};

struct s_philo
{
	t_fork *left;
	t_fork *right;
	pthread_t thread;
	int num;
};

void *philo_routine(void *p)
{
	t_philo *philo = (t_philo *)p;
	printf("hello, philo%d", philo->num);
	return (NULL);
}

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
	int right_index;

	right_index = philo->num - 1;
	if (right_index < 0)
		right_index = count;
	philo->left = &(forks[philo->num]);
	philo->right = &(forks[right_index]);
}

t_philo *init_philosophers(int count, t_fork *forks)
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

int main(int argc, char **argv)
{
	int num_of_philo = 3;

	t_philo *philosophers;
	t_fork *forks;

	forks = init_forks(num_of_philo);
	philosophers = init_philosophers(num_of_philo, forks);
}