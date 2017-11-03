/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_fg_bg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 12:25:21 by sfranc            #+#    #+#             */
/*   Updated: 2017/11/03 12:26:50 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		ft_check_arg(t_job *job_lst, char **arg, char *builtin)
{
	if (!arg)
		return (-1);
	if (job_lst == NULL)
	{
		ft_put_errmsg(g_shell->name, builtin, "no job");
		return (-1);
	}
	else if (arg[0] == NULL && job_lst)
		return (0);
	if (ft_tablen(arg) > 1)
	{
		ft_put_errmsg(g_shell->name, builtin, "too many arguments");
		return (-1);
	}
	if (ft_is_uns_nbr(arg[0]) == 0
		|| ft_atoi(arg[0]) == 0 || ft_atoi(arg[0]) > ft_joblst_len(job_lst))
	{
		ft_put_errmsg(g_shell->name, builtin, "no such job");
		return (-1);
	}
	return (0);
}

static t_job	*ft_get_job(t_job *lst, char *job_pos)
{
	if (!job_pos)
		return (ft_joblst_last(lst));
	else
		return (ft_joblst_at(lst, ft_atoi(job_pos)));
}

int				ft_builtin_fg(t_ast *ast)
{
	t_job	*curr_job;

	ft_exit_job(1);
	if (ft_check_arg(g_shell->job_lst, ast->argtab + 1, "fg") == -1)
		return (CMD_FAILURE);
	curr_job = ft_get_job(g_shell->job_lst, ast->argtab[1]);
	if (!curr_job)
	{
		ft_put_errmsg(g_shell->name, "fg", "no such job");
		return (CMD_FAILURE);
	}
	tcsetpgrp(g_shell->terminal, curr_job->pgid);
	if (kill(-curr_job->pgid, SIGCONT) < 0)
		ft_put_errmsg(g_shell->name, "kill", "error");
	ft_wait_for_job(&curr_job);
	tcsetpgrp(g_shell->terminal, g_shell->pgid);
	tcsetattr(g_shell->terminal, TCSADRAIN, &(g_shell->dfl_term));
	return (CMD_SUCCESS);
}

int				ft_builtin_bg(t_ast *ast)
{
	t_job	*curr_job;

	ft_exit_job(1);
	if (ft_check_arg(g_shell->job_lst, ast->argtab + 1, "bg") == -1)
		return (CMD_FAILURE);
	curr_job = ft_get_job(g_shell->job_lst, ast->argtab[1]);
	if (!curr_job)
	{
		ft_put_errmsg(g_shell->name, "bg", "no such job");
		return (CMD_FAILURE);
	}
	if (kill(-curr_job->pgid, SIGCONT) < 0)
		ft_put_errmsg(g_shell->name, "kill", "error");
	return (CMD_SUCCESS);
}
