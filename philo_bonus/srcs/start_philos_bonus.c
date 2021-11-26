/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philos_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:06:03 by totaisei          #+#    #+#             */
/*   Updated: 2021/11/26 19:25:55 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_philos(t_rule *rule)
{
	int	i;
	int	status;

	i = 0;
	while (i < rule->num)
	{
		waitpid(0, &status, 0);
		if (WEXITSTATUS(status))
		{
			printf("Child process has error\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	*observe_option(void *p)
{
	t_rule	*rule;
	long	i;

	rule = (t_rule *)p;
	i = 0;
	while (i < rule->num)
	{
		sem_wait(rule->option_sem);
		i++;
	}
	sem_wait(rule->output_sem);
	sem_post(rule->dead_sem);
	return (NULL);
}

void	start_option(t_rule *rule)
{
	if (rule->option_exists)
	{
		if (pthread_create(&(rule->option_observer),
				NULL, observe_option, rule))
		{
			printf("%s\n", ERROR_MESSAGE);
			exit(EXIT_FAILURE);
		}
		pthread_detach(rule->option_observer);
	}
}

void	start_philos(t_rule *rule, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < rule->num)
	{
		philo[i].pid = fork();
		if (philo[i].pid == -1)
		{
			printf("%s\n", ERROR_MESSAGE);
			exit(EXIT_FAILURE);
		}
		if (philo[i].pid == 0)
		{
			philo_routine(&(philo[i]));
		}
		i++;
	}
	start_option(rule);
	wait_philos(rule);
}
