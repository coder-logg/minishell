#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_minish t_minish;

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include "libft/libft.h"
# include "parser/parser.h"

typedef struct s_cmd
{
	char	**cmd;
}			t_cmd;

struct s_minish
{
	char	*line;
	char	**cmd;
};

int		is_all_spaces(char *str);
void	check(t_minish *minish, char **env);
void	cmd_not_found(char *cmd);
void	error_builtin(char *str);
#endif
