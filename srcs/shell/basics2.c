#include "shell.h"

/*
**	ft_clean_tab remove `\t' from line (nothing is node for `\n')
*/

void	ft_clean_tab(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t' || !ft_isprint(line[i]))
			line[i] = ' ';
		++i;
	}
}

