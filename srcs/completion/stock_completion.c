/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_completion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <rcarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 23:12:50 by rcarette          #+#    #+#             */
/*   Updated: 2017/10/16 16:04:02 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//static void		stock_line(t_completion data_comple, t_line_edit *line,\
//												char *temp, char *prompt)
//{
//	ft_memset(line->buffer, '\0', BUFF);
//	ft_strcpy(line->buffer, prompt);
//	ft_strcat(line->buffer, data_comple.path);
//	ft_strcat(line->buffer, temp);
//}

void			stock_completion(t_rlist *list, t_completion data_comple,\
															t_tc *tool)
{
//	ft_putendl2_fd("\nsc path = ", data_comple.path, 1);
//	ft_putendl2_fd("sc string = ", data_comple.string, 1);
//	ft_putendl2_fd("sc buff_cursor = ", data_comple.buff_cursor, 1);
//	ft_putendl2_fd("sc after_cursor = ", data_comple.after_cursor, 1);
//	ft_putendl2_fd("sc list->file = ", list->file, 1);
//	(void)data_comple;
	ft_insert(list->file + ft_strlen(data_comple.string), tool);
	if (list->type == 0)
		ft_insert("/", tool);
	else if (list->type == 2)
		ft_insert(" ", tool);

	//char	*prompt;
	//int		size;
	//char	*temp;
	//int		t_cursor;

	//size = ft_strlen(data_comple.path) + ft_strlen(data_comple.string);
	//prompt = ft_strndup(tool->buffer, (ft_calc_position(tool) - size));
	//t_cursor = ft_calc_position(tool);
	//temp = ft_memalloc((ft_strlen(list->file) + 2), sizeof(char));
	//ft_memset(temp, '\0', (ft_strlen(list->file) + 2));
	//ft_strcpy(temp, list->file);
	//(list->type == 0) ? ft_strcat(temp, "/") : 0;
	//if (list->type == 2 && ft_strlen(data_comple.after_cursor) == 0)
	//	ft_strcat(temp, " ");
	//ft_clear_all_line(tool);
	//stock_line(data_comple, tool, temp, prompt);
	//t_cursor = ft_strlen(tool->buff);
	//ft_strcat(tool->buffer, data_comple.after_cursor);
	//free(temp);
	//free(prompt);
	//tool->nbr_char = ft_strlen(tool->buffer);
	//ft_write_buffer(tool);
	//ft_move_cursor(tool, t_cursor);
}

void			stock_completion_match(t_completion data_comple, \
										int nbr, char *file, t_tc *tool)
{
	t_rlist		*list;
	char		*str;

	list = NULL;
	str = ft_strndup(file, nbr);
	push_back_s(&list, str, -1);
	stock_completion(list, data_comple, tool);
	clear_list_s(&list);
	free(str);
}
