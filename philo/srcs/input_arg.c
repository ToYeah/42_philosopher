#include "philo.h"

t_bool	input_num_arg(long *dest, char *str)
{
	if (is_num_str(str)
		&& ft_atol_limit(str, dest))
	{
		return (TRUE);
	}
	return (FALSE);
}

t_bool	input_option_arg(t_rule *rule, long argc, char **argv)
{
	if (argc != 6)
	{
		rule->option_exists = FALSE;
		return (TRUE);
	}
	rule->option_exists = TRUE;
	return (input_num_arg(&(rule->option), argv[5]));
}

t_bool	input_arg(t_rule *rule, int argc, char **argv)
{
	if ((argc != 5 && argc != 6)
		|| !input_num_arg(&(rule->num), argv[1])
		|| !input_num_arg(&(rule->time_to_die), argv[2])
		|| !input_num_arg(&(rule->time_to_eat), argv[3])
		|| !input_num_arg(&(rule->time_to_sleep), argv[4])
		|| !input_option_arg(rule, argc, argv))
	{
		printf("Invalid argument format.\n");
		return (FALSE);
	}
	return (TRUE);
}
