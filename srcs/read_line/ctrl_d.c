/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 16:32:46 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:17:41 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_check_and_restore_ctrld(t_shell *shell)
{
	if (shell->ctrl_d != 0)
	{
		g_shell->run = 1;
		shell->ctrl_d = 0;
		return (1);
	}
	return (0);
}

void	ft_ctrl_d(t_tc *tool)
{
	if (tool->nbr_char == 0)
	{
		tool->stop = 1;
		g_shell->run = 0;
		g_shell->ctrl_d = 1;
	}
}
