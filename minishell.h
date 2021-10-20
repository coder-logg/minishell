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

# define NO_FILE_OR_DIR "No such file or directory"
# define CMD_NOT_FOUND "command not found"
# define STRJOIN_ERROR "Error in ft_strjoin"

typedef struct s_cmd
{
	char	*cmd;
	char	**cmd_splited;
	pid_t		pid;
	int		fd_in;
	int		fd_out;
}			t_cmd;

struct s_minish
{
	char	*line;
	char	**cmd;
	t_list	*cmdlst;
};

// util/utils.c
void	*check_malloc(void *ptr);
void	set_free(void **var, void *new);
t_list	*create_node(char *cmd, char **cmd_splited);
void	destroy_node(void *content);

// util/errors.c for parse
int		cmd_not_found(char *cmd, char *str);
void	error_builtin(char *str);

// builtins
void	distribution(t_minish *minish, char **env);
void	ft_pwd(char **cmd_splited);
void	ft_env(char **cmd_splited, char **env);
int		run_cmd(char **cmd, char **env);
int		ft_pipes(t_minish *minish, char **env);

#endif
