#include "../minishell.h"

//char *parse_heredoc(char **cmd, int fname_start, t_cmd *structure)
//{
//
//}

int parse_file_name(char **cmd, int fname_start, char **dst)
{
	int		j;
	char	ch_str[2];
	char	*ptr;
	char	*buf;
	int		res;

	ptr = ft_strchrs(*cmd + fname_start, " <>");
//	printf("ptr = %s\n", ptr);
	if (ptr)
		buf = ft_substr(*cmd, fname_start, ptr - (*cmd + fname_start));
	else
		buf = ft_substr(*cmd, fname_start, ft_strlen(*cmd + fname_start));
	j = -1;
//	printf("buf = %s\n", buf);
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

int parse_redirect(char **cmd, int i, t_cmd *structure)
{
	bool	is_double;
	int		index;
	int		oflags;
	char	*buf;
	int		fname_start;

	is_double = false;
	oflags = 0;
	if ((*cmd)[i] == (*cmd)[i + 1])
		is_double = true;
	fname_start = i + is_double + 1;
	if ((*cmd)[i + 1] == ' ' || ((*cmd)[i] == (*cmd)[i + 1] && (*cmd)[i + 1]
								&& (*cmd)[i + 2] == ' '))
		fname_start++;
	int len = parse_file_name(cmd, fname_start, &buf);
	if ((*cmd)[i] == '<')
	{
		if (is_double)
		{
//			parse_heredoc(cmd, fname_start, structure);
			return (0);
		}
		else
			oflags = O_RDONLY;
		index = 0;
	}
	if ((*cmd)[i] == '>')
	{
		oflags = O_CREAT | O_WRONLY;
		if (is_double)
			oflags |= O_APPEND;
		else
			oflags |= O_TRUNC;
		index = 1;
	}
//	printf("buf = %s\n", buf);
	if (structure->rd_fds[index] != -1)
		close(structure->rd_fds[index]);
	structure->rd_fds[index] = open(buf, oflags, 0644);
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