SRCS := main.c check_args.c philo_utils.c init.c philo_action.c threads.c monitor.c

OBJS := $(SRCS:.c=.o)

DEPS := $(OBJS:.o=.d)

CC := gcc

CFLAGS := -Werror -Wall -Wextra -g3

CPPFLAGS := -MMD -MP

NAME = philo

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

-include $(DEPS)

clean :
	rm -f $(OBJS) $(DEPS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re 
