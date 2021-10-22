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

# define CMD_NOT_FOUND 127
# define CMD_CAN_NOT_EXEC 126

typedef struct s_cmd
{
	char	*cmd;
	char	**cmd_splited;
	int		fd_in;
	int		fd_out;
	pid_t	pid;
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

// util/errors.c
int		cmd_not_found(char *cmd, char *str);
void	error_builtin(char *str);
int		command_exit(char *cmd, char *str, int exit_code);

// builtins
int	distribution(t_minish *minish, char **cmd, char **env);
int		builtins(char **cmd, char **env);
void	ft_pwd(char **cmd_splited);
void	ft_env(char **cmd_splited, char **env);
void	ft_command(char **cmd, char **env);
void	run_cmd(char **cmd, char **env);
void	ft_pipes(t_minish *minish, char **env);
void	perror_exit_bash(char *str);
#endif
