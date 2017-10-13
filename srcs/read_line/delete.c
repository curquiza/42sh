/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 16:50:01 by curquiza          #+#    #+#             */
/*   Updated: 2017/07/13 18:31:06 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_delete_n_char(t_tc *tool, int pos, int len)
{
	char	*tmp;

	tmp = ft_strdup(tool->buff);
	ft_bzero(tool->buff, TC_SIZE);
	ft_strncpy(tool->buff, tmp, pos);
	ft_strcpy(tool->buff + pos, tmp + pos + len);
	ft_strdel(&tmp);
	tool->nbr_char = tool->nbr_char - len;
}

void	ft_delete_back(t_tc *tool)
{
	int		pos;

	if (tool->curs_y == 0 && tool->curs_x == tool->prompt_len)
	{
		tputs(tgetstr("bl", NULL), 1, ft_termput);
		return ;
	}
	pos = tool->curs_y * (tool->x_max + 1) + tool->curs_x - tool->prompt_len;
	pos--;
	ft_clear_all_lines(tool);
	ft_delete_n_char(tool, pos, 1);
	write(1, tool->buff, ft_strlen(tool->buff));
	ft_replace_cursor(tool);
	ft_move_left(tool);
}

void	ft_delete_front(t_tc *tool)
{
	int		pos;

	pos = (tool->x_max + 1) * tool->curs_y + tool->curs_x - tool->prompt_len;
	if (pos == tool->nbr_char)
	{
		tputs(tgetstr("bl", NULL), 1, ft_termput);
		return ;
	}
	ft_clear_all_lines(tool);
	ft_delete_n_char(tool, pos, 1);
	write(1, tool->buff, ft_strlen(tool->buff));
	ft_replace_cursor(tool);
}
