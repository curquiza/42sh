/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 22:37:13 by curquiza          #+#    #+#             */
/*   Updated: 2017/11/03 12:33:26 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*ft_get_pipeline_name(t_ast *ast)
{
	char	*rslt;
	char	*cmd;
	char	*tmp;

	rslt = NULL;
	while (ast && ast->lex && ast->lex->op == PIPE)
	{
		if (ast && ast->left && ast->left->argtab)
			cmd = ft_tab_to_str(ast->left->argtab);
		else
			cmd = ft_strdup("");
		tmp = rslt;
		rslt = tmp ? ft_strjoin3(tmp, " | ", cmd) : ft_strdup(cmd);
		ft_strdel(&tmp);
		ft_strdel(&cmd);
		ast = ast->right;
	}
	cmd = (ast && ast->argtab) ? ft_tab_to_str(ast->argtab) : ft_strdup("");
	tmp = rslt;
	rslt = tmp ? ft_strjoin3(tmp, " | ", cmd) : ft_strdup(cmd);
	ft_strdel(&tmp);
	ft_strdel(&cmd);
	return (rslt);
}

static int		ft_manage_job_ctrl(t_ast *ast, t_job *current_job, pid_t pid)
{
	int		ret;

	setpgid(pid, pid);
	ret = CMD_SUCCESS;
	if (ast->bg == 0)
	{
		ret = ft_wait_for_job(&current_job);
		tcsetpgrp(g_shell->terminal, g_shell->pgid);
		tcsetattr(g_shell->terminal, TCSADRAIN, &(g_shell->dfl_term));
	}
	else
	{
		ft_joblst_addback(&g_shell->job_lst, current_job);
		ft_putchar('[');
		ft_putnbr(ft_joblst_len(g_shell->job_lst));
		ft_putnbr2("]	", current_job->pgid);
	}
	return (ret);
}

int				ft_process_controller(pid_t pid, t_ast *ast)
{
	t_job	*current_job;
	char	*cmd_name;

	if (ast->lex && ast->lex->op == PIPE)
		cmd_name = ft_get_pipeline_name(ast);
	else if (ast->argtab)
		cmd_name = ft_tab_to_str(ast->argtab);
	else
		cmd_name = ft_strdup("");
	current_job = ft_joblst_new(cmd_name, pid);
	ft_strdel(&cmd_name);
	return (ft_manage_job_ctrl(ast, current_job, pid));
}

static int		ft_fork_and_exec(t_ast *ast)
{
	pid_t	pid;
	int		ret;

	ret = CMD_SUCCESS;
	if ((pid = fork()) == -1)
		ft_put_errmsg(ast->shell->name, NULL, "fork error");
	else if (pid == 0)
	{
		ft_do_ass_word(ast, 1);
		exit(ft_do_cmd(ast));
	}
	else if (pid > 0)
		ret = ft_process_controller(pid, ast);
	return (ft_get_cmdret(ret));
}

int				ft_exec_scmd(t_ast *ast)
{
	int		builtin_ret;

	if (ast)
	{
		if (!ast->cmd)
			ft_do_ass_word(ast, 0);
		if (ast->redir_list
			&& ft_do_redirection(ast->redir_list, ast->shell) == -1)
			return (CMD_FAILURE);
		if (!ast->cmd)
			return (CMD_SUCCESS);
		if (ast->cmd &&
			(builtin_ret = ft_is_built_in(ast->cmd->s)) != NOT_BUILTIN)
			return (ft_exec_built_in(ast, builtin_ret));
		return (ft_fork_and_exec(ast));
	}
	return (CMD_SUCCESS);
}
