#include "shell.h"

char	**ft_strsplit_escape(char *s)
{
	char	**field;
	char	*tmp;
	int		len;
	int		escape;

	field = NULL;
	while (*s)
	{
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
		while (*s == ' ')
			++s;
	}
	return (field);
}

