/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 22:37:13 by curquiza          #+#    #+#             */
/*   Updated: 2017/06/01 10:37:50 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_exec_scmd_pipeline(t_ast *ast)
{
	if (ast)
	{
		ft_do_ass_word(ast, 1);
		if (ast->redir_list
			&& ft_do_redirection(ast->redir_list, ast->shell) == -1)
			return (CMD_FAILURE);
		return (ft_do_cmd(ast));
	}
	return (CMD_SUCCESS);
}

int		ft_fork_and_exec(t_ast *ast, t_job **current_job)
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
	{
		(*current_job)->pgid = pid;
		//setpgid(pid, pid);
		//wait(&ret);
		//waitpid(pid, &ret, WUNTRACED);
		ret = ft_wait_for_job(current_job);
	}
	return (ft_get_cmdret(ret));
}

int		ft_exec_scmd(t_ast *ast, t_job **current_job)
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
		return (ft_fork_and_exec(ast, current_job));
	}
	return (CMD_SUCCESS);
}
