/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_ascii_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:15:45 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:16:13 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Not proud.
*/

static void	ft_swap_middle(t_comp *prev)
{
	t_comp	*current;
	t_comp	*tmp;
	t_comp	*next;

	if (!prev)
		return ;
	current = prev->next;
	tmp = current->next;
	next = current->next->next;
	if (prev)
		prev->next = tmp;
	tmp->prev = prev;
	current->next = next;
	if (next)
		next->prev = current;
	tmp->next = current;
	current->prev = tmp;
}

static void	ft_swap_beginning(t_comp **comp)
{
	t_comp		*tmp;
	t_comp		*current;
	t_comp		*next;

	current = *comp;
	tmp = current->next;
	next = current->next->next;
	tmp->prev = NULL;
	tmp->next = current;
	*comp = tmp;
	current->next = next;
	current->prev = *comp;
	if (next)
		next->prev = current;
}

void		ft_ascii_sort_words(t_comp **comp)
{
	t_comp		*current;

	if (!*comp || !(*comp)->next)
		return ;
	current = *comp;
	if (ft_strcmp((*comp)->word, (*comp)->next->word) > 0)
		ft_swap_beginning(comp);
	while (current && current->next)
	{
		if (ft_strcmp(current->word, current->next->word) > 0)
		{
			ft_swap_middle(current->prev);
			ft_ascii_sort_words(comp);
			return ;
		}
		current = current->next;
	}
}
