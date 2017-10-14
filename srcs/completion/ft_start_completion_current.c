/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_completion_current.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <rcarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 16:02:48 by rcarette          #+#    #+#             */
/*   Updated: 2017/07/07 05:25:15 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		check_line(t_line_edit *line, t_completion data_comple)
{
	char	*temporary;
	char	*temp;

	temporary = ft_strndup(line->buffer, line->position - \
										ft_strlen(data_comple.path));
	temp = temporary;
	temporary = ft_strtrim(temp);
	free(temp);
	if (ft_strlen(temporary) == line->nbr_prompt - 1)
	{
		free(temporary);
		return (0);
	}
	free(temporary);
	return (1);
}

static int		stock_slash(t_line_edit *line, t_completion data_comple)
{
	char	*begin;
	int		t_cursor;

	begin = ft_strndup(line->buffer, line->position);
	ft_memset(line->buffer, '\0', BUFF);
	ft_strcpy(line->buffer, begin);
	free(begin);
	ft_strcat(line->buffer, "/");
	t_cursor = ft_strlen(line->buffer);
	ft_strcat(line->buffer, data_comple.after_cursor);
	line->nbr_character = ft_strlen(line->buffer);
	ft_clear_all_line(line);
	ft_write_buffer(line);
	ft_move_cursor(line, t_cursor);
	return (1);
}

int				search_file_current(t_completion data_comple, t_line_edit *line)
{
	char		*temporary;
	t_rlist		*list;
	int			nbr;

	init_var(&temporary, &nbr);
	if (!(ft_strlen(data_comple.string)))
	{
		if (!(list = ft_getfiles_curr(&data_comple, temporary, 2)))
			return (tputs(tgetstr("bl", NULL), 1, &ft_putchar));
		display_all_completion(list, line, ft_getbigsize_file(list));
		clear_list_s(&list);
		return (1);
	}
	if (!(list = ft_getfiles_opt_curr(&data_comple, temporary, 2)))
		return (tputs(tgetstr("bl", NULL), 1, &ft_putchar));
	(lenght_rlist_s(list) == 1) ? stock_completion(list, data_comple, line) : 0;
	if (lenght_rlist_s(list) > 1)
		nbr = countnbr_match(list, ft_getsmall_file(list));
	nbr = (nbr == (int)ft_strlen(data_comple.string)) ? 0 : nbr;
	if (!nbr && lenght_rlist_s(list) > 1)
		display_all_completion(list, line, ft_getbigsize_file(list));
	else if (nbr > 0)
		stock_completion_match(data_comple, nbr, ft_getsmall_file(list), line);
	clear_list_s(&list);
	return (1);
}

int				search_file_with_path(t_line_edit *line, \
													t_completion data_comple)
{
	char		*temporary;
	t_rlist		*list;
	int			nbr;

	init_var(&temporary, &nbr);
	if (!(ft_strlen(data_comple.string)))
	{
		if (!(list = ft_getfiles_all(data_comple, temporary, 2)))
			return (tputs(tgetstr("bl", NULL), 1, &ft_putchar));
	}
	else
	{
		if (!(list = ft_getfiles_all_opt(data_comple, temporary, 2)))
			return (tputs(tgetstr("bl", NULL), 1, &ft_putchar));
	}
	(lenght_rlist_s(list) == 1) ? stock_completion(list, data_comple, line) : 0;
	if (lenght_rlist_s(list) > 1)
		nbr = countnbr_match(list, ft_getsmall_file(list));
	nbr = (nbr == (int)ft_strlen(data_comple.string)) ? 0 : nbr;
	if (!nbr && lenght_rlist_s(list) > 1)
		display_all_completion(list, line, ft_getbigsize_file(list));
	else if (nbr > 0)
		stock_completion_match(data_comple, nbr, ft_getsmall_file(list), line);
	clear_list_s(&list);
	return (1);
}

int				ft_start_completion_current(t_completion data_comple, \
															t_line_edit *line)
{
	if (ft_strlen(data_comple.path) == 1 && data_comple.path[0] == '.'\
										&& check_line(line, data_comple) == 0)
		return (stock_slash(line, data_comple));
	else if (ft_strchr(data_comple.path, '/') == NULL && \
				data_comple.string != NULL && data_comple.string[0] == '.')
	{
		if (ft_strlen(data_comple.string) > 1)
			return (tputs(tgetstr("bl", NULL), 1, &ft_putchar));
		stock_slash(line, data_comple);
	}
	else if (ft_strlen(data_comple.path) == 1 && data_comple.path[0] == '.' \
										&& check_line(line, data_comple) != 0)
	{
		search_file_current(data_comple, line);
	}
	else
		search_file_with_path(line, data_comple);
	return (1);
}
