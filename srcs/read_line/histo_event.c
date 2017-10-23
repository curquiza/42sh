/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histo_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:51:02 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/23 18:01:21 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	{
		histo = histo->prev;
		cnt++;
	}
	ft_strcpy(s, histo->line);
	ft_strcat(s, tmp);
	ft_strdel(&tmp);
	return (ft_strlen(histo->line));
}

static int	ft_check_and_expand(char *buff, t_histo_ctrl *ctrl, int *i)
{
	char	*eventname;

	eventname = ft_get_eventname(buff + *i);
	if (ft_check_eventname(eventname, ctrl->len) == -1)
	{
		ft_put_eventerror(g_shell->name, eventname);
		ft_strdel(&eventname);
		return (-1);
	}
	*i = *i + ft_expand_event(buff + *i, eventname, ctrl) - 1;
	ft_strdel(&eventname);
	return (1);
}

void		ft_histo_event(t_tc *tool, t_histo_ctrl *ctrl)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (tool->buff[i])
	{
		if (tool->buff[i] == 39)
			i = ft_next_squote(i, tool->buff);
		if (tool->buff[i] == '!'
			&& tool->buff[i + 1] && ft_is_separator(tool->buff[i + 1]) == 0)
		{
			if ((ret = ft_check_and_expand(tool->buff, ctrl, &i)) == -1)
				break ;
		}
		i++;
	}
	tool->nbr_char = ft_strlen(tool->buff);
	if (ret == 1)
	{
		ft_putstr("\n");
		ft_putstr(tool->buff);
	}
	else if (ret == -1)
		g_shell->event_err = 1;
}
