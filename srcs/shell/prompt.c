/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:09:21 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/21 16:52:07 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*ft_get_pwd(void)
{
	char	*var_pwd;

	var_pwd = ft_get_varvalue(g_shell->var_env, "PWD");
	if (!var_pwd || access(var_pwd, F_OK) != 0)
		return (getcwd(NULL, MAXPATHLEN));
	return (ft_strdup(var_pwd));
}

void		ft_put_cut_path(void)
{
	int		i;
	int		slash;
	char	*path;

	path = ft_get_pwd();
	if (path)
	{
		slash = 0;
		i = ft_strlen(path) - 1;
		if (i > 0 && path[i] == '/')
			i--;
		while (i > 0)
		{
			if (path[i] == '/')
				slash++;
			if (slash == 2)
				break ;
			i--;
		}
		ft_putchar(' ');
		i != 0 ? ft_putstr_col("..", B_CYAN, DEF) : 0;
		ft_putstr_col(path + i, B_CYAN, DEF);
	}
	ft_strdel(&path);
}

void		ft_put_user(void)
{
	int				uid;
	struct passwd	*pw;

	uid = ft_atoi(ft_get_varvalue(g_shell->var_priv, "UID"));
	if ((pw = getpwuid(uid)))
	{
		ft_putstr_col("@", B_YELLOW, DEF);
		ft_putstr_col(pw->pw_name, B_YELLOW, DEF);
	}
}

void		ft_put_prompt(void)
{
	ft_put_user();
	ft_put_cut_path();
	ft_putendl("");
	if (ft_atoi(ft_get_varvalue(g_shell->var_priv, "?")) != 0)
		ft_putstr_col("T.T >> ", RED, DEF);
	else
		ft_putstr_col("^.^ >> ", GREEN, DEF);
}
