#include "shell.h"

char	*ft_find_exclamchar(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 39)
			i = ft_next_squote(i, s);
		if (s[i] == '!')
			return (s + i);
		i++;
	}
	return (NULL);
}

char	*ft_check_histoevent_err(t_lexeme *lex)
{
	while (lex)
	{
		if (ft_find_exclamchar(lex->s) != NULL)
			;
		lex = lex->next;
	}
	return (NULL);
}
