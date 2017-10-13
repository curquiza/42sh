/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_up_down.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:41:04 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:41:06 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_move_up(t_tc *tool)
{
	if (tool->curs_y == 0)
		tputs(tgetstr("bl", NULL), 1, ft_termput);
	else
	{
		tputs(tool->up, 1, ft_termput);
		tool->curs_y--;
		if (tool->curs_y == 0 && tool->curs_x < tool->prompt_len)
		{
			while (tool->curs_x < tool->prompt_len)
				ft_move_right(tool);
		}
	}
}

void	ft_move_down(t_tc *tool)
{
	int		last_raw;
	int		remainder;
	int		i;

	last_raw = (tool->nbr_char + tool->prompt_len) / (tool->x_max + 1);
	remainder = (tool->nbr_char + tool->prompt_len) % (tool->x_max + 1);
	if (tool->curs_y == last_raw)
		tputs(tgetstr("bl", NULL), 1, ft_termput);
	else
	{
		tputs(tool->down, 1, ft_termput);
		tool->curs_y++;
		i = -1;
		while (++i < tool->curs_x)
			tputs(tool->right, 1, ft_termput);
		if (tool->curs_y == last_raw && tool->curs_x > remainder)
		{
			while (tool->curs_x > remainder)
				ft_move_left(tool);
		}
	}
}
