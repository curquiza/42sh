/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 15:14:35 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 16:48:43 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_find_endoftoken :
** Renvoie l'index de la chaine de char *s correspondant à la fin du token.
*/

int		ft_find_endoftoken(int i, char *s)
{
	while (s[i] && s[i] != '\n' && !ft_is_separator(s[i]) && !ft_is_op(s + i))
	{
		if (s[i] == 92)
			i++;
		else if (s[i] == 39)
			i = ft_next_squote(i, s);
		else if (s[i] == 34)
			i = ft_next_dquote(i, s);
		if (s[i])
			i++;
	}
	return (i);
}

/*
** ft_endoftoken_position :
** Renvoie l'index de la chaine de char *s correspondant à la fin du token en
** foncton du début des char observés.
*/

int		ft_endoftoken_position(t_lexeme *lex, char *s, int *ionbr)
{
	int			i;
	t_lexeme	*last;

	i = 0;
	if (s[i] == '\n')
		while (s[i] == '\n')
			i++;
	else if (ft_isdigit(*s) == 1)
	{
		while (ft_isdigit(s[i]) == 1)
			i++;
		(ft_is_redop(s + i) >= 1) ? *ionbr = 1 :
									(i = ft_find_endoftoken(i, s));
	}
	else if ((i = ft_is_op(s)))
		;
	else if (*s == '-')
	{
		last = ft_lexlst_last(lex);
		i = last && (last->op == GREATAND || last->op == LESSAND) ? 1 :
			ft_find_endoftoken(i, s);
	}
	else
		i = ft_find_endoftoken(i, s);
	return (i);
}

/*
** ft_lexer :
** Split en token la chaine de char *s dans une liste chainée de type t_lexeme.
** Identifie le type de chaque token.
*/

void	ft_lexer(t_lexeme **lex, char *s)
{
	int			i;
	char		*token;
	int			ind_ionbr;
	int			ind_assword;
	t_lexeme	*new;

	if (!lex || !s)
		return ;
	ind_assword = 0;
	while (*s)
	{
		while (ft_is_separator(*s) == 1)
			s++;
		ind_ionbr = 0;
		i = ft_endoftoken_position(*lex, s, &ind_ionbr);
		if (i != 0)
		{
			token = ft_strsub(s, 0, i);
			new = ft_lexlst_new(token);
			ft_token_type(new, ind_ionbr, &ind_assword);
			ft_lexlst_addback(lex, new);
			ft_strdel(&token);
		}
		s = s + i;
	}
}
