# minishell
8rd project of 42 school

#valgrind --tool=memcheck --track-origins=yes --show-leak-kinds=all --leak-check=full --track-fds=yes --trace-children=yes -s --suppressions=valgrind.supp ./minishell

Galaad
echo -awduidhaw test
echo -nnnnnn waefaw -n
<< d | << w cat | cat leaks
"" " -> dquotes not closed (same with simple quote)
env -i valgrind ./minishell + export -> segfault
<< d cat test + cat test -> leak

Max
ctrl c heredoc


PATH=$PATH:$PWD -> minishell dans autre directory fonctionne pas0
