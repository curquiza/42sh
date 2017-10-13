/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 17:04:50 by curquiza          #+#    #+#             */
/*   Updated: 2017/07/17 18:13:26 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_move_word_left(t_tc *tool)
{
	int		pos;

	pos = tool->curs_y * (tool->x_max + 1) + tool->curs_x - tool->prompt_len;
	if (pos)
	{
		ft_move_left(tool);
		pos--;
	}
	while (pos && tool->buff[pos] == ' ')
	{
		ft_move_left(tool);
		pos--;
	}
	while (pos && tool->buff[pos] && tool->buff[pos] != ' ')
	{
		ft_move_left(tool);
		pos--;
	}
	if (pos)
		ft_move_right(tool);
}

void	ft_move_word_right(t_tc *tool)
{
	int		pos;

	pos = tool->curs_y * (tool->x_max + 1) + tool->curs_x - tool->prompt_len;
	while (tool->buff[pos] && tool->buff[pos] != ' ')
	{
		ft_move_right(tool);
		pos++;
	}
	while (tool->buff[pos] == ' ')
	{
		ft_move_right(tool);
		pos++;
	}
}
