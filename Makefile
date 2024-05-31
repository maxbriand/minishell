NAME = minishell
CC = cc
#FLAGS = -Wall -Werror -Wextra
LIBFT = libft/libft.a

SRC =	main.c \
		exe/test.c \
		exe/ft_exe.c \
		exe/ft_exit_failure.c \
		exe/ft_check_path.c \
		exe/ft_utils.c \
		exe/ft_input_redir.c \
		exe/ft_output_redir.c \
		exe/ft_create_pipes.c \
		exe/ft_set_pipefd.c \
		exe/ft_close_pipes.c \
		exe/ft_builtins_exe.c \
		\
		builtins/ft_cd.c \
		builtins/ft_echo.c \
		builtins/ft_env.c \
		builtins/ft_exit.c \
		builtins/ft_export.c \
		builtins/ft_pwd.c \
		builtins/ft_unset.c \
		builtins/ft_butils.c \
		\
		parsing/ft_apply_quote.c \
		parsing/ft_catch_env.c \
		parsing/ft_check_arg.c \
		parsing/ft_cmd_arg_join.c \
		parsing/ft_define_cmd.c \
		parsing/ft_define_p.c \
		parsing/ft_define_pcmd_first.c \
		parsing/ft_define_pcmd.c \
		parsing/ft_error_p.c \
		parsing/ft_error_type.c \
		parsing/ft_realloc.c \
		parsing/ft_split_quote_ignore.c \
		parsing/ft_utils.c \
		parsing/ft_verif_access.c \
		parsing/ft_parsing.c \
		parsing/ft_ultimate_free.c \
		parsing/ft_split_separator.c \
		parsing/ft_strjoin_free.c \
		parsing/ft_better_strdup.c \
		parsing/ft_check_quote.c \
		parsing/ft_define_shure_arg.c \
		parsing/ft_strlen_array.c \


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
#./minishell

rev: fclean all
	valgrind --tool=memcheck --track-origins=yes --show-leak-kinds=all --leak-check=full --track-fds=yes --trace-children=yes -s --suppressions=valgrind.supp ./minishell

rew: fclean all
