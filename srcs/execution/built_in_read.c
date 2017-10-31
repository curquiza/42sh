#include "shell.h"

static int	ft_read_assign_to_reply(char **field)
{
	char	*tmp;

	tmp = field ? ft_tab_to_str(field) : NULL;
	ft_chg_varval_or_add(&g_shell->var_loc, "REPLY", tmp);
	free(tmp);
	return (CMD_SUCCESS);
}

static int	ft_read_put_invalid_identifier(char *var)
{
	char	*tmp;

	tmp = ft_strjoin3("`", var, "'");
	ft_put_errmsg(SHELL_NAME": read", tmp, "not a valid identifier");
	free(tmp);
	return (CMD_FAILURE);
}

static void	ft_join_field_and_add(char *var, char **field, int i)
{
	char	*tmp;

	tmp = ft_tab_to_str(field + i);
	ft_chg_varval_or_add(&g_shell->var_loc, var, tmp);
	free(tmp);
}

static int	ft_read_assign_field_to_var(char **var, int nb_var, char **field,\
		int nb_field)
{
	int		i;

	i = 0;
	while (var[i])
	{
		if (!ft_is_valid_name(var[i]))
			return (ft_read_put_invalid_identifier(var[i]));
		if (nb_var == 1 && nb_field > 1)
			ft_join_field_and_add(var[i], field, i);
		else if (nb_var && !nb_field)
		{
			ft_chg_varval_or_add(&g_shell->var_loc, var[i], "");
			nb_var--;
		}
		else
		{
			ft_chg_varval_or_add(&g_shell->var_loc, var[i], field[i]);
			nb_var--;
			nb_field--;
		}
		++i;
	}
	return (CMD_SUCCESS);
}

int			ft_builtin_read(t_ast *ast)
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
	field = (*flags ? ft_read_get_fields_opt_r() : ft_read_get_fields_no_opt());
	ret = (!*var ? ft_read_assign_to_reply(field) :\
			ft_read_assign_field_to_var(var, ft_tablen(var),\
				field, ft_tablen(field)));
	ft_tabdel(&field);
	ft_strdel(&flags);
	return (ret);
}
