NAME = minishell
CC = cc
FLAGS = -g
LIBFT = libft/libft.a

SRC =	ft_error_p.c\
		ft_ultimate_free.c\
		ft_error_type.c\
		ft_realloc.c\
		ft_split_quote_ignore.c\
		ft_split_separator.c\
		ft_utils.c\
		ft_verif_access.c\
		ft_catch_env.c\
		ft_apply_quote.c\
		ft_parsing.c\
		ft_init_p.c\
		ft_init_pcmd.c\
		ft_define_pcmd_first.c\
		ft_define_pcmd.c\
		ft_check_arg.c\
		ft_cmd_arg_join.c\
		ft_strjoin_free.c\
		ft_remove_element.c\
		ft_strlen_array.c\
		ft_check_quote.c\
		ft_better_strdup.c\
		ft_define_shure_arg.c\
		main.c


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
