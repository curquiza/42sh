#include "shell.h"

int		ft_builtin_read(t_ast *ast)
{
	(void)ast;
	ft_putendl("builtin read");
	return (CMD_SUCCESS);
}
