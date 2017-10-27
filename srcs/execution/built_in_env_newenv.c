/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env_newenv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:54:08 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/27 12:47:39 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	**ft_get_new_env(char **arg, char *flags, t_shell *shell)
{
	char	**new_env;
	int		i;

	if (ft_strchr(flags, 'i'))
	{
		if (!(new_env = (char **)malloc(sizeof(**new_env))))
			ft_exit("malloc error", 1);
		new_env[0] = NULL;
	}
	else
		new_env = ft_tabdup(shell->var_env);
	i = 0;
	while (arg[i])
	{
		if (!ft_strchr(arg[i], '='))
			break ;
		ft_chg_varval_or_add(&new_env, arg[i], NULL);
		i++;
	}
	return (new_env);
}

static char	*ft_get_new_path(void)
{
	int		fd;
	char	*tmp;
	char	*line;
	char	*path;

	fd = open("/etc/paths", O_RDONLY);
	path = NULL;
	line = NULL;
	tmp = NULL;
	while (get_next_line(fd, &line) == 1)
	{
		tmp = path;
		if (tmp)
			path = ft_strjoin3(tmp, ":", line);
		else
			path = ft_strdup(line);
		ft_strdel(&tmp);
		ft_strdel(&line);
	}
	return (path);
}

t_shell		*ft_get_new_shell(char **arg, char *flags, t_shell *old_shell)
{
	t_shell	*new_shell;
	char	**new_env;
	char	**utility;
	char	*new_path;

	new_env = ft_get_new_env(arg, flags, old_shell);
	new_shell = ft_init_shell(0, NULL, new_env, SHELL_NAME);
	ft_tabdel(&new_shell->var_env);
	new_shell->var_env = ft_tabdup(new_env);
	ft_tabdel(&new_env);
	utility = ft_get_utility(arg);
	if (utility && utility[0] && ft_exist_in(new_shell->var_env, "PATH") == 0
		&& ft_is_built_in(utility[0]) == NOT_BUILTIN)
	{
		new_path = ft_get_new_path();
		ft_chg_varval_or_add(&new_shell->var_env, "PATH", new_path);
		ft_strdel(&new_path);
	}
	return (new_shell);
}
