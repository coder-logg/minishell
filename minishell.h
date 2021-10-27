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

extern int	g_status;

typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;

typedef struct s_cmd
{
	char	*cmd;
	char	**cmd_splited;
	pid_t	pid;
	int		fd_in;
	int		fd_out;
}			t_cmd;

struct s_minish
{
	char	*line;
	char	**env;
	int		status;
	t_list	*cmdlst;
};

// util/utils.c
void	*check_malloc(void *ptr);
void	set_free(void **var, void *new);
t_list	*create_node(char *cmd, char **cmd_splited);
void	destroy_node(void *content);

// util/cvenkman.c
int cmd_splited_len(char **cmd);

// util/errors.c
int		cmd_not_found(char *cmd, char *str);
int		error_builtin(char *str);
int		command_exit(char *cmd, char *str, int exit_code);
void	perror_exit_bash(char *str);

// util/strarr_utils.c
int		arr_len(char **cmd_splited);
char	**strarr_add(char **arr, size_t arrlen, char *new);
char	**copystr_array(char **arr);

// builtins
int		distribution(t_minish *minish, char **cmd, char **env, bool flag_is_pipe);
int		builtins(char **cmd, char **env);
int		ft_pwd(char **cmd_splited);
int		ft_env(char **cmd_splited, char **env);
void	ft_command(char **cmd, char **env);
void	run_cmd(char **cmd, char **env);
void	ft_pipes(t_minish *minish, char **env);
int		echo(char **cmd_splited);
int		echo_n(char **cmd);
int		cd(char **cmd_splited, char **env);
int		get_envi(char **env, const char *key);
int		ft_exit(char **cmd);

// builtins/export
int		ft_export(char **cmd_splited, char **env);
void	print_export(char **export);
#endif
