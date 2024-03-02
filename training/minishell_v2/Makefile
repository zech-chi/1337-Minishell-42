NAME = minishell

RM = rm -f

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

READLINEFLAG = -lreadline

SRCS =	main.c \
		libft_tools/strlen.c \
		libft_tools/split.c \
		libft_tools/strcmp.c \
		libft_tools/strdup.c \
		libft_tools/strjoin.c \
		libft_tools/strncmp.c \
		libft_tools/strtrim.c \
		builtins/env.c \
		tree/tree.c

OBJS = $(SRCS:.c=.o)

all: print_header $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(READLINEFLAG) $^ -o $@

%.o: %.c mandatory/minishell.h
	$(CC) $(CFLAGS) $(READLINEFLAG) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

print_header:
	@echo "\033[38;2;116;226;145m"
	@echo "███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░"
	@echo "████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░"
	@echo "██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░"
	@echo "██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░"
	@echo "██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗"
	@echo "╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝"
	@echo "\033[38;2;89;180;195m"
	@echo "                       by: ymomen, zech-chi                       "
	@echo "\033[0m"

.PHONY: all clean fclean re