/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:02:39 by totaisei          #+#    #+#             */
/*   Updated: 2021/11/24 19:02:58 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_DIE "died"

typedef struct s_philo	t_philo;

typedef struct s_fork	t_fork;

typedef enum e_bool
{
	FALSE,
	TRUE
}						t_bool;

typedef struct s_rule
{
	long			num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	t_bool			option_exists;
	long			option;
	pthread_mutex_t	right_to_output;
	pthread_mutex_t	right_to_consultation;
	t_bool			dead_exists;
	t_bool			odd_flag;
	long			full_philo_count;
}						t_rule;

struct s_fork
{
	long			weight;
	pthread_mutex_t	mutex;
};

struct s_philo
{
	t_fork			*bigger;
	t_fork			*smaller;
	pthread_t		thread;
	pthread_t		doctor;
	long			last_meal_time;
	long			num;
	t_rule			*rule;
	long			eat_count;
	pthread_mutex_t	right_to_meal_time;
};

void	*philo_routine(void *p);

t_bool	input_arg(t_rule *rule, int argc, char **argv);

t_bool	ft_atol_limit(const char *str, long *return_value);
t_bool	is_num_str(char *str);

long	get_time_in_us(void);
long	get_time_in_ms(void);
void	philo_usleep(long time);
long	record_philo_action(t_philo *philo, const char *str);
void	*doctor_routine(void *p);

void	write_meal_time(t_philo *philo, long time);
long	read_meal_time(t_philo *philo);

void	take_fork(t_philo *philo);
void	put_fork(t_philo *philo);
void	eat_meal(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	think_philo(t_philo *philo);

t_fork	*init_forks(long count);
void	init_philosophers_fork(t_philo *philo, t_fork *forks);
t_philo	*init_philosophers(long count, t_fork *forks, t_rule *rule);
t_bool	init_rule(t_rule *rule, int argc, char **argv);
void	join_philosophers(t_philo *philos, long count);

#endif