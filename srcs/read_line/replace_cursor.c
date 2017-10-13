/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_cursor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 16:52:24 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:41:22 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_replace_cursor(t_tc *tool)
{
	int		i;
	int		remainder;

	i = (tool->nbr_char + tool->prompt_len) / (tool->x_max + 1);
	remainder = (tool->nbr_char + tool->prompt_len) % (tool->x_max + 1);
	if (remainder == 0)
		i--;
	while (i > 0)
	{
		tputs(tool->up, 1, ft_termput);
		i--;
	}
	i = -1;
	while (++i < tool->curs_y)
		tputs(tool->down, 1, ft_termput);
	tputs(tgetstr("cr", NULL), 1, ft_termput);
	i = -1;
	while (++i < tool->curs_x)
		tputs(tool->right, 1, ft_termput);
}
