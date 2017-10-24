/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd_tool.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 16:02:20 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/24 14:30:07 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*ft_pass_slash(char *path)
{
	while (*path == '/')
		path++;
	return (path);
}

static void	ft_go_back(char *new, int *i)
{
	if (*i == 0)
		return ;
	(*i)--;
	new[*i] = '\0';
	if (*i)
		(*i)--;
	else
		return ;
	while (*i > 0 && new[*i] != '/')
	{
		new[*i] = '\0';
		(*i)--;
	}
}

static char	*ft_clean_path(char *path)
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
		else if (!ft_strncmp(path, "./", 2) || !ft_strcmp(path, "."))
			path = ft_pass_slash(path + 1);
		else if (!ft_strncmp(path, "../", 3) || !ft_strcmp(path, ".."))
		{
			ft_go_back(new, &i);
			path += 2;
		}
		else
			new[i++] = *(path++);
	}
	return (new);
}

char		*ft_get_modifpath(char *path, char *flags, char *oldpwd)
{
	char	*tmp;
	char	*rslt;

	if (ft_strrchr(flags, 'P') > ft_strrchr(flags, 'L'))
		return (getcwd(NULL, MAXPATHLEN));
	if (path && path[0] == '/')
		return (ft_clean_path(path));
	if (!oldpwd)
		tmp = ft_strdup(path);
	else
		tmp = ft_strjoin3(oldpwd, "/", path);
	rslt = ft_clean_path(tmp);
	ft_strdel(&tmp);
	return (rslt);
}

int			ft_check_err_cd(char *path, t_shell *shell)
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
