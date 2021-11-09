#ifndef PARSER_H
# define PARSER_H

int parser(t_minish *minish);
char	*replace_substr(char *str, char *substr, char *replacement, int pos);
char	*shrink_chs_one(char *str, int pos, char ch);
int		read_env(char **str, int pos, char **env);
char	*skip_untill_chr(char *str, char chr);
char	*ft_strchrs(const char *str, const char *chrs);
int		parse_redirect(char **line, int i, t_cmd *cmd, char **env);
int		parse_quotes(char **str, int i, char **env);
char 	*substr_till_chr(char *str, char chr, int start);
char	*ft_strldup(const char *str, int len);
char	*chrdup(char ch, unsigned int len);
char	*chstr(char c);
int		parse_heredoc(char *stop_w, char **env);
//int		heredoc(t_cmd *structure, char *stop);

#endif
