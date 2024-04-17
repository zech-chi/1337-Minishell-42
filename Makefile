NAME = minishell

RM = rm -f

CC = cc

CFLAGS = -Wall -Wextra -Werror

READLINEFLAG = -lreadline

READLINE_L = $(shell brew --prefix readline)/lib
READLINE_I = $(shell brew --prefix readline)/include

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
		parsing/token_lst_2.c\
		parsing/tree.c \
		parsing/fix_lst_perfix.c\
		parsing/here_doc.c\
		parsing/here_doc_2.c\
		parsing/grpg.c\
		parsing/ft_split.c\
		main/main.c \
		execution/execute/execute.c \
		execution/execute/execute_builtins.c \
		execution/execute/execute_cmd.c \
		execution/execute/execute_pipe.c \
		execution/execute/execute_redirection_out.c \
		execution/execute/execute_redirection_in.c \
		execution/builtins/cd.c \
		execution/builtins/echo.c \
		execution/builtins/env.c \
		execution/builtins/exit.c \
		execution/builtins/export.c \
		execution/builtins/export_help.c \
		execution/builtins/pwd.c \
		execution/builtins/unset.c \
		execution/env/env_add.c \
		execution/env/env_clear.c \
		execution/env/env_create.c \
		execution/env/env_create_2d.c \
		execution/env/env_delete.c \
		execution/env/env_duplicate.c \
		execution/env/env_print.c \
		execution/env/env_search.c \
		execution/env/env_size.c \
		execution/env/env_update.c \
		execution/expanding/expand.c \
		execution/expanding/expand_dollar.c \
		execution/expanding/expand_tools.c \
		execution/expanding/wildcard.c \
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
		execution/tools/putstr_fd.c \
		execution/tools/free_2d_char.c \
		execution/tools/atoi.c \
		execution/tools/strlcpy.c \
		execution/tools/strlcat.c \
		herdoc/herdoc.c

OBJS = $(SRCS:.c=.o)

all: print_header $(NAME)

%.o: %.c header/minishell_common.h header/minishell_execution.h header/minishell_parsing.h
	$(CC) $(CFLAGS) -I $(READLINE_I) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS)  $^ -o $@ -L $(READLINE_L) $(READLINEFLAG)

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