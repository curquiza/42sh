/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:45:26 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/21 11:41:42 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**ft_get_new_env(char **arg, char *flags, t_shell *shell)
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
	ft_suppr_var(&new_shell->var_env, "PWD");
	ft_suppr_var(&new_shell->var_env, "SHLVL");
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

char		**ft_get_utility(char **arg)
{
	int		i;

	if (!arg)
		return (NULL);
	i = 0;
	while (arg[i])
	{
		if (!ft_strchr(arg[i], '='))
			break ;
		i++;
	}
	return (arg + i);
}

int			ft_exec_utility_env(t_shell *shell, char **arg)
{
	char		*line;
	char		*tmp;
	t_lexeme	*lex;
	t_ast		*ast;
	int			ret;

	line = NULL;
	while (*arg)
	{
		tmp = line;
		line = ft_strjoin3(tmp, " ", *arg);
		ft_strdel(&tmp);
		arg++;
	}
	lex = NULL;
	ft_lexer(&lex, line);
	ft_ast(lex, &ast, shell);
	ret = 0;
	if (!ast)
		ft_lexlstdel(&lex);
	else
		ret = ft_execution(ast);
	ft_del_ast(&ast);
	ft_strdel(&line);
	return (ret);
}

int			ft_builtin_env(t_ast *ast)
{
	char	*flags;
	char	**arg;
	int		flag_error;
	t_shell	*new_shell;
	int		ret;

	flags = ft_get_flags(ast->argtab + 1);
	if ((flag_error = ft_check_illegal_flags(flags, "i")) != 0)
	{
		ft_put_usage("env", flag_error, "i");
		ft_strdel(&flags);
		return (CMD_FAILURE);
	}
	arg = ft_get_arg(ast->argtab + 1, flag_error);
	new_shell = ft_get_new_shell(arg, flags, ast->shell);
	ret = 0;
	arg = ft_get_utility(arg);
	if (arg && !(*arg))
		ft_puttab(new_shell->var_env);
	else
		ret = ft_exec_utility_env(new_shell, arg);
	ft_del_shell(&new_shell);
	ft_strdel(&flags);
	return (ret != 0 ? CMD_FAILURE : CMD_SUCCESS);
}
