/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:04:56 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/25 16:57:21 by sfranc           ###   ########.fr       */
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

static void	ft_save_history_in_file(t_shell	*shell)
{
	char	*histo_file;

	if ((histo_file = ft_get_varvalue(shell->var_priv, "42SH_HISTO_FILE")))
		ft_histo_file_write(shell->histo_ctrl, histo_file, HISTO_WRITE);
}

int		ft_exit_shell(void)
{
	int		i;
	int		exit_status;

	ft_save_history_in_file(g_shell);
	i = 0;
	while (++i < 32)
		signal(i, SIG_DFL);
	ft_putendl("exit");
	exit_status = g_shell->exit_status;
	ft_del_shell(&g_shell);
	return (exit_status);
}
