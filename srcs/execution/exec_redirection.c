/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 22:34:06 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/26 17:00:05 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_connect_fd(char *output, int to, int from, t_shell *shell)
{
	if (dup2(to, from) == -1)
	{
		if (errno == EBADF)
			ft_put_errmsg(shell->name, output, "Bad file descriptor");
		else
			ft_put_errmsg(shell->name, output, "dup error");
		return (-1);
	}
	return (0);
}

int		ft_create_file(enum e_op op, char *output, t_shell *shell)
{
	int		fd;

	fd = 0;
	if (op == GREAT)
		fd = open(output, O_RDWR | O_CREAT | O_TRUNC, 0666);
	else if (op == LESS)
		fd = open(output, O_RDONLY);
	else if (op == DGREAT)
		fd = open(output, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
	{
		if (errno == EACCES)
			ft_put_errmsg(shell->name, output, "Permission denied");
		else if (errno == ENOENT)
			ft_put_errmsg(shell->name, output, "No such file or directory");
		else if (errno == EISDIR)
			ft_put_errmsg(shell->name, output, "Is a directory");
		else
			ft_put_errmsg(shell->name, output, "open error");
		return (-1);
	}
	return (fd);
}

int		ft_apply_fd_aggr(t_redir *redir, t_shell *shell)
{
	if (ft_strcmp(redir->output, "-") == 0)
	{
		if (close(redir->io_nbr) == -1)
		{
			ft_put_errmsg(shell->name, redir->output, "close error");
			return (-1);
		}
		return (0);
	}
	else if (ft_is_uns_nbr(redir->output) == 0 || !ft_strcmp(redir->output, ""))
	{
		ft_put_errmsg(shell->name, redir->output, "ambiguous redirect");
		return (-1);
	}
	return (ft_connect_fd(redir->output, ft_atoi(redir->output), redir->io_nbr,
																	shell));
}

/*
** ft_apply_hdoc :
** À l'execution. Gère les here-doc.
** Retourne -1 si erreur, 0 sinon.
*/

int		ft_apply_hdoc(t_redir *redir, t_shell *shell)
{
	int		ret;
	int		pfd[2];

	if (pipe(pfd) == -1)
	{
		ft_put_errmsg(shell->name, redir->output, "pipe error");
		return (-1);
	}
	if (redir->hdoc)
		write(pfd[1], redir->hdoc, ft_strlen(redir->hdoc));
	close(pfd[1]);
	ret = ft_connect_fd(redir->output, pfd[0], redir->io_nbr, shell);
	close(pfd[0]);
	return (ret);
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

int		ft_do_redirection(t_redir *redir, t_shell *shell)
{
	int		ret;

	while (redir)
	{
		if (ft_check_fd(redir, shell) == -1)
			return (-1);
		if (redir->op == GREATAND || redir->op == LESSAND)
			ret = ft_apply_fd_aggr(redir, shell);
		else if (redir->op == DLESS)
			ret = ft_apply_hdoc(redir, shell);
		else
		{
			redir->fd = ft_create_file(redir->op, redir->output, shell);
			ft_putnbr2("redir->fd = ", redir->fd);
			ret = -1;
			if (redir->fd != -1)
				ret = ft_connect_fd(redir->output, redir->fd,
									redir->io_nbr, shell);
		}
		if (ret == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
