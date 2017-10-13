/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_left_right.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 14:52:33 by curquiza          #+#    #+#             */
/*   Updated: 2017/07/17 14:53:10 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_go_to_eol(t_tc *tool)
{
	int		i;

	i = tool->curs_x;
	while (i < tool->x_max)
	{
		tputs(tool->right, 1, ft_termput);
		i++;
	}
	tool->curs_x = tool->x_max;
}

void	ft_move_left(t_tc *tool)
{
	if (tool->curs_y == 0 && tool->curs_x == tool->prompt_len)
		tputs(tgetstr("bl", NULL), 1, ft_termput);
	else if (tool->curs_x != 0)
	{
		tputs(tool->left, 1, ft_termput);
		tool->curs_x--;
	}
	else if (tool->curs_x == 0)
	{
		tputs(tool->up, 1, ft_termput);
		tool->curs_y--;
		ft_go_to_eol(tool);
	}
}

void	ft_move_right(t_tc *tool)
{
	if (tool->curs_y * (tool->x_max + 1) + tool->curs_x + 1
		== tool->nbr_char + tool->prompt_len + 1)
		tputs(tgetstr("bl", NULL), 1, ft_termput);
	else if (tool->curs_x == tool->x_max)
	{
		tputs(tool->down, 1, ft_termput);
		tputs(tgetstr("cr", NULL), 1, ft_termput);
		tool->curs_y++;
		tool->curs_x = 0;
	}
	else
	{
		tputs(tool->right, 1, ft_termput);
		tool->curs_x++;
	}
}
