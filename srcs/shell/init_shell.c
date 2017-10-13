/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 23:01:06 by curquiza          #+#    #+#             */
/*   Updated: 2017/07/26 15:08:47 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**ft_init_priv(void)
{
	char	**priv;
	char	*uid_char;

	priv = NULL;
	ft_add_var(&priv, "?", "0");
	uid_char = ft_itoa(getuid());
	ft_add_var(&priv, "UID", uid_char);
	ft_strdel(&uid_char);
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
	pwd = getcwd(NULL, 0);
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
	return (shell);
}
