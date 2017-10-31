#include "shell.h"

static char	**ft_strsplit_escape(char *s)
{
	char	**field;
	char	*tmp;
	int		len;
	int		escape;

	if (!s)
		return (NULL);
	field = NULL;
	while (*s)
	{
		while (*s == ' ')
			++s;
		len = 0;
		escape = 0;
		while (*(s + len) && (*(s + len) != ' ' || (*(s + len) == ' ' && escape)))
		{
			escape = 0;
			++len;
			if (*(s + len) == '\\')
			{
				escape = 1;
				++len;
			}
		}
		tmp = ft_strsub(s, 0, len);
		ft_escape_removal_only(&tmp);
		ft_add_var(&field, tmp, NULL);
		free(tmp);
		s = s + len;
	}
	return (field);
}

char	**ft_read_get_fields_opt_r(void)
{
	char	*line;
	char	**field;

	field = NULL;
	line = NULL;
	if (get_next_line(STDIN_FILENO, &line) == 1)
	{
		ft_clean_tab(line);
		field = ft_strsplit(line, ' ');
	}
	ft_strdel(&line);
	return (field);
}

static int	ft_is_end_of_fields(char *test)
{
	int		escape;

	escape = 0;
	while (*test)
	{
		if (*test == '\\' && !escape)
		{
			++test;
			if (*test == '\n')
			{
				*(test - 1) = '\0';
				*test = '\0';
				++test;
			}
			escape = 1;
		}
		else
		{
			++test;
			escape = 0;
		}
	}
	return (escape ? 0 : 1);
}

char	**ft_read_get_fields_no_opt(void)
{
	char	*line;
	char	*next_line;
	char	*tmp;
	char	**field;

	field = NULL;
	line = NULL;
	while (get_next_line(STDIN_FILENO, &next_line) == 1)
	{
		tmp = line;
		line = ft_strjoin3(line, next_line, "\n");
		free(tmp);
		if (ft_is_end_of_fields(line) == 1)
		{
			ft_strdel(&next_line);
			break ;
		}
		ft_strdel(&next_line);
		ft_putstr("> ");
	}
	ft_clean_tab(line);
	field = ft_strsplit_escape(line);
	ft_strdel(&line);
	return (field);
}
