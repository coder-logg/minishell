#include "../minishell.h"

int	arr_len(char **cmd_splited)
{
	int	i;

	i = 0;
	if (!cmd_splited)
		return (0);
	while (cmd_splited[i] != NULL)
		i++;
	return (i);
}

char	**strarr_add(char **arr, size_t arrlen, char *new)
{
	char	**new_arr;

	new_arr = (char	**)chmllc(ft_calloc(arrlen + 2, sizeof(char *)));
	if (!new_arr || !new)
		return (NULL);
	if (arrlen >= 1 && arr)
		ft_memcpy(new_arr, arr, sizeof(char *) * arrlen);
	new_arr[arrlen] = new;
	new_arr[arrlen + 1] = NULL;
	if (arr)
		free(arr);
	return (new_arr);
}

char	**copystr_array(char **arr)
{
	char	**res;
	int		arrlen;
	int		i;

	arrlen = arr_len(arr);
	i = -1;
	res = chmllc(ft_calloc(arrlen + 1, sizeof(char *)));
	res[arrlen] = NULL;
	while (++i < arrlen)
		res[i] = ft_strdup(arr[i]);
	return (res);
}
