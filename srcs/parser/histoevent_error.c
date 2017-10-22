#include "shell.h"

void	ft_put_eventerror(char *name, char *event)
{
	if (name)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (event)
	{
		ft_putstr_fd("!", 2);
		ft_putstr_fd(event, 2);
	}
	ft_putendl_fd(": event not found", 2);
}

static char	*ft_find_exclamchar(char *s)
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

static int		ft_expand_histoevent(char **s)
{
	//char	*tmp;
	//char	*rslt;

	(void)s;
	//tmp = ft_find_exclamchar(*s);
	//rslt = ft_strsub(*s, 0, tmp - *s);
	//ft_putendl2_fd("rslt = ", rslt, 1);
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
	//return (ft_strdup("toto"));
	return (NULL);
}
