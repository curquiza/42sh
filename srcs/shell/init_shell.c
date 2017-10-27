/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 23:01:06 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/25 16:56:44 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**ft_init_priv(void)
{
	char	**priv;
	char	*uid_char;
	char	*pwd;
	char	*tmp;

	priv = NULL;
	ft_add_var(&priv, "?", "0");
	uid_char = ft_itoa(getuid());
	ft_add_var(&priv, "UID", uid_char);
	ft_strdel(&uid_char);
	if ((pwd = getcwd(NULL, MAXPATHLEN)))
	{
		tmp = ft_strjoin3(pwd, "/", HISTO_FILE_NAME);
		ft_add_var(&priv, "42SH_HISTO_FILE", tmp);
		ft_strdel(&tmp);
		ft_strdel(&pwd);
	}
	return (priv);
}

char	**ft_init_env(char **environ)
{
	char	**env;
	char	*charval;
	int		intval;
	char	*pwd;

	env = ft_tabdup(environ);
	intval = 0;
	charval = ft_get_varvalue(env, "SHLVL");
	if (charval)
		intval = ft_atoi(charval);
	intval++;
	charval = ft_itoa(intval);
	ft_chg_varval_or_add(&env, "SHLVL", charval);
	pwd = getcwd(NULL, MAXPATHLEN);
	if (pwd)
		ft_chg_varval_or_add(&env, "PWD", pwd);
	else
		ft_chg_varval_or_add(&env, "PWD", "");
	free(pwd);
	free(charval);
	return (env);
}

t_flag	*ft_init_flags(int ac, char **av)
{
	int		i;
	t_flag	*new;

	new = ft_memalloc(sizeof(*new));
	i = 1;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], FLAG_TOKEN))
			new->token = 1;
		else if (!ft_strcmp(av[i], FLAG_AST))
			new->ast = 1;
		i++;
	}
	return (new);
}

static void	ft_fill_history_from_file(t_shell *shell)
{
	char	*histo_file;

	if ((histo_file = ft_get_varvalue(shell->var_priv, "42SH_HISTO_FILE")))
		ft_histo_file_read(shell->histo_ctrl, histo_file);
}

t_shell	*ft_init_shell(int ac, char **av, char **environ, char *name)
{
	t_shell		*shell;

	shell = ft_memalloc(sizeof(*shell));
	shell->name = ft_strdup(name);
	shell->run = 1;
	shell->var_env = ft_init_env(environ);
	shell->var_priv = ft_init_priv();
	shell->flags = ft_init_flags(ac, av);
	shell->tc_tool = ft_memalloc(sizeof(*shell->tc_tool));
	shell->histo_ctrl = ft_memalloc(sizeof(*shell->histo_ctrl));
	shell->comp_ctrl = ft_memalloc(sizeof(*shell->comp_ctrl));
	ft_fill_history_from_file(shell);
	shell->gpid = getpid();
	ft_putnbr2("shell->gpid = ", shell->gpid);
	return (shell);
}
