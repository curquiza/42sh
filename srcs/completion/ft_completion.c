/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <rcarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 16:04:01 by rcarette          #+#    #+#             */
/*   Updated: 2017/07/07 05:24:08 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static int		if_line_empty(t_line_edit *line)
{
	char	*getline;
	char	*temporary_getline;

	if (line->position == line->nbr_prompt)
		return (tputs(tgetstr("bl", NULL), 1, &ft_putchar));
	if (line->nbr_prompt == line->nbr_character)
		return (0);
	getline = ft_strdup(&line->buffer[line->nbr_prompt]);
	temporary_getline = getline;
	getline = ft_strtrim(temporary_getline);
	free(temporary_getline);
	if (ft_strlen(getline))
	{
		free(getline);
		return (1);
	}
	free(getline);
	return (tputs(tgetstr("bl", NULL), 1, &ft_putchar));
}

static void		free_struct_data(t_completion *data_compl)
{
	(data_compl->path != NULL) ? free(data_compl->path) : 0;
	(data_compl->string != NULL) ? free(data_compl->string) : 0;
	(data_compl->after_cursor != NULL) ? free(data_compl->after_cursor) : 0;
	(data_compl->buff_cursor != NULL) ? free(data_compl->buff_cursor) : 0;
}

static int		check_pipe(t_line_edit *line, t_completion data_comple)
{
	char	*temporary;
	char	*temp;
	int		size;

	temporary = ft_strndup(line->buffer, line->position - \
										ft_strlen(data_comple.path));
	temp = temporary;
	temporary = ft_strtrim(temp);
	free(temp);
	size = ft_strlen(temporary);
	if (ft_strlen(temporary) == line->nbr_prompt - 1)
	{
		free(temporary);
		return (1);
	}
	while (temporary[--size] != ' ')
		if (temporary[size] == '|' || temporary[size] == ';' \
												|| temporary[size] == '&')
		{
			free(temporary);
			return (1);
		}
	free(temporary);
	return (0);
}

int				ft_start_completion(t_completion data_compl, \
							t_line_edit *line, t_control_env *env, DIR **rep)
{
	if (data_compl.path[0] == '/')
	{
		if (!(*rep = opendir(data_compl.path)))
			return (tputs(tgetstr("bl", NULL), 1, &ft_putchar));
		completion_dir(data_compl, line);
	}
	else if (data_compl.path[0] == ' ')
		display_all_current(line, data_compl);
	else if (data_compl.path[0] == '.')
	{
		if (ft_strchr(data_compl.path, '/'))
			if (!(*rep = opendir(data_compl.path)))
				return (tputs(tgetstr("bl", NULL), 1, &ft_putchar));
		ft_start_completion_current(data_compl, line);
	}
	else
	{
		if ((check_pipe(line, data_compl)))
			return (completion_command(line, data_compl, env));
		ft_completion_after_command(line, data_compl);
	}
	return (0);
}

void			ft_completion(t_line_edit *line, t_control_env *env)
{
	t_completion	data_compl;
	DIR				*rep;

	rep = NULL;
	if (!(if_line_empty(line)))
		return ;
	ft_getdata(&data_compl, line);
	ft_getdata_dir(&data_compl);
	ft_start_completion(data_compl, line, env, &rep);
	(rep != NULL) ? closedir(rep) : 0;
	free_struct_data(&data_compl);
}
