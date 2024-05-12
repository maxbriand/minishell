NAME = minishell 
CC = cc
#FLAGS = -Wall -Werror -Wextra 
LIBFT = libft/libft.a

SRC = 	exe/main.c \
		exe/ft_exe.c \
		\
		builtins/ft_cd.c \

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