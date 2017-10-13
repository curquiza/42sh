/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_list_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:44:33 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 16:46:07 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_lex_suppr_elem(t_lexeme **elem)
{
	t_lexeme	*suppr;

	suppr = *elem;
	*elem = (*elem)->next;
	ft_strdel(&suppr->s);
	ft_strdel(&suppr->hdoc);
	suppr->next = NULL;
	free(suppr);
}

void	ft_lexlst_remove_if(t_lexeme **begin_list, void *ref, int mode)
{
	t_lexeme	*current;

	if (*begin_list)
	{
		current = *begin_list;
		while (current->next)
		{
			if (mode == 0 && ft_strcmp(current->next->s, ref) == 0)
				ft_lex_suppr_elem(&(current->next));
			else if (mode == 1 && current->next->token == *(int *)ref)
				ft_lex_suppr_elem(&(current->next));
			else
				current = current->next;
		}
		if (*begin_list)
		{
			if (mode == 0 && ft_strcmp((*begin_list)->s, ref) == 0)
				ft_lex_suppr_elem(begin_list);
			else if (mode == 1 && (*begin_list)->token == *(int *)ref)
				ft_lex_suppr_elem(begin_list);
		}
	}
}

void	ft_lexlstdel(t_lexeme **alst)
{
	t_lexeme	*current;

	if (!alst)
		return ;
	current = *alst;
	while (current)
		ft_lex_suppr_elem(&(current));
	*alst = NULL;
}
