#include "shell.h"

static void	ft_put_eventerror(char *name, char *event)
{
	ft_putendl_fd("", 2);
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
	ft_putstr_fd(": event not found", 2);
}

static char	*ft_get_eventname(char *s)
{
	int		len;

	if (!s || *s != '!')
		return (NULL);
	s++;
	len = 0;
	if (ft_isdigit(s[len]) == 1)
	{
		while (s[len] && ft_isdigit(s[len]) == 1)
			len++;
	}
	else
	{
		while (s[len] && ft_is_separator(s[len]) == 0)
			len++;
	}
	return (ft_strsub(s, 0, len));
}

static int	ft_check_eventname(char *eventname, int histolen)
{
	if (!eventname || ft_strlen(eventname) > 10)
		return (-1);
	if (ft_is_uns_nbr(eventname) == 0)
		return (-1);
	if (ft_atoi(eventname) > histolen || ft_atoi(eventname) <= 0)
		return (-1);
	return (0);
}

static int	ft_expand_event(char *s, char *eventname, t_histo_ctrl *ctrl)
{
	int		num_event;
	char	*tmp;
	t_histo	*histo;
	int		cnt;

	tmp = ft_strdup(s + 1 + ft_strlen(eventname));
	ft_bzero(s, ft_strlen(s));
	num_event = ft_atoi(eventname);
	histo = ctrl->end;
	cnt = 1;
	while (histo && cnt != num_event)
		cnt++;
	ft_strcpy(s, histo->line);
	ft_strcat(s, tmp);
	ft_strdel(&tmp);
	return (ft_strlen(histo->line));
}

void	ft_histo_event(t_tc *tool, t_histo_ctrl *ctrl)
{
	int		i;
	char	*eventname;

	(void)ctrl;
	i = 0;
	while (tool->buff[i])
	{
		if (tool->buff[i] == 39)
			i = ft_next_squote(i, tool->buff);
		if (tool->buff[i] == '!'
			&& tool->buff[i + 1] && ft_is_separator(tool->buff[i + 1]) == 0)
		{
			eventname = ft_get_eventname(tool->buff + i);
			if (ft_check_eventname(eventname, ctrl->len) == -1)
			{
				ft_put_eventerror(g_shell->name, eventname);
				ft_strdel(&eventname);
				break ;
			}
			i = i + ft_expand_event(tool->buff + i, eventname, ctrl);
			ft_strdel(&eventname);
		}
		i++;
	}
	tool->nbr_char = ft_strlen(tool->buff);
}
