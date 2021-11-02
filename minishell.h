#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_minish	t_minish;
typedef struct s_cmd	t_cmd;

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
# define SYNTAX_ERROR 258
# define RS	"\x1b[0m"
# define X  "\x1b[36m"

# define ALL_GOOD 400
# define NOT_VALID 401
# define SAME_KEY 402

extern int	g_status;

typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;

struct s_cmd
{
	char		*cmd;
	char		**cmd_splited;
	int			rd_fds[2];
	pid_t		pid;
	int			fd_in;
	int			fd_out;
};

struct s_minish
{
	char	*line;
	char	**env;
	// t_list	*env_lst;
	t_list	*cmdlst;
};

// util/utils.c
void	*check_malloc(void *ptr);
void	set_free(void **var, void *new);
t_list	*create_node(char *cmd, char **cmd_splited);
void	destroy_node(void *content);

// util/cvenkman/cvenkman.c
void	free_arr(char **arr);
	// char	**get_env_from_list(t_env *env_list)

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
void		run_cmd(char **cmd, char **env);
void	ft_pipes(t_minish *minish, char **env);
int		echo(char **cmd_splited);
int		cd(char **cmd_splited, char **env);
int		get_envi(char **env, const char *key);
int		ft_exit(char **cmd);

// builtins/export_and_unset
int		ft_export(char **cmd_splited, char **env, t_minish *minish);
void	print_export(char **export);
int		unset(char **cmd_splited, char **env, t_minish *minish);

// builtins/export_and_unset/export_utils.c
void	not_valid_export(char *cmd, char *str);
int		check_valid(char *str, int *ret, char **env);
int		valid_export_len(char **cmd_splited, char **env);
void	*return_flag(int *ret);

#endif
