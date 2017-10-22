/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 16:33:05 by curquiza          #+#    #+#             */
/*   Updated: 2017/07/31 19:05:14 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "struct.h"

enum	e_inhib
{
	I_OK,
	I_SQUOTE,
	I_DQUOTE,
	I_BSLASH,
	I_PIPE,
	I_DPIPE,
	I_DAND
};

/*
** inhibitor.c
*/

void			ft_read_cmd_again(enum e_inhib inhib, char **line);
int				ft_manage_inhib_ctrl(char **line, t_shell *shell);
void			ft_hook_line_up_to_lex(int ret_inhib, t_lexeme **lex,
																char **line);
int				ft_inhibitor(t_lexeme **lex, t_shell *shell);

/*
** inhibitor_check.c
*/

int				ft_check_quote(t_lexeme *lex);
int				ft_check_pipe(t_lexeme *lex);
int				ft_check_bslash(t_lexeme *lex);
enum e_inhib	ft_check_all_inhib(t_lexeme *lex);

/*
** inhibitor_get_endoftoken.c
*/

void			ft_split_endoftoken(int i, t_lexeme *lex, char **line);
void			ft_add_endoftoken_bslash(t_lexeme *lex, char **line);
void			ft_add_endoftoken_quote(t_lexeme *lex, char **line, int quote);
void			ft_rm_bslash_newline(char **s);

/*
** syntax_error.c
*/

void			ft_puterr_unexp_token(char *token, char *shell_name);
t_lexeme		*ft_next_token(t_lexeme *lex);
char			*ft_check_tokenerror(t_lexeme *lex);

/*
** histoevent_error.c
*/

void			ft_put_eventerror(char *name, char *event);
char			*ft_check_histoevent_err(t_lexeme *lex);

/*
** here_doc.c
*/

int				ft_is_quoted(char *s);
void			ft_apply_hdoc_bslash(char **s);
int				ft_hdoc(t_lexeme *lex, t_shell *shell);

/*
** here_doc_get_lines.c
*/

int				ft_manage_bslash_in_hdoc(char **line, char **word);
int				ft_manage_hdoc_line(t_lexeme *lex, int quoted, char **line,
									char **word);
int				ft_get_hdoc_lines(t_lexeme *lex, int quoted);

/*
** parser.c
*/

int				ft_parser(t_lexeme **lex, t_shell *shell);

#endif
