#include "minishell.h"

int main()
{
    char    *line;

    char *cmdline = ft_strjoin(getenv("USER"), "$>");
    while (1)
    {
        line = readline(cmdline);
        if (!ft_strcmp(line, "exit"))
            exit(0);
    }
    return (0);
}
