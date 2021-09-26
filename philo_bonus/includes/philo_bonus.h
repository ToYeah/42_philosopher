#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/wait.h>

#define MSG_FORK "has taken a fork"
#define MSG_EAT "is eating"
#define MSG_SLEEP "is sleeping"
#define MSG_THINK "is thinking"
#define MSG_DIE "died"
#define SEM_OPTION "/option"
#define SEM_FORK "/fork"
#define SEM_DEAD "/dead"
#define SEM_OUTPUT "/output"
#define SEM_CONSUL "/consul"

typedef struct s_philo t_philo;

typedef struct s_fork t_fork;

typedef struct timeval t_time;

typedef enum e_bool
{
	FALSE,
	TRUE
} t_bool;

typedef struct s_rule
{
	long num;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	t_bool option_exists;
	long option;
	t_bool  dead_exists;
	t_bool odd_flag;
	long full_philo_count;
	sem_t *option_sem;
	sem_t *fork_sem;
	sem_t *dead_sem;
	sem_t *output_sem;
	sem_t *consul_sem;
} t_rule;


struct s_philo
{
	pthread_t doctor;
	pthread_t nurse;
	long last_meal_time;
	long num;
	t_rule *rule;
	long eat_count;
	pid_t pid;
};

t_bool input_arg(t_rule *rule, int argc, char **argv);

t_bool ft_atol_limit(const char *str, long *return_value);
t_bool is_num_str(char *str);
void start_philos(t_rule *rule, t_philo *philo);
long get_time_in_us();
long get_time_in_ms();
void philo_usleep(long time);
long record_philo_action(t_philo *philo, const char *str);
void philo_routine(t_philo *philo);
void *nurse_routine(void *p);
void *doctor_routine(void *p);