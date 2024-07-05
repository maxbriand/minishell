NAME = minishell
CC = cc
FLAGS = -g -Wall -Werror -Wextra
LIBFT = libft/libft.a

SRC =	ft_ultimate_free.c\
		ft_error_type.c\
		ft_realloc.c\
		ft_split_quote_ignore.c\
		ft_split_separator.c\
		ft_utils.c\
		ft_catch_env.c\
		ft_apply_quote.c\
		ft_parsing.c\
		ft_init_p.c\
		ft_init_pcmd.c\
		ft_define_pcmd_first.c\
		ft_define_pcmd.c\
		ft_check_arg.c\
		ft_check_arg_op.c\
		ft_cmd_arg_join.c\
		ft_strjoin_free.c\
		ft_remove_element.c\
		ft_strlen_array.c\
		ft_check_quote.c\
		ft_better_strdup.c\
		ft_define_shure_arg.c\
		ft_init_export.c\
		ft_file_error.c\
		ft_split_separator_utils.c\
		ft_split_quote_utils.c \
		ft_hd_set.c \
		ft_free_array.c \
		ft_free_utils.c \
		ft_init_utils.c \
		ft_free_p.c \
		ft_define_outfile.c \
		main.c


all: $(NAME)

$(NAME): $(LIBFT)
	@$(CC) $(FLAGS) $(SRC) -g -Iinclude -Ilibft/include -Llibft -lft -lreadline -lhistory -lncurses -o $(NAME)

$(LIBFT):
	@make --no-print-directory -C libft

rev: fclean all
	valgrind --tool=memcheck --track-origins=yes --show-leak-kinds=all --leak-check=full --track-fds=yes --trace-children=yes -s --suppressions=valgrind.supp ./minishell

clean:
	@make --no-print-directory clean -C libft

fclean: clean
	@make --no-print-directory fclean -C libft
	@rm -f $(NAME)

re: fclean all
