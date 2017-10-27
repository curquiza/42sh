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
	return (field);
}

static void	ft_read_assign_field_to_var(char **var, char **field)
{
	int		i;
	i = 0;
	while (var[i])
	{
		var[i] ? ft_putstr(var[i]) : 0;
		var[i] ? ft_putstr("=") : 0;
		field[i] ? ft_putstr(field[i]) : 0;
		write(1, "\n", 1);
		++i;
	}
}

int		ft_builtin_read(t_ast *ast)
{
	char	*flags;
	char	**var;
	int		flag_error;
	char	**field;


	flags = ft_get_flags(ast->argtab + 1);
	if ((flag_error = ft_check_illegal_flags(flags, "r")) != 0)
	{
		ft_put_usage("read", flag_error, "r");
		ft_strdel(&flags);
		return (CMD_FAILURE);
	}
	var = ft_get_arg(ast->argtab + 1, flag_error);

	field = ft_read_get_fields(flags);

	ft_read_assign_field_to_var(var, field);

	return (CMD_SUCCESS);
}
