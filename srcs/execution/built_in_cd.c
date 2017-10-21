/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:43:54 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/21 18:09:41 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_fill_oldpwd(t_shell *shell, char *pwd)
{
	char	*pwd_var;

	if ((pwd_var = ft_get_varvalue(shell->var_env, "PWD")) != NULL)
		ft_chg_varval_or_add(&shell->var_env, "OLDPWD", pwd_var);
	else if (pwd)
		ft_chg_varval_or_add(&shell->var_env, "OLDPWD", pwd);
	else
		ft_suppr_var(&shell->var_env, "OLDPWD");
}

static int	ft_go_to_dir(t_shell *shell, char *path, char *flags)
{
	char	*pwd;
	char	*modif_path;

	if (!path)
		return (CMD_FAILURE);
	//if (ft_check_err_cd(path, shell) == -1)
	//	return (CMD_FAILURE);
	//pwd = getcwd(NULL, MAXPATHLEN);
	//ft_fill_oldpwd(pwd, shell);
	pwd = getcwd(NULL, MAXPATHLEN);
	if (chdir(path) == -1)
	{
		if (ft_check_err_cd(path, shell) != -1)
			ft_put_errmsg(shell->name, "cd", "chdir error");
		ft_strdel(&pwd);
		return (CMD_FAILURE);
	}
	ft_fill_oldpwd(shell, pwd);
	modif_path = ft_get_modifpath(path, flags, pwd);
	if (modif_path)
		ft_chg_varval_or_add(&shell->var_env, "PWD", modif_path);
	ft_strdel(&modif_path);
	ft_strdel(&pwd);
	return (CMD_SUCCESS);
}

static int	ft_go_to_home(t_shell *shell, char *flags)
{
	int		ret;
	char	*path;

	if (!(path = ft_get_varvalue(shell->var_env, "HOME")))
	{
		ft_put_errmsg(shell->name, "cd", "HOME not set");
		return (CMD_FAILURE);
	}
	path = ft_strdup(path);
	ret = ft_go_to_dir(shell, path, flags);
	ft_strdel(&path);
	return (ret);
}

static int	ft_go_to_oldpwd(t_shell *shell, char *flags)
{
	int		ret;
	char	*path;

	if (!(path = ft_get_varvalue(shell->var_env, "OLDPWD")))
	{
		ft_put_errmsg(shell->name, "cd", "OLDPWD not set");
		return (CMD_FAILURE);
	}
	path = ft_strdup(path);
	ret = ft_go_to_dir(shell, path, flags);
	ft_strdel(&path);
	return (ret);
}

int			ft_builtin_cd(t_ast *ast)
{
	char	*flags;
	char	flag_error;
	char	**arg;
	int		ret;

	ret = CMD_SUCCESS;
	flags = ft_get_flags(ast->argtab + 1);
	if ((flag_error = ft_check_illegal_flags(flags, "LP")) != 0)
	{
		ft_put_usage("cd", flag_error, "LP");
		ft_strdel(&flags);
		return (CMD_FAILURE);
	}
	arg = ft_get_arg(ast->argtab + 1, flag_error);
	if (arg && !arg[0])
		ret = ft_go_to_home(ast->shell, flags);
	else if (arg && !ft_strcmp(arg[0], "-"))
		ret = ft_go_to_oldpwd(ast->shell, flags);
	else if (arg && arg[0])
		ret = ft_go_to_dir(ast->shell, arg[0], flags);
	ft_strdel(&flags);
	return (ret);
}
