#include "shell.h"

int		ft_builtin_read(t_ast *ast)
{
	char	*line;
	char	**var;
	char	**field;
	int		i;

	if (get_next_line(STDIN_FILENO, &line) == 1)
	{
		field = ft_strsplit(line, ' ');
	}
	var = ast->argtab + 1;
	i = 0;
	while (var[i])
	{
		var[i] ? ft_putstr(var[i]) : 0;
		var[i] ? ft_putstr("=") : 0;
		field[i] ? ft_putstr(field[i]) : 0;
		write(1, "\n", 1);
		++i;
	}
	return (CMD_SUCCESS);
}
