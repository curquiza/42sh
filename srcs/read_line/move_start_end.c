/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_start_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 15:04:18 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:40:52 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_move_start(t_tc *tool)
{
	int		i;

	i = tool->curs_y + 1;
	while (--i > 0)
		tputs(tool->up, 1, ft_termput);
	tool->curs_y = 0;
	tputs(tgetstr("cr", NULL), 1, ft_termput);
	i = -1;
	while (++i < tool->prompt_len)
		tputs(tool->right, 1, ft_termput);
	tool->curs_x = tool->prompt_len;
}

void	ft_move_end(t_tc *tool)
{
	int		last_raw;
	int		remainder;

	last_raw = (tool->nbr_char + tool->prompt_len) / (tool->x_max + 1);
	remainder = (tool->nbr_char + tool->prompt_len) % (tool->x_max + 1);
	while (tool->curs_y < last_raw)
		ft_move_down(tool);
	tputs(tgetstr("cr", NULL), 1, ft_termput);
	tool->curs_x = 0;
	while (tool->curs_x < remainder)
		ft_move_right(tool);
}
