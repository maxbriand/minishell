NAME = minishell
CC = cc
#FLAGS = -Wall -Werror -Wextra
LIBFT = libft/libft.a

SRC = 	src/parsing.c\
		src/define_p.c\
		src/main.c\
		src/ultimate_free.c\
		src/error_type.c


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
