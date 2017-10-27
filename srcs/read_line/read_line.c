/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 17:03:09 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/18 17:05:15 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_termput(int c)
{
	write(1, &c, 1);
	return (0);
}

static void	ft_read_without_tc(char **line)
{
	char	*get_gnl;

	ft_putstr("*** GNL mode ***\n$> ");
	if (get_next_line(STDIN_FILENO, &get_gnl) == -1)
		ft_exit("gnl error", 1);
	*line = ft_strjoin(get_gnl, "\n");
	ft_strdel(&get_gnl);
}

void		ft_read_line(char **line, int prompt_len)
{
	char	little_buff[5];

	ft_strdel(line);
	if (ft_init_tc() == -1)
		ft_read_without_tc(line);
	else
	{
		ft_init_struct_tc(g_shell->tc_tool, prompt_len);
		while (g_shell->tc_tool->stop == 0)
		{
			ft_bzero(little_buff, 5);
			read(0, little_buff, 4);
			ft_interpreter(little_buff, g_shell->tc_tool);
		}
		ft_putendl("");
		*line = ft_strdup(g_shell->tc_tool->buff);
		ft_reset_tc(g_shell->tc_tool);
	}
	g_shell->ctrl_c = 0;
}
