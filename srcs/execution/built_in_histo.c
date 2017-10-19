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
	(void)ast;
	ft_print_histo(g_shell->histo_ctrl);
	return (CMD_SUCCESS);
}
