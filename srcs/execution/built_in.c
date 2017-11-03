/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 16:18:42 by curquiza          #+#    #+#             */
/*   Updated: 2017/11/03 12:23:24 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static enum e_builtin	ft_is_built_in2(char *s)
{
	if (!ft_strcmp(s, "unset"))
		return (B_UNSET);
	if (!ft_strcmp(s, "export"))
		return (B_EXPORT);
	if (!ft_strcmp(s, "history"))
		return (B_HISTORY);
	if (!ft_strcmp(s, "read"))
		return (B_READ);
	if (!ft_strcmp(s, "fg"))
		return (B_FG);
	if (!ft_strcmp(s, "bg"))
		return (B_BG);
	if (!ft_strcmp(s, "jobs"))
		return (B_JOBS);
	return (NOT_BUILTIN);
}

enum e_builtin			ft_is_built_in(char *s)
{
	enum e_builtin	ret;

	if (s)
	{
		if (!ft_strcmp(s, "echo"))
			return (B_ECHO);
		if (!ft_strcmp(s, "cd"))
			return (B_CD);
		if (!ft_strcmp(s, "env"))
			return (B_ENV);
		if (!ft_strcmp(s, "setenv"))
			return (B_SETENV);
		if (!ft_strcmp(s, "unsetenv"))
			return (B_UNSETENV);
		if (!ft_strcmp(s, "exit"))
			return (B_EXIT);
		if (!ft_strcmp(s, "set"))
			return (B_SET);
		ret = ft_is_built_in2(s);
		if (ret != NOT_BUILTIN)
			return (ret);
	}
	return (NOT_BUILTIN);
}

static int				ft_exec_built_in2(t_ast *ast, enum e_builtin ret)
{
	if (ret == B_UNSET)
		return (ft_builtin_unset(ast));
	if (ret == B_EXPORT)
		return (ft_builtin_export(ast));
	if (ret == B_HISTORY)
		return (ft_builtin_history(ast));
	if (ret == B_READ)
		return (ft_builtin_read(ast));
	if (ret == B_FG)
		return (ft_builtin_fg(ast));
	if (ret == B_BG)
		return (ft_builtin_bg(ast));
	if (ret == B_JOBS)
		return (ft_builtin_jobs(ast));
	return (0);
}

int						ft_exec_built_in(t_ast *ast, enum e_builtin ret)
{
	int	ret_builtin;

	if (ret == B_ECHO)
		return (ft_builtin_echo(ast));
	if (ret == B_CD)
		return (ft_builtin_cd(ast));
	if (ret == B_ENV)
		return (ft_builtin_env(ast));
	if (ret == B_SETENV)
		return (ft_builtin_setenv(ast));
	if (ret == B_UNSETENV)
		return (ft_builtin_unsetenv(ast));
	if (ret == B_EXIT)
		return (ft_builtin_exit(ast));
	if (ret == B_SET)
		return (ft_builtin_set(ast));
	ret_builtin = ft_exec_built_in2(ast, ret);
	if (ret_builtin != 0)
		return (ret_builtin);
	return (0);
}
