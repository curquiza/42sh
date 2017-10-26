/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 10:02:07 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/26 17:17:31 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <errno.h>
#include <stdio.h>

static void	ft_save_std_fd(t_ast *ast)
{
	//ast->shell->std_fd[0] = dup(0);
	//ast->shell->std_fd[1] = dup(1);
	//ast->shell->std_fd[2] = dup(2);
	int			i;
	i = 0;
	while (i < 10)
	{
		ast->shell->std_fd[i] = dup(i);
		//perror("");
		ft_putnbr2("i = ", i);
		ft_putnbr2("std_fd = ", ast->shell->std_fd[i]);
		i++;
	}
}

static void	ft_restore_fd(t_ast *ast)
{
	t_redir		*redir;
	int			i;

	i = 0;
	while (i < 10)
	{
		dup2(ast->shell->std_fd[i], i);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		close(ast->shell->std_fd[i]);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		ast->shell->std_fd[i] = 0;
		i++;
	}

	//dup2(ast->shell->std_fd[0], 0);
	//dup2(ast->shell->std_fd[1], 1);
	//dup2(ast->shell->std_fd[2], 2);
	//close(ast->shell->std_fd[0]);
	//close(ast->shell->std_fd[1]);
	//close(ast->shell->std_fd[2]);
	//ast->shell->std_fd[0] = 0;
	//ast->shell->std_fd[1] = 0;
	//ast->shell->std_fd[2] = 0;
	redir = ast->redir_list;
	while (redir)
	{
		if (redir->fd != -1 && redir->fd != 0)
			close(redir->fd);
		redir = redir->next;
	}
}

void		ft_pre_execution(t_ast *ast)
{
	if (ast)
	{
		ft_semantic_analysis(ast);
		ft_expansion(ast);
		ft_get_argtab(ast);
		ft_build_redir_list(ast);
		ft_save_std_fd(ast);
	}
}

int			ft_execution(t_ast *ast)
{
	int		ret_cmd;

	if (ast)
	{
		if (ast->lex && ast->lex->op == SEMIC)
			return (ft_apply_semic(ast));
		else if (ast->lex && ast->lex->op == DPIPE)
			return (ft_apply_d_pipe(ast));
		else if (ast->lex && ast->lex->op == DAND)
			return (ft_apply_d_and(ast));
		else if (ast->lex && ast->lex->op == PIPE)
			return (ft_apply_pipe(ast));
		else
		{
			ft_pre_execution(ast);
			ret_cmd = ft_exec_scmd(ast);
			ft_fill_cmd_return(ret_cmd, ast->shell);
			ft_restore_fd(ast);
			return (ret_cmd);
		}
	}
	return (CMD_SUCCESS);
}

void		ft_cmd_line_execution(t_ast **ast, t_shell *shell)
{
	if (shell->flags->token || shell->flags->ast)
		ft_putendl_col("\n---- EXEC ----\n", B_YELLOW, DEF);
	ft_fill_cmd_return(ft_execution(*ast), shell);
	if (shell->flags->token || shell->flags->ast)
		ft_putendl_col("\n--------------\n", B_YELLOW, DEF);
	ft_del_ast(ast);
}
