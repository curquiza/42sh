/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_quote_removal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 14:03:04 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:54:13 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_escape_char(char **s, int *i, char esc_char)
{
	char	*tmp;
	int		gap;
	int		len;

	if (esc_char == '\n')
		gap = 2;
	else
		gap = 1;
	len = ft_strlen(*s);
	tmp = *s;
	*s = ft_strnew(len - gap);
	ft_strncpy(*s, tmp, *i);
	ft_strcpy(*s + *i, tmp + *i + gap);
	free(tmp);
	if (esc_char != '\n')
		*i = *i + 1;
}

void	ft_rm_quote(char **s, int start, int i)
{
	char	*tmp;

	tmp = *s;
	*s = ft_strnew(ft_strlen(*s) - 2);
	ft_strncpy(*s, tmp, start);
	ft_strncpy(*s + start, tmp + start + 1, i - start - 1);
	ft_strcpy(*s + i - 1, tmp + i + 1);
	free(tmp);
}

void	ft_apply_dquote(char **s, int *i)
{
	int		start;

	start = *i;
	(*i)++;
	while ((*s)[*i] && (*s)[*i] != 34)
	{
		if ((*s)[*i] == 92 && ((*s)[*i + 1] == '$' || (*s)[*i + 1] == '`'
								|| (*s)[*i + 1] == 34 || (*s)[*i + 1] == 92
								|| (*s)[*i + 1] == '\n'))
			ft_escape_char(s, i, (*s)[*i + 1]);
		else
			(*i)++;
	}
	ft_rm_quote(s, start, *i);
	(*i) = (*i) - 1;
}

void	ft_apply_squote(char **s, int *i)
{
	int		start;

	start = *i;
	(*i)++;
	while ((*s)[*i] && (*s)[*i] != 39)
		(*i)++;
	ft_rm_quote(s, start, *i);
	(*i) = (*i) - 1;
}

void	ft_quote_removal(char **s)
{
	int		i;

	if (!*s)
		return ;
	i = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == 92 && (*s)[i + 1])
			ft_escape_char(s, &i, (*s)[i + 1]);
		else if ((*s)[i] == 39)
			ft_apply_squote(s, &i);
		else if ((*s)[i] == 34)
			ft_apply_dquote(s, &i);
		else
			i++;
	}
}
