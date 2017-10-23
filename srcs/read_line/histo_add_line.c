/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histo_add_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 16:47:21 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/23 17:54:33 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_histolst_del(t_histo **alst)
{
	if (alst)
	{
		if (*alst)
			ft_strdel(&(*alst)->line);
		(*alst)->next = NULL;
		(*alst)->prev = NULL;
		free(*alst);
		*alst = NULL;
	}
}

void	ft_del_old_histo(t_histo_ctrl *ctrl)
{
	t_histo		*last;

	last = ctrl->end->prev;
	ft_histolst_del(&last->next);
	last->next = NULL;
	ctrl->end = last;
}

void	ft_add_histo_line(t_tc *tool, t_histo **histo, t_histo_ctrl *ctrl)
{
	t_histo		*new;

	if (!histo || tool->nbr_char == 0)
		return ;
	new = ft_memalloc(sizeof(*new));
	new->line = ft_strdup(tool->buff);
	if (!(*histo))
		*histo = new;
	else
	{
		new->next = *histo;
		(*histo)->prev = new;
		*histo = new;
	}
	ctrl->start = *histo;
	if (!ctrl->end)
		ctrl->end = *histo;
	ctrl->len++;
	if (ctrl->len > HISTO_SIZE)
	{
		ft_del_old_histo(ctrl);
		ctrl->len--;
	}
	ft_strdel(&ctrl->current);
}
