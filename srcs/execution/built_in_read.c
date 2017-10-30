#include "shell.h"

static char	**ft_read_get_fields(char *r)
{
	char	*line;
	char	**field;

	(void)r;
	field = NULL;
	if (get_next_line(STDIN_FILENO, &line) == 1)
	{
		field = ft_strsplit(line, ' ');
	}
	ft_strdel(&line);
	return (field);
}

static int	ft_read_assign_field_to_var(char **var, char **field)
{
	char	*tmp;
	int		nb_var;
	int		nb_field;
	int		i;
	
	if (!*var)
	{
		tmp = ft_tab_to_str(field);
		ft_putendl2_fd("add ", "REPLY", 1);
		ft_chg_varval_or_add(&g_shell->var_loc, "REPLY", tmp);
		free (tmp);
		return (CMD_SUCCESS);
	}
	i = 0;
	nb_var = ft_tablen(var);
	nb_field = ft_tablen(field);
	while (var[i])
	{
		if (!ft_is_valid_name(var[i]))
		{
			tmp = ft_strjoin3("`", var[i], "'");
			ft_put_errmsg(SHELL_NAME": read", tmp, "not a valid identifier");
			free(tmp);
			return (CMD_FAILURE);
		}
		if (nb_var == 1 && nb_field > 1)
		{
			tmp = ft_tab_to_str(field + i);
			ft_putendl2_fd("add ", var[i], 1);
			ft_chg_varval_or_add(&g_shell->var_loc, var[i], tmp);
			free (tmp);
			break ;
		}
		else if (nb_var && !nb_field)
		{
			ft_putendl2_fd("add ", var[i], 1);
			ft_chg_varval_or_add(&g_shell->var_loc, var[i], "");
			nb_var--;
		}
		else
		{
			ft_putendl2_fd("add ", var[i], 1);
			ft_chg_varval_or_add(&g_shell->var_loc, var[i], field[i]);
			nb_var--;
			nb_field--;
		}
		++i;
	}
	return (CMD_SUCCESS);
}

int		ft_builtin_read(t_ast *ast)
{
	char	*flags;
	char	**var;
	int		flag_error;
	char	**field;
	int		ret;


	flags = ft_get_flags(ast->argtab + 1);
	if ((flag_error = ft_check_illegal_flags(flags, "r")) != 0)
	{
		ft_put_usage("read", flag_error, "r");
		ft_strdel(&flags);
		return (CMD_FAILURE);
	}
	var = ft_get_arg(ast->argtab + 1, flag_error);

	field = ft_read_get_fields(flags);

	ret = ft_read_assign_field_to_var(var, field);
	
	ft_tabdel(&field);
	ft_strdel(&flags);
	return (ret);
}
