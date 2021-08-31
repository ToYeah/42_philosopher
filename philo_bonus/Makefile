NAME		= philo_bonus
SRCS		= srcs/input_arg_utils.c srcs/input_arg.c srcs/philo_bonus.c 
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -pthread
OBJS		= $(SRCS:.c=.o)
OBJS_DIR	= objs
INCLUDES	= -I includes

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

$(NAME)	: $(OBJS) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

srcs: 
	sed -i -e "s|^SRCS\t\t=.*|SRCS\t\t= `find * -name "*.c" | tr '\n' ' '`|g" ./Makefile

.PHONY: all clean fclean re srcs