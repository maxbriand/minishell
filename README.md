# minishell
8rd project of 42 school

#valgrind --tool=memcheck --track-origins=yes --show-leak-kinds=all --leak-check=full --track-fds=yes --trace-children=yes -s --suppressions=valgrind.supp ./minishell

echo -awduidhaw test
echo -nnnnnn waefaw -n
ctrl c heredoc
echo "	" | cat -e -> leak
"' quote not close -> leak
env -i ./minishell / export -> segfault
unset home -> cd -> leak
PATH=$PATH:$PWD -> minishell dans autre directory fonctionne pas0
heredoc \n aussi leak
cat | cat | ls a verif parcec que bzr