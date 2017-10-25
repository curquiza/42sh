/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 21:28:24 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/25 18:26:20 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

enum e_cmd_search	ft_check_cmd_slash(t_ast *ast)
{
	struct stat	buff;

	errno = 0;
	if (stat(ast->cmd->s, &buff) == -1)
	{
		if (errno == 13)
			return (NOPERM);
		else
			return (NOSUCHFILE);
	}
	if (S_ISDIR(buff.st_mode))
		return (ISDIR);
	if (access(ast->cmd->s, X_OK) == -1)
		return (NOPERM);
	return (FOUND);
}

char				**ft_get_pathtab(t_shell *shell)
{
	char	*path_str;

	path_str = ft_get_varvalue(shell->var_env, "PATH");
	if (!path_str)
		path_str = ft_get_varvalue(shell->var_loc, "PATH");
	if (!path_str)
		return (NULL);
	return (ft_strsplit(path_str, ':'));
}

enum e_cmd_search	ft_check_path(char *cmd)
{
	int			ret_stat;
	int			ret_access;
	struct stat	buff;

	ret_stat = stat(cmd, &buff);
	ret_access = access(cmd, X_OK);
	if (ret_stat != -1 && ret_access != -1)
		return (FOUND);
	else if (ret_stat != -1 && ret_access == -1)
		return (NOPERM);
	return (0);
}

enum e_cmd_search	ft_check_cmd_noslash(t_ast *ast)
{
	char				**path_tab;
	char				*cmd;
	enum e_cmd_search	ret;
	int					i;

	if (ast->cmd && ast->cmd->s && !ft_strcmp(ast->cmd->s, ""))
		return (NOTFOUND);
	if (!(path_tab = ft_get_pathtab(ast->shell)))
		return (NOTFOUND);
	cmd = NULL;
	i = 0;
	ret = NOSUCHFILE;
	while (path_tab[i])
	{
		ft_strdel(&cmd);
		cmd = ft_strjoin3(path_tab[i], "/", ast->cmd->s);
		if ((ret = ft_check_path(cmd)) != 0)
			break ;
		i++;
	}
	if (ret == FOUND)
		ft_strdeldup(&ast->cmd->s, cmd);
	ft_strdel(&cmd);
	ft_tabdel(&path_tab);
	return (ret == 0 ? NOTFOUND : ret);
}

int					ft_do_cmd(t_ast *ast)
{
	enum e_cmd_search	error_ret;
	enum e_builtin		builtin_ret;

	if (ast && ast->cmd && ast->cmd->s)
	{
		ft_catch_signal_child();
		if (ft_strchr(ast->cmd->s, '/'))
			error_ret = ft_check_cmd_slash(ast);
		else if ((builtin_ret = ft_is_built_in(ast->cmd->s)) != NOT_BUILTIN)
			return (ft_exec_built_in(ast, builtin_ret));
		else
			error_ret = ft_check_cmd_noslash(ast);
		if (error_ret != FOUND)
			return (ft_putmsg_cmderr(ast->cmd->s, error_ret, ast->shell));
		execve(ast->cmd->s, ast->argtab, ast->shell->var_env);
	}
	return (CMD_SUCCESS);
}
