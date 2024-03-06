NAME = minishell

RM = rm -f

CC = cc

CFLAGS = -Wall -Wextra -Werror

READLINEFLAG = -lreadline

SRCS =	main.c  tree.c  token_lst.c ft_strtrim.c ft_strlcpy.c ft_stdup.c ft_strchr.c ft_strlen.c linked_lst.c oltils.c linked_lst2.c infix_to_Postfix.c

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