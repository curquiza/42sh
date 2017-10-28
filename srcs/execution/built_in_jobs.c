#include "shell.h"

int		ft_builtin_jobs(t_ast *ast)
{
	(void)ast;
	ft_putendl("BUILTIN JOBS");
	return (CMD_SUCCESS);
}
