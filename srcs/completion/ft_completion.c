/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <rcarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 16:04:01 by rcarette          #+#    #+#             */
/*   Updated: 2017/10/16 15:26:51 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//static int		if_line_empty(t_tc *tool)
//{
//	char	*getline;
//	char	*temporary_getline;
//
//	if (ft_calc_position(tool) == tool->prompt_len)
//		return (tputs(tgetstr("bl", NULL), 1, &ft_termput));
//	if (tool->prompt_len == tool->nbr_char)
//		return (0);
//	getline = ft_strdup(&tool->buff[tool->nbr_prompt]);
//	temporary_getline = getline;
//	getline = ft_strtrim(temporary_getline);
//	free(temporary_getline);
//	if (ft_strlen(getline))
//	{
//		free(getline);
//		return (1);
//	}
//	free(getline);
//	return (tputs(tgetstr("bl", NULL), 1, &ft_termput));
//}

static void		free_struct_data(t_completion *data_compl)
{
	(data_compl->path != NULL) ? free(data_compl->path) : 0;
	(data_compl->string != NULL) ? free(data_compl->string) : 0;
	(data_compl->after_cursor != NULL) ? free(data_compl->after_cursor) : 0;
	(data_compl->buff_cursor != NULL) ? free(data_compl->buff_cursor) : 0;
}

static int		check_pipe(t_tc *tool, t_completion data_comple)
{
	char	*temporary;
	char	*temp;
	int		size;

	temporary = ft_strndup(tool->buff, ft_calc_position(tool) - \
										ft_strlen(data_comple.path));
	temp = temporary;
	temporary = ft_strtrim(temp);
	free(temp);
	size = ft_strlen(temporary);
	if ((int)ft_strlen(temporary) == tool->nbr_prompt - 1)
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
							t_tc *tool, DIR **rep)
{
	if (data_compl.path[0] == '/')
	{
		if (!(*rep = opendir(data_compl.path)))
			return (tputs(tgetstr("bl", NULL), 1, &ft_termput));
		completion_dir(data_compl, tool);
	}
	else if (data_compl.path[0] == ' ')
		display_all_current(tool, data_compl);
	else if (data_compl.path[0] == '.')
	{
		if (ft_strchr(data_compl.path, '/'))
			if (!(*rep = opendir(data_compl.path)))
				return (tputs(tgetstr("bl", NULL), 1, &ft_termput));
		ft_start_completion_current(data_compl, tool);
	}
	else
	{
		if ((check_pipe(tool, data_compl)))
			return (completion_command(tool, data_compl));
		ft_completion_after_command(tool, data_compl);
	}
	return (0);
}

void			ft_completion_romain(t_tc *tool)
{
	t_completion	data_compl;
	DIR				*rep;

	rep = NULL;
	//if (!(if_line_empty(tool)))
	//	return ;
	if (tool->buff[0] == '\0')
		return ; // OK?
	ft_getdata(&data_compl, tool);//OK
	ft_getdata_dir(&data_compl);//OK
	ft_start_completion(data_compl, tool, &rep); //OK
	(rep != NULL) ? closedir(rep) : 0;
	free_struct_data(&data_compl);//OK
}
