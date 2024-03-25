NAME = minishell

RM = rm -f

CC = cc

CFLAGS = -Wall -Wextra -Werror

READLINEFLAG = -lreadline


#READLINE_L = $(shell brew --prefix readline)/lib
#READLINE_I = $(shell brew --prefix readline)/include

SRCS =	parsing/ft_stdup.c \
		parsing/ft_putstr_fd.c \
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
		parsing/fix_lst_perfix.c\
		main/main.c \
		execution/execute/execute.c \
		execution/execute/execute_pipe.c \
		execution/execute/execute_builtins.c \
		execution/execute/execute_redirection_out.c \
		execution/builtins/echo.c \
		execution/builtins/cd.c \
		execution/builtins/pwd.c \
		execution/builtins/export.c \
		execution/builtins/unset.c \
		execution/builtins/exit.c \
		execution/builtins/env.c \
		execution/env/env1.c \
		execution/env/env2.c \
		execution/expanding/expand.c \
		execution/expanding/expand_tools.c \
		execution/expanding/print_lst.c \
		execution/tools/itoa.c \
		execution/tools/linked_list.c \
		execution/tools/split.c \
		execution/tools/strcmp.c \
		execution/tools/strdup.c \
		execution/tools/strjoin.c \
		execution/tools/strlen.c \
		execution/tools/strncmp.c \
		execution/tools/strtrim.c \
		execution/tools/print_error.c \
		execution/tools/isspace.c \
		execution/tools/substr.c \
		execution/tools/putstr_fd.c 

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