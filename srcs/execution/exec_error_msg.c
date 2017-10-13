/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_msg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 22:39:45 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/27 20:08:58 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_put_errmsg(char *bin, char *s, char *msg)
{
	if (bin)
	{
		ft_putstr_fd(bin, 2);
		ft_putstr_fd(": ", 2);
	}
	if (s)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putendl_fd(msg, 2);
}

int		ft_putmsg_cmderr(char *cmd, enum e_cmd_search ret, t_shell *shell)
{
	if (ret == NOTFOUND)
	{
		ft_put_errmsg(shell->name, cmd, "command not found");
		return (127);
	}
	else if (ret == NOSUCHFILE)
	{
		ft_put_errmsg(shell->name, cmd, "no such file or directory");
		return (127);
	}
	else if (ret == NOPERM)
	{
		ft_put_errmsg(shell->name, cmd, "permission denied");
		return (126);
	}
	else if (ret == ISDIR)
	{
		ft_put_errmsg(shell->name, cmd, "is a directory");
		return (126);
	}
	return (0);
}

void	ft_put_readonly_errmsg(char *bin, char *cmd, char *varname)
{
	if (bin)
	{
		ft_putstr_fd(bin, 2);
		ft_putstr_fd(": ", 2);
	}
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (varname)
		ft_putstr_fd(varname, 2);
	ft_putendl_fd(" is a readonly variable", 2);
}

void	ft_put_invalidname_errmsg(char *bin, char *cmd, char *varname)
{
	if (bin)
	{
		ft_putstr_fd(bin, 2);
		ft_putstr_fd(": ", 2);
	}
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (varname)
		ft_putstr_fd(varname, 2);
	ft_putendl_fd(" is not a valid variable name", 2);
}

void	ft_put_cd_errmsg(char *bin, char *s, char *msg)
{
	if (bin)
	{
		ft_putstr_fd(bin, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd("cd: ", 2);
	if (s)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putendl_fd(msg, 2);
}
