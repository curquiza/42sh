/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_read_optr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 12:29:24 by sfranc            #+#    #+#             */
/*   Updated: 2017/11/03 12:29:26 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_gen_len_field: when read with no option
** Get the len of a field, which is a word that can include escape spaces.
*/

static int	ft_get_len_field(char *s)
{
	int	len;
	int	escape;

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
	return (len);
}

/*
** ft_strsplit_escape: when read with no option
** Split a string into an array of strings, using spaces as separator
** (tab and \n have previously been cleaned) BUT spaces can be escaped.
*/

static char	**ft_strsplit_escape(char *s)
{
	char	**field;
	char	*tmp;
	int		len;

	if (!s)
		return (NULL);
	field = NULL;
	while (*s)
	{
		while (*s == ' ')
			++s;
		len = ft_get_len_field(s);
		tmp = ft_strsub(s, 0, len);
		ft_escape_removal_only(&tmp);
		ft_add_var(&field, tmp, NULL);
		free(tmp);
		s = s + len;
	}
	return (field);
}

/*
** ft_is_end_of_fields: when read with no option
** Check if the \n is not escaped to mark end of user input
** when backslash processing is activated.
*/

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

/*
** ft_read_get_fields_no_opt: read mode with no option
** get next line for read with no option, meaning WITH backslash processing.
*/

char		**ft_read_get_fields_no_opt(void)
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

/*
** ft_read_get_fields_opt_r: read mode with option r
** get next line for read with NO backslash processing.
*/

char		**ft_read_get_fields_opt_r(void)
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
