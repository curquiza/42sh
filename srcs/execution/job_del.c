/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 12:35:38 by sfranc            #+#    #+#             */
/*   Updated: 2017/11/03 12:35:45 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_job_suppr_elem(t_job **elem)
{
	t_job	*suppr;

	suppr = *elem;
	*elem = (*elem)->next;
	ft_strdel(&suppr->cmd_name);
	suppr->pgid = 0;
	suppr->next = NULL;
	free(suppr);
}

void		ft_del_job(t_job *current)
{
	t_job	*tmp;

	if (!g_shell->job_lst)
		return ;
	if (g_shell->job_lst == current)
	{
		ft_job_suppr_elem(&g_shell->job_lst);
		return ;
	}
	tmp = g_shell->job_lst;
	while (tmp->next)
	{
		if (tmp->next == current)
		{
			ft_job_suppr_elem(&tmp->next);
			return ;
		}
		tmp = tmp->next;
	}
}
