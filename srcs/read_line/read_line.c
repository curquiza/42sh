/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 17:03:09 by curquiza          #+#    #+#             */
/*   Updated: 2017/11/03 13:58:58 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_termput(int c)
{
	write(1, &c, 1);
	return (0);
}

void		ft_read_line(char **line, int prompt_len)
{
	char	little_buff[5];

	ft_strdel(line);
	ft_init_tc();
	ft_init_struct_tc(g_shell->tc_tool, prompt_len);
	g_shell->ctrl_c = 0;
	while (g_shell->tc_tool->stop == 0)
	{
		ft_bzero(little_buff, 5);
		read(0, little_buff, 3);
		ft_interpreter(little_buff, g_shell->tc_tool);
	}
	ft_putendl("");
	*line = ft_strdup(g_shell->tc_tool->buff);
	ft_reset_tc(g_shell->tc_tool);
}
