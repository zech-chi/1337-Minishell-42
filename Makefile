NAME = minishell

RM = rm -f

CC = cc

CFLAGS = -Wall -Wextra -Werror

READLINEFLAG = -lreadline

SRCS =	parsing/ft_stdup.c \
		parsing/ft_strchr.c \
		parsing/ft_strjoin.c \
		parsing/ft_strlcpy.c \
		parsing/ft_strlen.c \
		parsing/ft_strtrim.c \
		parsing/infix_to_Postfix.c \
		parsing/linked_lst.c \
		parsing/linked_lst2.c \
		parsing/oltils.c \
		parsing/print_tree.c \
		parsing/token_lst.c \
		parsing/tree.c \
		main/main.c \
		execution/execute/execute.c \
		execution/builtins/echo.c \
		execution/builtins/env.c \
		execution/expanding/expand.c \
		execution/libft_tools/itoa.c \
		execution/libft_tools/linked_list.c \
		execution/libft_tools/split.c \
		execution/libft_tools/strcmp.c \
		execution/libft_tools/strdup.c \
		execution/libft_tools/strjoin.c \
		execution/libft_tools/strlen.c \
		execution/libft_tools/strncmp.c \
		execution/libft_tools/strtrim.c

OBJS = $(SRCS:.c=.o)

all: print_header $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(READLINEFLAG) $^ -o $@

%.o: %.c minishell_v1.h 
	$(CC) $(CFLAGS) -c $< -o $@

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