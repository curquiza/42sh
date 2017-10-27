#include "shell.h"

void	ft_save_std_fd(t_ast *ast)
{
	int			i;

	i = 0;
	while (i < 10)
	{
		ast->shell->std_fd[i] = fcntl(i, F_DUPFD_CLOEXEC, 10);
		i++;
	}
}

void	ft_restore_fd(t_ast *ast)
{
	t_redir		*redir;
	int			i;

	i = -1;
	while (++i < 10)
		dup2(ast->shell->std_fd[i], i);
	i = -1;
	while (++i < 10)
	{
		if (ast->shell->std_fd[i] != -1)
			close(ast->shell->std_fd[i]);
	}
	i = -1;
	while (++i < 10)
		ast->shell->std_fd[i] = 0;
	redir = ast->redir_list;
	while (redir)
	{
		if (redir->fd != -1 && redir->fd != 0)
			close(redir->fd);
		redir = redir->next;
	}
}

int		ft_check_fd(t_redir *redir, t_shell *shell)
{
	char	*tmp;

	if (redir->io_nbr > FD_MAX - 1)
	{
		tmp = ft_itoa(redir->io_nbr);
		ft_put_errmsg(shell->name, tmp, "Not a valid file descriptor");
		ft_strdel(&tmp);
		return (-1);
	}
	if ((redir->op == GREATAND || redir->op == LESSAND)
		&& (ft_atoi(redir->output) > FD_MAX - 1))
	{
		ft_put_errmsg(shell->name, redir->output, "Invalid file descriptor");
		return (-1);
	}
	return (0);
}
