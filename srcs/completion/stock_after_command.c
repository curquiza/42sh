/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_after_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <rcarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 01:44:17 by rcarette          #+#    #+#             */
/*   Updated: 2017/07/07 05:25:07 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

void		stockafter_command(t_line_edit *line, t_completion data_comple,\
																t_list *list)
{
	char	*prompt;
	int		t_cursor;

	prompt = ft_strndup(line->buffer, line->position - \
												ft_strlen(data_comple.path));
	ft_memset(line->buffer, '\0', BUFF);
	ft_clear_all_line(line);
	ft_strcpy(line->buffer, prompt);
	ft_strcat(line->buffer, list->file);
	(list->type == 0) ? ft_strcat(line->buffer, "/") : 0;
	if (list->type == 2 && ft_strlen(data_comple.after_cursor) == 0)
		ft_strcat(line->buffer, " ");
	t_cursor = ft_strlen(line->buffer);
	ft_strcat(line->buffer, data_comple.after_cursor);
	line->nbr_character = ft_strlen(line->buffer);
	ft_write_buffer(line);
	ft_move_cursor(line, t_cursor);
	free(prompt);
}

void		stock_after_match(t_line_edit *line, t_completion data_comple, \
														t_list *list, int nbr)
{
	t_list		*list_file;
	char		*str;

	list_file = NULL;
	str = ft_strndup(ft_getsmall_file(list), nbr);
	push_back_s(&list_file, str, -1);
	stockafter_command(line, data_comple, list_file);
	clear_list_s(&list_file);
	free(str);
}
