#include "shell.h"

static void	ft_print_histo(t_histo_ctrl *ctrl)
{
	t_histo	*tmp;
	int		i;

	i = 0;
	tmp = ctrl->end;
	while (tmp)
	{
		ft_putnbr(++i);
		ft_putendl2_fd("\t", tmp->line, 1);
		tmp = tmp->prev;
	}
}

static int	ft_histo_delete_lines(char *flags, char **arg)
{
	int		ret;

	ret = CMD_SUCCESS;
	if (ft_strchr(flags, 'c'))
		ft_histo_inside_clearall(g_shell->histo_ctrl);
	else if (ft_strchr(flags, 'd'))
	{
		if (!arg[0] || !ft_is_uns_nbr(arg[0]))
		{
			ft_putendl_fd(SHELL_NAME": history: numeric offset required", 2);
			ret = CMD_FAILURE;
		}
		else
			ret = ft_histo_inside_delone(g_shell->histo_ctrl, ft_atoi(arg[0]));
	}
	return (ret);
}

static void	ft_histo_add_lines(char *flags, char **arg)
{
	char	*line;

	if (ft_strchr(flags, 's') && arg && arg[0])
	{
		if ((line = ft_tab_to_str(arg)))
		{
			ft_histo_inside_addline(g_shell->histo_ctrl, line);
			ft_strdel(&line);
		}
	}
}

static int	ft_manage_histo_file(char *flags, char **arg)
{
	char	*a;
	char	*r;
	char	*w;

	a = ft_strchr(flags, 'a');
	r = ft_strchr(flags, 'r');
	w = ft_strchr(flags, 'w');
	if (a && (!r || a < r) && (!w || a < w) && arg[0])
		return (ft_histo_file_write(g_shell->histo_ctrl, arg[0], HISTO_APPEND));
	else if (w && (!a || w < a) && (!r || w < r) && arg[0])
		return (ft_histo_file_write(g_shell->histo_ctrl, arg[0], HISTO_WRITE));
	else if (r && (!a || r < a) && (!w || r < w) && arg[0])
		return (ft_histo_file_read(g_shell->histo_ctrl, arg[0]));
	else if (a || r || w)
	{
		ft_putendl_fd(SHELL_NAME": history: missing filename", 2);
		return (CMD_FAILURE);
	}
	return (CMD_SUCCESS);
}

int			ft_builtin_history(t_ast *ast)
{
	char	*flags;
	char	**arg;
	int		flag_error;
	int		ret_del;
	int		ret_file;

	flags = ft_get_flags(ast->argtab + 1);
	if ((flag_error = ft_check_illegal_flags(flags, "acdrsw")) != 0)
	{
		ft_put_usage("history", flag_error, HISTO_USAGE);
		ft_strdel(&flags);
		return (CMD_FAILURE);
	}
	arg = ft_get_arg(ast->argtab + 1, flag_error);
	if (!*flags)
	{
		ft_print_histo(g_shell->histo_ctrl);
		ft_strdel(&flags);
		return (CMD_SUCCESS);
	}
	ret_del = ft_histo_delete_lines(flags, arg);
	ft_histo_add_lines(flags, arg);
	ret_file = ft_manage_histo_file(flags, arg);
	ft_strdel(&flags);
	return (ret_del == CMD_FAILURE ? ret_del : ret_file);
}
