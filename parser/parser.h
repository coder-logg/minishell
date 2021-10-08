#ifndef PARSER_H
# define PARSER_H

void	parser(t_minish *minish);
char	*replace_subst(char *str, char *substr, char *replacement, int pos);
char	*collapse_symbols(char *str, int pos, char ch);

#endif
