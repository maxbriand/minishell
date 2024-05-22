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
		exe/ft_create_pipes.c \
		exe/ft_set_pipefd.c \
		exe/ft_close_pipes.c \
		\
		builtins/ft_cd.c \
		builtins/ft_echo.c \
		builtins/ft_env.c \
		builtins/ft_exit.c \
		builtins/ft_export.c \
		builtins/ft_pwd.c \
		builtins/ft_unset.c \
		\
		parsing/apply_quote.c \
		parsing/catch_path_env.c \
		parsing/check_arg.c \
		parsing/cmd_arg_join.c \
		parsing/define_cmd.c \
		parsing/define_p.c \
		parsing/define_pcmd_first.c \
		parsing/define_pcmd.c \
		parsing/error_p.c \
		parsing/error_type.c \
		parsing/ft_realloc.c \
		parsing/ft_split_quote_ignore.c \
		parsing/ft_utils.c \
		parsing/ft_verif_access.c \
		parsing/parsing.c \
		parsing/ultimate_free.c \

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
# clear
# ./minishell