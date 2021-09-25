#include "philo_bonus.h"

t_bool init_philosophers(t_rule *rule, t_philo **philo)
{
	t_philo* res;
	int i;

	res = malloc(sizeof(t_philo) * rule->num);
	if (!res)
	{
		return (FALSE);
		//error
	}
	i = 0;
	while (i < rule->num)
	{
		res[i].rule = rule;
		res[i].num = i + 1;
		i++;
	}
	*philo = res;
	return (TRUE);
}

t_bool init_forks(t_rule *rule)
{
	rule->fork_sem = sem_open(SEM_FORK, O_CREAT | O_EXCL, S_IRWXU, rule->num);
	if (rule->fork_sem == SEM_FAILED)
		return (FALSE);
	return (TRUE);
}

t_bool init_rule(t_rule *rule, int argc, char **argv)
{
	if (!input_arg(rule, argc, argv))
		return (FALSE);
	if (rule->option_exists)
	{
		rule->option_sem = sem_open(SEM_OPTION, O_CREAT | O_EXCL, S_IRWXU, rule->option);
		if (rule->option_sem == SEM_FAILED)
			return (FALSE);
	}
	rule->dead_sem = sem_open(SEM_DEAD, O_CREAT | O_EXCL, S_IRWXU, rule->num);
	if (rule->dead_sem == SEM_FAILED)
		return (FALSE);
	rule->output_sem = sem_open(SEM_OUTPUT, O_CREAT | O_EXCL, S_IRWXU, 1);
	if (rule->output_sem == SEM_FAILED)
		return (FALSE);

	rule->dead_exists = FALSE;
	rule->full_philo_count = 0;
	rule->odd_flag = TRUE;
	if (rule->num % 2 == 0)
		rule->odd_flag = FALSE;
	return (TRUE);
}

void delete_semaphores(void)
{
	sem_unlink(SEM_OPTION);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_OUTPUT);
}

int main(int argc, char **argv)
{
	t_rule rule;
	t_philo *philo;

	delete_semaphores();
	if (!init_rule(&rule, argc, argv))
		return (1);
	if (!init_forks(&rule))
		return (1);
	if (!init_philosophers(&rule, &philo))
		return (1);
	start_philos(&rule, philo);
	delete_semaphores();
}