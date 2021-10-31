#include "../minishell.h"

int heredoc(const char *stop_w, char **env, const int *fd)
{
	char	*buf;
	int		i;
	
	i = -1;
	close(fd[0]);
	while (1)
	{
		buf = readline("> ");
		if (!buf)
			break;
		if (!ft_strcmp(buf, stop_w))
			break;
		while (buf[++i])
		{
			if (buf[i] == '$')
				i = read_env(&buf, i, env);
//			if (i < 0)
//			{
////				g_status =
//				return (-1);
//			}
		}
		write(fd[1], buf, ft_strlen(buf));
		write(fd[1], "\n", 1);
	}
	return (0);
}

int parse_heredoc(char *stop_w, char **env)
{
	int		fd[2];
	int		pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		heredoc(stop_w, env, fd);
		exit(0);
	}
	else
		wait(&pid);
	close(fd[1]);
	return (fd[0]);
}

int parse_file_name(char **cmd, int fname_start, char **dst)
{
	int		j;
	char	ch_str[2];
	char	*ptr;
	char	*buf;
	int		res;

	ptr = ft_strchrs(*cmd + fname_start, " <>");
	if (ptr)
		buf = ft_substr(*cmd, fname_start, ptr - (*cmd + fname_start));
	else
		buf = ft_substr(*cmd, fname_start, ft_strlen(*cmd + fname_start));
	j = -1;
	res = ft_strlen(buf);
	while (buf[++j])
	{
		if (buf[j] == '\"' || buf[j] == '\'')
		{
			ch_str[0] = buf[j];
			ch_str[1] = 0;
			set_free((void **)&buf, replace_subst(buf, ch_str, "", j));
			if (!buf)
				return (-1);
			j = skip_untill_chr(buf + j, ch_str[0]) - buf;
			set_free((void **)&buf, replace_subst(buf, ch_str, "", j));
			if (!buf)
				return (-1);
		}
	}
	*dst = buf;
	return (res);
}

int get_oflags(char redirect, bool is_double)
{
	int	oflags;

	if (redirect == '>')
	{
		oflags = O_CREAT | O_WRONLY;
		if (is_double)
			oflags |= O_APPEND;
		else
			oflags |= O_TRUNC;
	}
	else
		oflags = O_RDONLY;
	return oflags;
}

int parse_redirect(char **cmd, int i, t_cmd *structure, char **env)
{
	bool	is_double;
	int		index;
	char	*buf;
	int		fname_start;
	size_t	len;

	is_double = false;
	if ((*cmd)[i] == (*cmd)[i + 1])
		is_double = true;
	fname_start = i + is_double + 1;
	if ((*cmd)[i + 1] == ' ' || ((*cmd)[i] == (*cmd)[i + 1] && (*cmd)[i + 1]
								&& (*cmd)[i + 2] == ' '))
		fname_start++;
	len = parse_file_name(cmd, fname_start, &buf);
	index = 0;
	if ((*cmd)[i] == '<' && is_double)
	{
		if (structure->rd_fds[index] != -1)
			close(structure->rd_fds[index]);
		structure->rd_fds[index] = parse_heredoc(buf, env);
	}
	else if ((*cmd)[i] == '>')
		index = 1;
	if (!(index == 0 && is_double))
	{
		if (structure->rd_fds[index] != -1)
			close(structure->rd_fds[index]);
		structure->rd_fds[index] = open(buf, get_oflags((*cmd)[i], is_double), 0644);
		if (structure->rd_fds[index] == -1)
			cmd_not_found(buf, strerror(errno));
	}
	set_free((void **)&buf, ft_substr(*cmd, i, len + fname_start - i));
	set_free((void **)cmd, replace_subst(*cmd, buf, "", i));
	set_free((void **)cmd, shrink_chs_one(*cmd, i - 1, ' '));
	if (!(*cmd)[i + 1] && (*cmd)[i - 1])
	{
		i--;
		set_free((void **)cmd, ft_strtrim(*cmd, " \t"));
	}
	free(buf);
	return (i);
}