/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_cut_paste.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 12:54:22 by curquiza          #+#    #+#             */
/*   Updated: 2017/07/18 14:32:45 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_copy(t_tc *tool)
{
	int		pos;

	pos = tool->curs_y * (tool->x_max + 1) + tool->curs_x - tool->prompt_len;
	ft_bzero(tool->tmp, TC_SIZE);
	ft_strcpy(tool->tmp, tool->buff + pos);
}

void	ft_cut(t_tc *tool)
{
	int		pos;
	int		len;

	pos = tool->curs_y * (tool->x_max + 1) + tool->curs_x - tool->prompt_len;
	len = ft_strlen(tool->buff + pos);
	ft_bzero(tool->tmp, TC_SIZE);
	ft_strcpy(tool->tmp, tool->buff + pos);
	ft_bzero(tool->buff + pos, len);
	ft_clear_all_lines(tool);
	tool->nbr_char -= len;
	write(1, tool->buff, ft_strlen(tool->buff));
	ft_replace_cursor(tool);
}
