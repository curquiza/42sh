#include "shell.h"

int		ft_builtin_fg(t_ast *ast)
{
	(void)ast;
	ft_putendl("BUILTIN FG");
	return (CMD_SUCCESS);
}

int		ft_builtin_bg(t_ast *ast)
{
	(void)ast;
	ft_putendl("BUILTIN BG");
	return (CMD_SUCCESS);
}
