/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_reset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:09:42 by curquiza          #+#    #+#             */
/*   Updated: 2017/11/03 15:06:09 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_init_tc(void)
{
	char			*name_term;
	struct termios	term;

	if (isatty(STDIN_FILENO) != 1)
		ft_exit("Init termcaps: stdin is not referring to a terminal", 1);
	name_term = ft_get_varvalue(g_shell->var_env, "TERM");
	if (!name_term || tgetent(NULL, name_term) != 1)
		ft_exit("\ninit termcaps: not a valid terminal name,\
				can't get the terminal informations.\nShell closing...", 1);
	if (tcgetattr(0, &term) != 0)
		ft_exit("Init termcaps: tcgetattr error", 1);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 1;
	if (tcsetattr(0, TCSANOW, &term) != 0)
		ft_exit("Init termcaps: tcsetattr error", 1);
}

void	ft_reset_tc(t_tc *tool)
{
	struct termios	term;

	if (tcgetattr(0, &term) != 0)
		ft_exit("Reset termcaps: tcsetattr error", 1);
	term.c_lflag |= ICANON;
	term.c_lflag |= ECHO;
	if (tcsetattr(0, TCSANOW, &term) != 0)
		ft_exit("Reset termcaps: tcsetattr error", 1);
	ft_bzero(tool, sizeof(*tool));
}

void	ft_init_struct_tc(t_tc *tool, int prompt_len)
{
	struct winsize	*w;

	ft_bzero(tool, sizeof(*tool));
	tool->up = tgetstr("up", NULL);
	tool->down = tgetstr("sf", NULL);
	tool->right = tgetstr("nd", NULL);
	tool->left = tgetstr("le", NULL);
	w = ft_memalloc(sizeof(*w));
	if (ioctl(1, TIOCGWINSZ, w) != 0)
		tool->x_max = tgetnum("co") - 1;
	else
		tool->x_max = w->ws_col - 1;
	free(w);
	if (prompt_len >= tool->x_max + 1)
	{
		tool->prompt_len = prompt_len % (tool->x_max + 1);
		if (prompt_len == tool->x_max + 1 && tool->redim == 0)
			tputs(tool->down, 1, ft_termput);
	}
	else
		tool->prompt_len = prompt_len;
	tool->init_prompt_len = prompt_len;
	tool->curs_x = tool->prompt_len;
}
