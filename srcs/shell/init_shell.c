/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 23:01:06 by curquiza          #+#    #+#             */
/*   Updated: 2017/11/03 14:06:52 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**ft_init_priv(void)
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

char		**ft_init_env(char **environ)
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

t_flag		*ft_init_flags(int ac, char **av)
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

static void	ft_init_for_job_ctrl(t_shell *shell)
{
	shell->terminal = STDOUT_FILENO;
	while (tcgetpgrp(shell->terminal) != (shell->pgid = getpgrp()))
		kill(-shell->pgid, SIGTTIN);
	shell->pgid = getpid();
	if (setpgid(shell->pgid, shell->pgid) < 0)
		ft_exit("Shell init : couldn't put the shell in its own process group",
				1);
	if (tcsetpgrp(shell->terminal, shell->pgid) == -1)
		ft_exit("Shell init : impossible to grab the control of the terminal",
				1);
	if (tcgetattr(shell->terminal, &shell->dfl_term) != 0)
		ft_exit("Shell init : imposible to get the termios structure", 1);
}

t_shell		*ft_init_shell(int ac, char **av, char **environ, int mode)
{
	t_shell		*shell;

	shell = ft_memalloc(sizeof(*shell));
	shell->name = ft_strdup(SHELL_NAME);
	shell->run = 1;
	shell->var_env = ft_init_env(environ);
	shell->var_priv = ft_init_priv();
	shell->flags = ft_init_flags(ac, av);
	shell->tc_tool = ft_memalloc(sizeof(*shell->tc_tool));
	shell->histo_ctrl = ft_memalloc(sizeof(*shell->histo_ctrl));
	shell->comp_ctrl = ft_memalloc(sizeof(*shell->comp_ctrl));
	if (mode == 1)
	{
		ft_fill_history_from_file(shell);
		ft_init_for_job_ctrl(shell);
	}
	return (shell);
}
