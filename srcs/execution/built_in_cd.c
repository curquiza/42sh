/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:43:54 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/20 17:46:24 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_check_err_cd(char *path, t_shell *shell)
{
	struct stat		info;

	if (!path)
		return (-1);
	errno = 0;
	if (stat(path, &info) == -1)
	{
		if (errno == 13)
			ft_put_cd_errmsg(shell->name, path, "permission denied");
		else
			ft_put_cd_errmsg(shell->name, path, "no such file or directory");
		return (-1);
	}
	if (!S_ISDIR(info.st_mode))
	{
		ft_put_cd_errmsg(shell->name, path, "not a directory");
		return (-1);
	}
	if (access(path, X_OK) == -1)
	{
		ft_put_cd_errmsg(shell->name, path, "permission denied");
		return (-1);
	}
	return (0);
}

void	ft_fill_oldpwd(char *pwd, t_shell *shell)
{
	char	*pwd_var;

	if ((pwd_var = ft_get_varvalue(shell->var_env, "PWD")) != NULL)
		ft_chg_varval_or_add(&shell->var_env, "OLDPWD", pwd_var);
	else if (pwd)
		ft_chg_varval_or_add(&shell->var_env, "OLDPWD", pwd);
	else
		ft_suppr_var(&shell->var_env, "OLDPWD");
}

char	*ft_pass_slash(char *path)
{
	while (*path == '/')
		path++;
	return (path);
}

char	*ft_clean_path(char *path)
{
	char	*new;
	int		i;

	new = ft_strnew(MAXPATHLEN);
	i = 0;
	while (*path && i < MAXPATHLEN)
	{
		if (*path == '/')
		{
			path = ft_pass_slash(path);
			new[i++] = '/';
		}
		else if (*path 
				&& (!ft_strncmp(path, "./", 2)
					|| (*path == '.' && *(path + 1) == '\0')))
			path = ft_pass_slash(path + 1);
		else
		{
			new[i] = *path;
			path++;
			i++;
		}
	}
	return (new);
}

char	*ft_get_modifpath(char *path, char *flags, char *pwd)
{
	char	*new_path;
	char	*rslt;

	if (ft_strrchr(flags, 'P') > ft_strrchr(flags, 'L'))
		return (getcwd(NULL, MAXPATHLEN));
	new_path = ft_clean_path(path);
	ft_putendl2_fd("new path = ", new_path, 2);
	if (new_path && new_path[0] == '/')
		return (new_path);
	rslt = ft_strjoin3(pwd, "/", new_path);
	ft_strdel(&new_path);
	return (rslt);
}

int		ft_go_to_dir(t_shell *shell, char *path, char *flags)
{
	char	*pwd;
	char	*modif_path;

	if (ft_check_err_cd(path, shell) == -1)
		return (CMD_FAILURE);
	pwd = getcwd(NULL, MAXPATHLEN);
	ft_fill_oldpwd(pwd, shell);
//	if (pwd)
//		ft_chg_varval_or_add(&shell->var_env, "OLDPWD", pwd);
	if (chdir(path) == -1)
	{
		ft_put_errmsg(shell->name, "cd", "chdir error");
		ft_strdel(&pwd);
		return (CMD_FAILURE);
	}
	//pwd = getcwd(NULL, MAXPATHLEN);
	//if (pwd)
	//	ft_chg_varval_or_add(&shell->var_env, "PWD", pwd);
	//ft_strdel(&pwd);
	modif_path = ft_get_modifpath(path, flags, pwd);
	if (modif_path)
		ft_chg_varval_or_add(&shell->var_env, "PWD", modif_path);
	ft_strdel(&modif_path);
	ft_strdel(&pwd);
	return (CMD_SUCCESS);
}

int		ft_go_to_home(t_shell *shell, char *flags)
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

int		ft_go_to_oldpwd(t_shell *shell, char *flags)
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

int		ft_builtin_cd(t_ast *ast)
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
