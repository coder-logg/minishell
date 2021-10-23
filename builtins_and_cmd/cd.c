#include "../minishell.h"

int	cd(char **cmd_splited, char **env)
{
	char	*path;
	int		status;
	int		pwdi;
	char	*pwd;
	int		oldpwdi;
	char	*buf;

	if (arr_len(cmd_splited) == 1)
		path = getenv("HOME");
	else
		path = cmd_splited[1];
	buf = check_malloc(ft_calloc(1024, sizeof(char)));
	oldpwdi = get_envi(env, "OLDPWD");
	if (!ft_strcmp(path, "-"))
	{
//		oldpwdi = get_envi(env, "OLDPWD");
		if (oldpwdi == -1)
		{
			cmd_not_found("cd", "OLDPWD not set");
			return (-1);
		}
		else
			path = env[oldpwdi] + ft_strlen("OLDPWD=");
	}
	status = chdir(path);
	if (status)
	{
		path = ft_strjoin(path, ": No such file or directory");
		cmd_not_found("cd", path);
		free(path);
		free(buf);
		return (status);
	}
	getcwd(buf, 1024);
	pwdi = get_envi(env, "PWD");
	pwd = env[pwdi];
	set_free((void **)&pwd, replace_subst(pwd, "PWD=", "OLDPWD=", 0));
//	free(env[pwdi]);
	env[oldpwdi] = pwd;
	env[pwdi] = ft_strjoin("PWD=", buf);
	free(buf);
	return (status);
}