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

static char	*ft_get_eventname(char *s)
{
	int		len;

	if (!s || *s != '!')
		return (NULL);
	s++;
	len = 0;
	while (s[len] && ft_isdigit(s[len]) == 1)
		len++;
	return (ft_strsub(s, 0, len));
}

static int	ft_check_eventname(char *s, int histolen)
{
	if (!s || ft_strlen(s) > 10)
		return (-1);
	if (ft_is_uns_nbr(s) == 0)
		return (-1);
	if (ft_atoi(s) > histolen || ft_atoi(s) <= 0)
		return (-1);
	return (0);
}

static char	*ft_expand_histoevent(char **s, t_histo_ctrl *ctrl)
{
	char	*tmp;
	char	*eventname;
	//char	*rslt;

	tmp = ft_find_exclamchar(*s);
	eventname = ft_get_eventname(tmp);
	if (ft_check_eventname(eventname, ctrl->len) == -1)
		return (eventname);
	//rslt = ft_strsub(*s, 0, tmp - *s);
	//ft_putendl2_fd("rslt = ", rslt, 1);
	return (NULL);
}


// histo->start = le dernier inscrit dans la liste = le plus recent
// !1 dans bash = le dernier = le moins recent

char	*ft_check_histoevent_err(t_lexeme *lex, t_histo_ctrl *ctrl)
{
	char	*error;

	while (lex)
	{
		if (ft_find_exclamchar(lex->s) != NULL)
		{
			if ((error = ft_expand_histoevent(&lex->s, ctrl)) != NULL)
				return (error);
		}
		lex = lex->next;
	}
	//return (ft_strdup("toto"));
	return (NULL);
}
