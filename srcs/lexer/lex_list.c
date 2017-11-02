/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 16:57:10 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 16:44:22 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_lexeme	*ft_lexlst_new(char *s)
{
	t_lexeme	*new;

	if (!(new = (t_lexeme *)malloc(sizeof(*new))))
		ft_exit("malloc error", 1);
	if (s == NULL)
		new->s = NULL;
	else
		new->s = ft_strdup(s);
	new->hdoc = NULL;
	new->token = 0;
	new->op = 0;
	new->hdoc_delim = 0;
	new->next = NULL;
	return (new);
}

void		ft_lexlst_addback(t_lexeme **alst, t_lexeme *new)
{
	t_lexeme	*tmp;

	if (alst == NULL)
		return ;
	tmp = *alst;
	if (*alst == NULL)
		*alst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_lexeme	*ft_lexlst_last(t_lexeme *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int			ft_lexlst_len(t_lexeme *lst)
{
	int		cpt;

	cpt = 0;
	while (lst)
	{
		cpt++;
		lst = lst->next;
	}
	return (cpt);
}
