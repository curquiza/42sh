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

int		ft_expand_histoevent(char **s)
{
	char	*tmp;
	char	*rslt;

	tmp = ft_find_exclamchar(*s);
	rslt = ft_strsub(*s, 0, tmp - *s);
	ft_putendl2_fd("rslt = ", rslt, 1);
	ft_strdel(&tmp);
	return (0);
}

char	*ft_check_histoevent_err(t_lexeme *lex)
{
	while (lex)
	{
		if (ft_find_exclamchar(lex->s) != NULL)
			ft_expand_histoevent(&lex->s);
		lex = lex->next;
	}
	return (NULL);
}
