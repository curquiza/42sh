/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_completion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <rcarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 23:12:50 by rcarette          #+#    #+#             */
/*   Updated: 2017/07/07 05:25:03 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		stock_line(t_completion data_comple, t_line_edit *line,\
												char *temp, char *prompt)
{
	ft_memset(line->buffer, '\0', BUFF);
	ft_strcpy(line->buffer, prompt);
	ft_strcat(line->buffer, data_comple.path);
	ft_strcat(line->buffer, temp);
}

void			stock_completion(t_rlist *list, t_completion data_comple,\
															t_line_edit *line)
{
	char	*prompt;
	int		size;
	char	*temp;
	int		t_cursor;

	size = ft_strlen(data_comple.path) + ft_strlen(data_comple.string);
	prompt = ft_strndup(line->buffer, (line->position - size));
	t_cursor = line->position;
	temp = ft_memalloc((ft_strlen(list->file) + 2), sizeof(char));
	ft_memset(temp, '\0', (ft_strlen(list->file) + 2));
	ft_strcpy(temp, list->file);
	(list->type == 0) ? ft_strcat(temp, "/") : 0;
	if (list->type == 2 && ft_strlen(data_comple.after_cursor) == 0)
		ft_strcat(temp, " ");
	ft_clear_all_line(line);
	stock_line(data_comple, line, temp, prompt);
	t_cursor = ft_strlen(line->buffer);
	ft_strcat(line->buffer, data_comple.after_cursor);
	free(temp);
	free(prompt);
	line->nbr_character = ft_strlen(line->buffer);
	ft_write_buffer(line);
	ft_move_cursor(line, t_cursor);
}

void			stock_completion_match(t_completion data_comple, \
										int nbr, char *file, t_line_edit *line)
{
	t_rlist		*list;
	char		*str;

	list = NULL;
	str = ft_strndup(file, nbr);
	push_back_s(&list, str, -1);
	stock_completion(list, data_comple, line);
	clear_list_s(&list);
	free(str);
}
