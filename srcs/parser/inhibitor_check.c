/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibitor_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 15:17:22 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 16:51:17 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_check_quote :
** Retourne la valeur ascii correspondant à la quote si cette dernière a été
** ouverte mais n'a pas été fermée, sinon retourne 0.
*/

int				ft_check_quote(t_lexeme *lex)
{
	int		i;
	char	*s;

	s = ft_lexlst_last(lex)->s;
	i = 0;
	while (s[i])
	{
		if (s[i] == 92)
			i++;
		else if (s[i] == 39)
		{
			i = ft_next_squote(i, s);
			if (!s[i])
				return (39);
		}
		else if (s[i] == 34)
		{
			i = ft_next_dquote(i, s);
			if (!s[i])
				return (34);
		}
		if (s[i])
			i++;
	}
	return (0);
}

/*
** ft_check_ctrl_op :
** Retourne -1 si un |, && ou || est trouvé en fin de ligne envoyée par
** l'utilisateur.
** Sinon retourne 0.
*/

int				ft_check_ctrl_op(t_lexeme *lex, enum e_op op)
{
	while (lex)
	{
		if (lex->op == op)
		{
			lex = ft_next_token(lex);
			if (!lex)
				return (-1);
		}
		lex = lex->next;
	}
	return (0);
}

/*
** ft_check_bslash :
** Retourne -1 si un back-slash suivi d'un '\n' est trouvé, sinon retourne 0.
*/

int				ft_check_bslash(t_lexeme *lex)
{
	int			i;
	t_lexeme	*last;

	last = ft_lexlst_last(lex);
	if (last->token == NEW_LINE)
		return (0);
	i = ft_strlen(last->s) - 2;
	if (last->s[i] == 92 && last->s[i + 1] == '\n')
		return (-1);
	return (0);
}

/*
** ft_check_all_inhib :
** Retourne l'inhibateur causant l'erreur.
*/

enum e_inhib	ft_check_all_inhib(t_lexeme *lex)
{
	int		ret_quote;

	if (!lex)
		return (I_OK);
	if ((ret_quote = ft_check_quote(lex)) == 34)
		return (I_DQUOTE);
	if (ret_quote == 39)
		return (I_SQUOTE);
	if (ft_check_bslash(lex) == -1)
		return (I_BSLASH);
	if (ft_check_ctrl_op(lex, PIPE) == -1)
		return (I_PIPE);
	if (ft_check_ctrl_op(lex, DPIPE) == -1)
		return (I_DPIPE);
	if (ft_check_ctrl_op(lex, DAND) == -1)
		return (I_DAND);
	return (I_OK);
}
