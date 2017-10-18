/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:41:52 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/18 11:32:48 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_interpreter(char *buff, t_tc *tool)
{
	ft_eol_interpreter(buff, tool);
	ft_basic_interpreter(buff, tool);
	ft_histo_interpreter(buff, tool);
	ft_compl_interpreter(buff, tool);
}

void	ft_eol_interpreter(char *buff, t_tc *tool)
{
	if (buff[0] == '\n')
	{
		if (tool->ctrl_r == 0)
		{
			ft_add_histo_line(tool, &g_shell->histo_ctrl->start,
									g_shell->histo_ctrl);
			ft_insert_eol(tool);
		}
		else
			ft_put_ctrl_r_rslt(tool, g_shell->histo_ctrl);
	}
}

void	ft_basic_interpreter(char *buff, t_tc *tool)
{
	ft_isprint(buff[0]) == 1 ? ft_insert(buff, tool) : 0;
	buff[0] == 127 ? ft_delete_back(tool) : 0;
	if (buff[0] == 27 && buff[2] == 51 && buff[3] == 126)
		ft_delete_front(tool);
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 68)
		ft_move_left(tool);
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 67)
		ft_move_right(tool);
	if ((buff[0] == 27 && buff[1] == 27 && buff[2] == 91 && buff[3] == 65)
		|| (buff[0] == 27 && buff[1] == 91 && buff[2] == 53 && buff[3] == 126))
		ft_move_up(tool);
	if ((buff[0] == 27 && buff[1] == 27 && buff[2] == 91 && buff[3] == 66)
		|| (buff[0] == 27 && buff[1] == 91 && buff[2] == 54 && buff[3] == 126))
		ft_move_down(tool);
	if ((buff[0] == 27 && buff[1] == 91 && buff[2] == 72) || buff[0] == 1)
		ft_move_start(tool);
	if ((buff[0] == 27 && buff[1] == 91 && buff[2] == 70) || buff[0] == 5)
		ft_move_end(tool);
	buff[0] == 2 ? ft_move_word_left(tool) : 0;
	buff[0] == 6 ? ft_move_word_right(tool) : 0;
	buff[0] == 11 ? ft_copy(tool) : 0;
	buff[0] == 24 ? ft_cut(tool) : 0;
	buff[0] == 16 ? ft_insert(tool->tmp, tool) : 0;
	buff[0] == 4 ? ft_ctrl_d(tool) : 0;
}

void	ft_histo_interpreter(char *buff, t_tc *tool)
{
	if (buff[0] == 18 && tool->ctrl_r == 0 && g_shell->inhib == 0)
		ft_ctrl_r(tool);
	if (tool->ctrl_r == 0)
	{
		if (buff[0] == 27 && buff[1] == 91 && buff[2] == 65)
			ft_histo_up(tool, g_shell->histo_ctrl);
		else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 66)
			ft_histo_down(tool, g_shell->histo_ctrl);
		else
			g_shell->histo_ctrl->pos = 0;
	}
}

void	ft_compl_interpreter(char *buff, t_tc *tool)
{
	if (tool->ctrl_r == 0 && g_shell->inhib == 0)
	{
		if (buff[0] == 9)
			ft_completion(tool, g_shell->comp_ctrl);
	}
}
