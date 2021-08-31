#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <limits.h>

#define MSG_FORK "has taken a fork"
#define MSG_EAT "is eating"
#define MSG_SLEEP "is sleeping"
#define MSG_THINK "is thinking"
#define MSG_DIE "died"

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
} t_rule;

t_bool input_arg(t_rule *rule, int argc, char **argv);

t_bool ft_atol_limit(const char *str, long *return_value);
t_bool is_num_str(char *str);
