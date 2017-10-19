/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 10:02:07 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/19 14:02:52 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_save_std_fd(t_ast *ast)
{
	ast->shell->std_fd[0] = dup(0);
	ast->shell->std_fd[1] = dup(1);
	ast->shell->std_fd[2] = dup(2);
}

void	ft_restore_std_fd(t_ast *ast)
{
	dup2(ast->shell->std_fd[0], 0);
	dup2(ast->shell->std_fd[1], 1);
	dup2(ast->shell->std_fd[2], 2);
	close(ast->shell->std_fd[0]);
	close(ast->shell->std_fd[1]);
	close(ast->shell->std_fd[2]);
	//ft_bzero(ast->shell->std_fd, sizeof(*ast->shell->std_fd) * 3);
	ast->shell->std_fd[0] = 0;
	ast->shell->std_fd[1] = 0;
	ast->shell->std_fd[2] = 0;
}

void	ft_pre_execution(t_ast *ast)
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

int		ft_execution(t_ast *ast)
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
			ft_restore_std_fd(ast);
			return (ret_cmd);
		}
	}
	return (CMD_SUCCESS);
}

void	ft_cmd_line_execution(t_ast **ast, t_shell *shell)
{
	if (shell->flags->token || shell->flags->ast)
		ft_putendl_col("\n---- EXEC ----\n", B_YELLOW, DEF);
	ft_fill_cmd_return(ft_execution(*ast), shell);
	if (shell->flags->token || shell->flags->ast)
		ft_putendl_col("\n--------------\n", B_YELLOW, DEF);
	ft_del_ast(ast);
}
