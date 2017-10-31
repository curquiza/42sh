/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 12:03:29 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/26 12:30:43 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_check_ctrl_c(char **line, t_shell *shell)
{
	if (line && *line && shell->ctrl_c == 1)
	{
		ft_strdel(&g_shell->line);
		g_shell->line = ft_strdup(*line);
		free(*line);
		return (1);
	}
	return (0);
}

void	ft_ctrl_c(int sig)
{
	(void)sig;
	ft_fill_cmd_return(CMD_FAILURE, g_shell);
	ft_init_struct_tc(g_shell->tc_tool, PROMPT_DEF_SIZE);
	g_shell->ctrl_c = 1;
	g_shell->inhib = 0;
}

void	ft_redim_window(int sig)
{
	int		init_prompt_len;
	int		nbr_char;
	int		ctrl_r;
	char	buff[TC_SIZE];
	int		pos;

	(void)sig;
	g_shell->tc_tool->redim = 1;
	pos = g_shell->tc_tool->curs_y * (g_shell->tc_tool->x_max + 1)
		+ g_shell->tc_tool->curs_x - g_shell->tc_tool->prompt_len;
	ft_bzero(buff, TC_SIZE);
	ft_strcpy(buff, g_shell->tc_tool->buff);
	nbr_char = g_shell->tc_tool->nbr_char;
	ctrl_r = g_shell->tc_tool->ctrl_r;
	init_prompt_len = g_shell->tc_tool->init_prompt_len;
	ft_init_struct_tc(g_shell->tc_tool, init_prompt_len);
	ft_strcpy(g_shell->tc_tool->buff, buff);
	g_shell->tc_tool->nbr_char = nbr_char;
	g_shell->tc_tool->ctrl_r = ctrl_r;
	g_shell->tc_tool->curs_y = (pos + g_shell->tc_tool->prompt_len)
							/ (g_shell->tc_tool->x_max + 1);
	g_shell->tc_tool->curs_x = (pos + g_shell->tc_tool->prompt_len)
							% (g_shell->tc_tool->x_max + 1);
}

void	ft_catch_signal_parent(void)
{
	signal(SIGQUIT, SIG_IGN);
	//signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGWINCH, ft_redim_window);
	signal(SIGINT, ft_ctrl_c);
	signal(SIGCHLD, ft_exit_job);
}

void	ft_catch_signal_child(void)
{
	signal(SIGQUIT, SIG_DFL);
	//signal(SIGTERM, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGWINCH, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}
