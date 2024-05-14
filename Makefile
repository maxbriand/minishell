NAME = minishell
CC = cc
#FLAGS = -Wall -Werror -Wextra
LIBFT = libft/libft.a

SRC =	mini_libft/error_p.c\
		mini_libft/ultimate_free.c\
		mini_libft/error_type.c\
		mini_libft/ft_realloc.c\
		src/parsing.c\
		src/define_p.c\
		src/define_first_arg.c\
		src/main.c


all: $(NAME)

$(NAME): $(LIBFT)
	@$(CC) $(FLAGS) $(SRC) -Iinclude -Ilibft/include -Llibft -lft -lreadline -lhistory -o $(NAME)

$(LIBFT):
	@make --no-print-directory -C libft

clean:
	@make --no-print-directory clean -C libft

fclean: clean
	@make --no-print-directory fclean -C libft
	@rm -f $(NAME)

re: fclean all
