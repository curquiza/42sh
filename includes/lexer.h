/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 16:34:39 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:58:09 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*
** lex_list.c
*/

t_lexeme	*ft_lexlst_new(char *s);
void		ft_lexlst_addback(t_lexeme **alst, t_lexeme *new);
t_lexeme	*ft_lexlst_last(t_lexeme *lst);
int			ft_lexlst_len(t_lexeme *lst);

/*
** lex_list_del.c
*/

void		ft_lex_suppr_elem(t_lexeme **elem);
void		ft_lexlst_remove_if(t_lexeme **begin_list, void *ref, int mode);
void		ft_lexlstdel(t_lexeme **alst);

/*
** lexer.c
*/

int			ft_find_endoftoken(int i, char *s);
int			ft_endoftoken_position(t_lexeme *lex, char *s, int *ionbr);
void		ft_lexer(t_lexeme **lex, char *s);

/*
** lexer_token_type.c
*/

void		ft_check_c_op(t_lexeme *lex);
void		ft_check_r_op(t_lexeme *lex);
void		ft_check_ass_word(t_lexeme *lex);
void		ft_token_type(t_lexeme *lex, int ind_ionbr, int *ind_assword);

/*
** lexer_op_type.c
*/

int			ft_is_op(char *s);
int			ft_is_redop(char *s);

#endif
