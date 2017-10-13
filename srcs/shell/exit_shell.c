/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:04:56 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:04:59 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_del_histo(t_histo_ctrl **ctrl)
{
	t_histo		*tmp;
	t_histo		*suppr;

	if (!ctrl || !*ctrl)
		return ;
	tmp = (*ctrl)->start;
	while (tmp)
	{
		suppr = tmp;
		tmp = tmp->next;
		ft_strdel(&suppr->line);
		suppr->next = NULL;
		suppr->prev = NULL;
		free(suppr);
		suppr = NULL;
	}
	ft_strdel(&(*ctrl)->current);
	ft_bzero(*ctrl, sizeof(**ctrl));
	free(*ctrl);
	*ctrl = NULL;
}

void	ft_del_shell(t_shell **shell)
{
	ft_strdel(&(*shell)->name);
	ft_strdel(&(*shell)->line);
	ft_tabdel(&(*shell)->var_env);
	ft_tabdel(&(*shell)->var_loc);
	ft_tabdel(&(*shell)->var_priv);
	free((*shell)->flags);
	free((*shell)->tc_tool);
	ft_reset_compl((*shell)->comp_ctrl);
	free((*shell)->comp_ctrl);
	ft_del_histo(&(*shell)->histo_ctrl);
	ft_bzero(*shell, sizeof(t_shell *));
	free(*shell);
	*shell = NULL;
}

int		ft_exit_shell(void)
{
	int		i;
	int		exit_status;

	i = 0;
	while (++i < 32)
		signal(i, SIG_DFL);
	ft_putendl("exit");
	exit_status = g_shell->exit_status;
	ft_del_shell(&g_shell);
	return (exit_status);
}
