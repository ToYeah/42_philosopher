#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philosophers;
	t_fork	*forks;
	t_rule	rule;

	if (!init_rule(&rule, argc, argv))
		return (1);
	forks = init_forks(rule.num);
	if (!forks)
		return (1);
	philosophers = init_philosophers(rule.num, forks, &(rule));
	if (!philosophers)
		return (1);
	join_philosophers(philosophers, rule.num);
	free(philosophers);
	free(forks);
}
