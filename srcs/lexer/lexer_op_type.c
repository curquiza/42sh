/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_op_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 16:16:47 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/13 17:40:35 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_is_op :
** Retourne 0 si les 1er char de *s ne correspondent pas à un opérateur.
** Sinon, retourne la length de cet opérateur.
*/

int		ft_is_op(char *s)
{
	if (!ft_strncmp(s, "<<-", 3))
		return (3);
	if (!ft_strncmp(s, ";;", 2) || !ft_strncmp(s, ">>", 2)
		|| !ft_strncmp(s, "<<", 2) || !ft_strncmp(s, ">&", 2)
		|| !ft_strncmp(s, "<&", 2) || !ft_strncmp(s, "||", 2)
		|| !ft_strncmp(s, "&&", 2) || !ft_strncmp(s, "<>", 2)
		|| !ft_strncmp(s, ">|", 2))
		return (2);
	else if (*s == '|' || *s == ';' || *s == '>' || *s == '<' || *s == '&')
		return (1);
	else
		return (0);
}

/*
** ft_is_redop_ionbr :
** Retourne 0 si les 1er char de *s ne correspondent pas à un opérateur de
** redirection.
** Sinon, retourne la length de cet opérateur.
*/

int		ft_is_redop(char *s)
{
	if (!ft_strncmp(s, "<<-", 3))
		return (3);
	if (!ft_strncmp(s, ">>", 2) || !ft_strncmp(s, "<<", 2)
		|| !ft_strncmp(s, "<&", 2) || !ft_strncmp(s, ">&", 2)
		|| !ft_strncmp(s, "<>", 2) || !ft_strncmp(s, ">|", 2))
		return (2);
	else if (*s == '>' || *s == '<')
		return (1);
	else
		return (0);
}
