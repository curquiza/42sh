/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibitor_get_endoftoken.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:41:10 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 16:53:21 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_split_endoftoken :
** Ajoute au token précédent la partie de **line correspondant à la fin du
** token.
** Realloc **line en fonction.
*/

void	ft_split_endoftoken(int i, t_lexeme *lex, char **line)
{
	char		*tmp;
	char		*old_token;
	t_lexeme	*last;

	tmp = ft_strsub(*line, 0, i);
	last = ft_lexlst_last(lex);
	old_token = last->s;
	last->s = ft_strjoin(old_token, tmp);
	ft_strdel(&old_token);
	ft_strdel(&tmp);
	tmp = *line;
	*line = ft_strdup(*line + i);
	ft_strdel(&tmp);
}

/*
** ft_rm_bslash_newline :
** Supprime les back-slash suivi de '\n' dans la chaine de char *s.
*/

void	ft_rm_bslash_newline(char **s)
{
	int		i;

	i = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == 39)
		{
			i = ft_next_squote(i, *s);
			(*s)[i] ? i++ : 0;
		}
		else if ((*s)[i] == 92 && (*s)[i + 1] == '\n')
			ft_escape_char(s, &i, '\n');
		else
			i++;
	}
}

/*
** ft_add_endoftoken_bslash :
** Suite à une inhibition du back-slash.
** Trouve la fin du token précédent et apelle le split.
*/

void	ft_add_endoftoken_bslash(t_lexeme *lex, char **line)
{
	int			i;
	t_lexeme	*last;

	if (!lex || !line || !*line)
		return ;
	ft_rm_bslash_newline(&(last = ft_lexlst_last(lex))->s);
	i = 0;
	while ((*line)[i] && (*line)[i] != '\n' && !ft_is_separator((*line)[i]))
	{
		if ((*line)[i] == 92)
			i++;
		if ((*line)[i])
			i++;
	}
	ft_split_endoftoken(i, lex, line);
	last->op = 0;
	last->token = 0;
	ft_check_c_op(last);
	ft_check_r_op(last);
}

/*
** ft_add_endoftoken_quote :
** Suite à une inhibition des quotes.
** Trouve la fin du token précédent et apelle le split.
*/

void	ft_add_endoftoken_quote(t_lexeme *lex, char **line, int quote)
{
	int			i;

	if (!lex || !line || !*line)
		return ;
	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == 92 && quote == 34)
			i++;
		else if ((*line)[i] == quote)
		{
			i++;
			break ;
		}
		if ((*line)[i])
			i++;
	}
	i = ft_find_endoftoken(i, *line);
	ft_split_endoftoken(i, lex, line);
}
