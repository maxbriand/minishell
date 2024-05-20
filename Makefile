NAME = minishell 
CC = cc
#FLAGS = -Wall -Werror -Wextra 
LIBFT = libft/libft.a

SRC = 	exe/test.c \
		exe/main.c \
		exe/ft_exe.c \
		exe/ft_exit_failure.c \
		exe/ft_check_path.c \
		exe/ft_utils.c \
		exe/ft_input_redir.c \
		exe/ft_output_redir.c \
		\
		builtins/ft_cd.c \
		builtins/ft_echo.c \
		builtins/ft_env.c \
		builtins/ft_exit.c \
		builtins/ft_export.c \
		builtins/ft_pwd.c \
		builtins/ft_unset.c \

all: $(NAME)

$(NAME): $(LIBFT)
	@$(CC) $(FLAGS) $(SRC) -g -Iinclude -Ilibft/include -Llibft -lft -lreadline -lhistory -lncurses -o $(NAME)

$(LIBFT):
	@make --no-print-directory -C libft

clean:
	@make --no-print-directory clean -C libft

fclean: clean
	@make --no-print-directory fclean -C libft
	@rm -f $(NAME)

re: fclean all
	clear
	./minishell