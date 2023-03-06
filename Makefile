SRCS=		srcs/main.c		\
		srcs/check_args.c 	\
		srcs/failure.c		\
		srcs/init_parameters.c 	\
		srcs/monitor.c		\
		srcs/philo_utils_1.c	\
		srcs/philo_utils_2.c	\
		srcs/routine.c		\
		srcs/timing.c

OBJS=		$(SRCS:.c=.o)

RM=		rm -f

CFLAGS=		 -pthread -Wall -Wextra -Werror

NAME=		philo

CC=		cc

all:	 $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $^

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
