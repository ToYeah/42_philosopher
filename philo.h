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
	t_fork *bigger;
	t_fork *smaller;
	pthread_t thread;
	int num;
};
