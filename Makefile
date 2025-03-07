NAME = minishell
CC = cc
FLAGS = -Wall -Werror -Wextra
LIBFT = libft/libft.a

SRC =	main.c \
		exe/ft_create_heredocs.c \
		exe/ft_before_exe.c \
		exe/ft_exe_1builtin.c \
		exe/ft_exe_in_fork.c \
		exe/ft_exe.c \
		exe/ft_exit_failure.c \
		exe/ft_exit_failure2.c \
		exe/ft_check_path.c \
		exe/ft_utils.c \
		exe/ft_input_redir.c \
		exe/ft_output_redir.c \
		exe/ft_create_pipes.c \
		exe/ft_set_pipefd.c \
		exe/ft_close_pipes.c \
		exe/ft_builtins_exe.c \
		exe/ft_signals.c \
		\
		builtins/ft_cd.c \
		builtins/ft_echo.c \
		builtins/ft_env.c \
		builtins/ft_exit.c \
		builtins/ft_export.c \
		builtins/ft_export2.c \
		builtins/ft_export3.c \
		builtins/ft_pwd.c \
		builtins/ft_unset.c \
		builtins/ft_butils.c \
		\
		parsing/ft_init_env.c \
		parsing/ft_init_shlvl.c \
		parsing/ft_init_export.c \
		parsing/ft_apply_quote.c \
		parsing/ft_file_error.c \
		parsing/ft_catch_env.c \
		parsing/ft_check_arg.c \
		parsing/ft_cmd_arg_join.c \
		parsing/ft_init_pcmd.c \
		parsing/ft_init_p.c \
		parsing/ft_define_pcmd_first.c \
		parsing/ft_define_pcmd.c \
		parsing/ft_split_quote_utils.c \
		parsing/ft_error_type.c \
		parsing/ft_realloc.c \
		parsing/ft_split_quote_ignore.c \
		parsing/ft_utils.c \
		parsing/ft_parsing.c \
		parsing/ft_ultimate_free.c \
		parsing/ft_split_separator.c \
		parsing/ft_strjoin_free.c \
		parsing/ft_better_strdup.c \
		parsing/ft_check_quote.c \
		parsing/ft_define_shure_arg.c \
		parsing/ft_strlen_array.c \
		parsing/ft_check_arg_op.c \
		parsing/ft_remove_element.c \
		parsing/ft_split_separator_utils.c \
		parsing/ft_free_array.c \
		parsing/ft_hd_set.c \
		parsing/ft_declare_utils.c \
		parsing/ft_free_utils.c \
		parsing/ft_free_p.c \
		parsing/ft_is_error.c \
		
OBJ = $(patsubst %.c, %.o, $(SRC))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -Llibft -lft -lreadline -lhistory -lncurses -o $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -g -c $< -o $@ -Iinclude -Ilibft/include 

$(LIBFT):
	@make --no-print-directory -C libft

clean:
	@make --no-print-directory clean -C libft
	@rm -f */*.o
	@rm -f *.o

fclean: clean
	@make --no-print-directory fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all re fclean clean