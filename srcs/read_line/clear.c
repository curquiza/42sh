/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 14:06:13 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:15:26 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_clear_all_lines(t_tc *tool)
{
	int		i;

	i = tool->curs_y + 1;
	while (--i > 0)
		tputs(tool->up, 1, ft_termput);
	tputs(tgetstr("cr", NULL), 1, ft_termput);
	i = -1;
	while (++i < tool->prompt_len)
		tputs(tool->right, 1, ft_termput);
	tputs(tgetstr("ce", NULL), 1, ft_termput);
	if (tool->nbr_char + tool->prompt_len > tool->x_max + 1)
	{
		tputs(tool->down, 1, ft_termput);
		tputs(tgetstr("cr", NULL), 1, ft_termput);
		tputs(tgetstr("cd", NULL), 1, ft_termput);
		tputs(tool->up, 1, ft_termput);
		i = -1;
		while (++i < tool->prompt_len)
			tputs(tool->right, 1, ft_termput);
	}
}

void	ft_clean_buff(t_tc *tool)
{
	int		i;

	i = 0;
	while (tool->buff[i])
	{
		if (tool->buff[i] == '\n')
		{
			ft_bzero(tool->buff + i + 1, TC_SIZE - i - 1);
			tool->stop = 1;
			break ;
		}
		if (tool->buff[i] == '\t')
			tool->buff[i] = ' ';
		i++;
	}
}
