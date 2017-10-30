#include "shell.h"

static int		ft_exec_scmd_pipeline(t_ast *ast)
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

static int	ft_launch_pipeline(t_ast *ast)
{
	int		pfd[2];
	pid_t	pid;
	
	(pipe(pfd) == -1) ? ft_put_errmsg(ast->shell->name, NULL, "pipe error") : 0;
	if ((pid = fork()) == -1)
		ft_put_errmsg(ast->shell->name, NULL, "fork error");
	else if (pid == 0)
	{
		close(pfd[0]);
		dup2(pfd[1], 1);
		exit(ft_exec_scmd_pipeline(ast->left));
	}
	else if (pid > 0)
	{
		if (ft_check_cmd_slash(ast->left) != FOUND
				&& ft_check_cmd_noslash(ast->left) != FOUND)
			waitpid(pid, NULL, WUNTRACED);
		close(pfd[1]);
		dup2(pfd[0], 0);
		if (ast && ast->right && ast->right->lex && ast->right->lex->op == PIPE)
			exit(ft_launch_pipeline(ast->right));
		exit(ft_exec_scmd_pipeline(ast->right));
	}
	return (CMD_SUCCESS);
}

static void	ft_pre_execution_pipeline(t_ast *ast)
{
	while (ast && ast->lex && ast->lex->op == PIPE)
	{
		ft_pre_execution(ast->left);
		ast = ast->right;
	}
	if (ast)
		ft_pre_execution(ast);
}

int		ft_apply_pipe(t_ast *ast)
{
	pid_t	pid;
	int		ret;

	ret = CMD_SUCCESS;
	ft_pre_execution_pipeline(ast);
	if ((pid = fork()) == -1)
		ft_put_errmsg(ast->shell->name, NULL, "fork error");
	else if (pid == 0)
		exit(ft_launch_pipeline(ast));
	else if (pid > 0)
		ret = ft_process_controller(pid, ast);
	return (ft_get_cmdret(ret));
}
