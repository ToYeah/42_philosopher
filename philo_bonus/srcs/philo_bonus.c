#include "philo_bonus.h"

t_bool init_rule(t_rule *rule, int argc, char **argv)
{
	if (!input_arg(rule, argc, argv))
	{
		return (FALSE);
	}
	rule->dead_exists = FALSE;
	rule->full_philo_count = 0;
	rule->odd_flag = TRUE;
	if (rule->num % 2 == 0)
		rule->odd_flag = FALSE;
	return (TRUE);
}

int main(int argc, char **argv)
{
	t_rule rule;

	if (!init_rule(&rule, argc, argv))
		return (1);
}