#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_philo t_philo;

typedef struct s_fork t_fork;

typedef struct timeval t_time;

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
	t_time last_meal_time;
	int num;
};

void *philo_routine(void *p);