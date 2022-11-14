NAME = philo

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRCS_DIR = srcs
LIBFT_DIR = $(SRCS_DIR)/libft
PHILOS_DIR = philos

SRCS = main.c \
		$(LIBFT_DIR)/ft_atoi.c \
		$(LIBFT_DIR)/ft_calloc.c \
		$(LIBFT_DIR)/ft_isdigit.c \
		$(LIBFT_DIR)/ft_isspace.c \
		$(LIBFT_DIR)/ft_strlen.c \
		$(PHILOS_DIR)/philos.c \
		$(PHILOS_DIR)/routine.c \
		$(PHILOS_DIR)/time.c \
		$(PHILOS_DIR)/time_converter.c \
		$(PHILOS_DIR)/supervisor.c \
		$(PHILOS_DIR)/remove.c \
		$(PHILOS_DIR)/make.c \
		$(PHILOS_DIR)/can.c \
		$(PHILOS_DIR)/print.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -pthread $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re