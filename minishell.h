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

typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;

typedef struct s_cmd
{
	char	*cmd;
	char	**cmd_splited;
}			t_cmd;

struct s_minish
{
	char	*line;
	int		status;
	char	**env;
	t_list	*cmdlst;
};

// util/utils.c
void	*check_malloc(void *ptr);
void	set_free(void **var, void *new);
t_list	*create_node(char *cmd, char **cmd_splited);
void	destroy_node(void *content);

// util/strarr_utils.c
int		arr_len(char **cmd_splited);
char	**strarr_add(char **arr, size_t arrlen, char *new);
char	**copystr_array(char **arr);

// util/errors.c for parse
void	cmd_not_found(char *cmd, char *str);
void	error_builtin(char *str);

// builtins
int		distribution(char **splited, char **env);
void	ft_pwd(char **cmd_splited);
void	ft_env(char **cmd_splited, char **env);
int		run_cmd(char **cmd, char **env);
int		echo_n(char **cmd);
int		cd(char **cmd_splited, char **env);

#endif
