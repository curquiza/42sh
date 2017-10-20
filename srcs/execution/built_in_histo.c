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

int			ft_builtin_history(t_ast *ast)
{
	char	*flags;
	char	**arg;
	int		flag_error;
	int		ret;
	char	*a;
	char	*r;
	char	*w;

	(void)ast;
	
	flags = ft_get_flags(ast->argtab + 1);
	if ((flag_error = ft_check_illegal_flags(flags, "acdrsw")) != 0)
	{
		ft_put_usage("history", flag_error,\
				"c] or [-d] [offset] or one of [-arw] [filename] or [-s");
		ft_strdel(&flags);
		return (CMD_FAILURE);
	}
	arg = ft_get_arg(ast->argtab + 1, flag_error);
	
	// run
	ret = CMD_SUCCESS;	
	// no flags
	if (!*flags)
	{
		ft_print_histo(g_shell->histo_ctrl);
		return (ret);
	}
	// delete all or one line
	if (ft_strchr(flags, 'c'))
	{
		ft_putendl("** delete l'histo");
	}
	else if (ft_strchr(flags, 'd'))
	{
		if (!arg[0] || !ft_is_uns_nbr(arg[0]))
		{
			ft_putendl_fd(SHELL_NAME": history: numeric offset required", 2);
			ret = CMD_FAILURE;
		}
		else
			// check is offset not out of range
			ft_putendl("** delete offset");
	}

	// add one line
	if (ft_strchr(flags, 's'))
	{
		ft_putendl("** add string");
	}
	// file write or read
	a = ft_strchr(flags, 'a');
	r = ft_strchr(flags, 'r');
	w = ft_strchr(flags, 'w');

	if (a && (!r || a < r) && (!w || a < w) && arg[0])
		ft_putendl("** append");
	else if (w && (!a || w < a) && (!r || w < r) && arg[0])
		ft_putendl("** overwrite");
	else if (r && (!a || r < a) && (!w || r < w) && arg[0])
		ft_putendl("** read");
	else if (a || r || w)
	{
		ft_putendl_fd(SHELL_NAME": history: missing filename", 2);
		ret = CMD_FAILURE;
	}

	return (ret);
}
