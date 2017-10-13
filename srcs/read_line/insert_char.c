/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 17:50:35 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:39:12 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_add_n_char(t_tc *tool, char *buff, int pos, int len)
{
	char	*tmp;

	if (len > (int)ft_strlen(buff))
		len = ft_strlen(buff);
	tmp = ft_strdup(tool->buff);
	ft_bzero(tool->buff, TC_SIZE);
	ft_strncpy(tool->buff, tmp, pos);
	ft_strncpy(tool->buff + pos, buff, len);
	ft_strcpy(tool->buff + pos + len, tmp + pos);
	tool->nbr_char = tool->nbr_char + len;
	ft_strdel(&tmp);
}

void	ft_insert(char *buff, t_tc *tool)
{
	int		pos;
	int		i;
	int		len;

	if (tool->nbr_char + ft_strlen(buff) >= TC_SIZE - 2)
	{
		tputs(tgetstr("bl", NULL), 1, ft_termput);
		return ;
	}
	len = ft_strlen(buff);
	pos = tool->curs_y * (tool->x_max + 1) + tool->curs_x - tool->prompt_len;
	ft_clear_all_lines(tool);
	ft_add_n_char(tool, buff, pos, len);
	ft_clean_buff(tool);
	write(1, tool->buff, ft_strlen(tool->buff));
	ft_replace_cursor(tool);
	i = -1;
	while (++i < len)
		ft_move_right(tool);
}

void	ft_insert_eol(t_tc *tool)
{
	if (tool->nbr_char >= TC_SIZE - 1)
	{
		tool->buff[TC_SIZE - 2] = '\n';
		tool->buff[TC_SIZE - 1] = '\0';
	}
	else
		tool->buff[tool->nbr_char] = '\n';
	tool->stop = 1;
}
