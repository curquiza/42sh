/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histo_up_down.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 16:52:32 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:32:55 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_get_line_with_pos(t_histo *histo, int n)
{
	int i;

	i = 1;
	while (histo && i < n)
	{
		histo = histo->next;
		i++;
	}
	return (histo ? histo->line : NULL);
}

void	ft_histo_up(t_tc *tool, t_histo_ctrl *ctrl)
{
	char	*line;

	if (ctrl->pos == 0)
	{
		ft_strdel(&ctrl->current);
		ctrl->current = ft_strdup(tool->buff);
	}
	if (ctrl->len && ctrl->pos < ctrl->len)
	{
		ft_clear_all_lines(tool);
		ft_init_struct_tc(tool, tool->init_prompt_len);
		ctrl->pos++;
		line = ft_get_line_with_pos(ctrl->start, ctrl->pos);
		if (line)
			ft_insert(line, tool);
	}
}

void	ft_histo_down(t_tc *tool, t_histo_ctrl *ctrl)
{
	char	*line;

	if (ctrl->pos >= 1 && ctrl->len > 0)
	{
		ft_clear_all_lines(tool);
		ft_init_struct_tc(tool, tool->init_prompt_len);
		ctrl->pos--;
		if (ctrl->pos == 0)
			ft_insert(ctrl->current, tool);
		else
		{
			line = ft_get_line_with_pos(ctrl->start, ctrl->pos);
			if (line)
				ft_insert(line, tool);
		}
	}
}
