#ifndef PARSER_H
# define PARSER_H

void	parser(t_minish *minish);
char	*replace_subst(char *str, char *substr, char *replacement, int pos);
char	*shrink_chs_one(char *str, int pos, char ch);
int		read_env(char **str, int pos);
int		count_symbol_occur(char *str, char ch);
int		arr_len(char **cmd_splited);
char	*skip_untill_chr(char *str, char chr);

#endif
