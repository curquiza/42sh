/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_completion_current.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <rcarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 16:02:48 by rcarette          #+#    #+#             */
/*   Updated: 2017/10/16 15:26:42 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		check_line(t_tc *tool, t_completion data_comple)
{
	char	*temporary;
	char	*temp;

	temporary = ft_strndup(tool->buff, ft_calc_position(tool) - \
										ft_strlen(data_comple.path));
	temp = temporary;
	temporary = ft_strtrim(temp);
	free(temp);
	if ((int)ft_strlen(temporary) == tool->nbr_prompt - 1)
	{
		free(temporary);
		return (0);
	}
	free(temporary);
	return (1);
}

static int		stock_slash(t_tc *tool, t_completion data_comple)
{
	(void)data_comple;
	ft_insert("/", tool);
	//char	*begin;
	//int		t_cursor;

	//begin = ft_strndup(line->buffer, ft_calc_position(tool));
	//ft_memset(line->buffer, '\0', BUFF);
	//ft_strcpy(line->buffer, begin);
	//free(begin);
	//ft_strcat(line->buffer, "/");
	//t_cursor = ft_strlen(line->buffer);
	//ft_strcat(line->buffer, data_comple.after_cursor);
	//line->nbr_character = ft_strlen(line->buffer);
	//ft_clear_all_line(line);
	//ft_write_buffer(line);
	//ft_move_cursor(line, t_cursor);
	return (1);
}

int				search_file_current(t_completion data_comple, t_tc *tool)
{
	char		*temporary;
	t_rlist		*list;
	int			nbr;

	init_var(&temporary, &nbr);
	if (!(ft_strlen(data_comple.string)))
	{
		if (!(list = ft_getfiles_curr(&data_comple, temporary, 2)))
			return (tputs(tgetstr("bl", NULL), 1, &ft_termput));
		display_all_completion(list, tool, ft_getbigsize_file(list));
		clear_list_s(&list);
		return (1);
	}
	if (!(list = ft_getfiles_opt_curr(&data_comple, temporary, 2)))
		return (tputs(tgetstr("bl", NULL), 1, &ft_termput));
	(lenght_rlist_s(list) == 1) ? stock_completion(list, data_comple, tool) : 0;
	if (lenght_rlist_s(list) > 1)
		nbr = countnbr_match(list, ft_getsmall_file(list));
	nbr = (nbr == (int)ft_strlen(data_comple.string)) ? 0 : nbr;
	if (!nbr && lenght_rlist_s(list) > 1)
		display_all_completion(list, tool, ft_getbigsize_file(list));
	else if (nbr > 0)
		stock_completion_match(data_comple, nbr, ft_getsmall_file(list), tool);
	clear_list_s(&list);
	return (1);
}

int				search_file_with_path(t_tc *tool, \
													t_completion data_comple)
{
	char		*temporary;
	t_rlist		*list;
	int			nbr;

	init_var(&temporary, &nbr);
	if (!(ft_strlen(data_comple.string)))
	{
		if (!(list = ft_getfiles_all(data_comple, temporary, 2)))
			return (tputs(tgetstr("bl", NULL), 1, &ft_termput));
	}
	else
	{
		if (!(list = ft_getfiles_all_opt(data_comple, temporary, 2)))
			return (tputs(tgetstr("bl", NULL), 1, &ft_termput));
	}
	(lenght_rlist_s(list) == 1) ? stock_completion(list, data_comple, tool) : 0;
	if (lenght_rlist_s(list) > 1)
		nbr = countnbr_match(list, ft_getsmall_file(list));
	nbr = (nbr == (int)ft_strlen(data_comple.string)) ? 0 : nbr;
	if (!nbr && lenght_rlist_s(list) > 1)
		display_all_completion(list, tool, ft_getbigsize_file(list));
	else if (nbr > 0)
		stock_completion_match(data_comple, nbr, ft_getsmall_file(list), tool);
	clear_list_s(&list);
	return (1);
}

int				ft_start_completion_current(t_completion data_comple, \
															t_tc *tool)
{
	if (ft_strlen(data_comple.path) == 1 && data_comple.path[0] == '.'\
										&& check_line(tool, data_comple) == 0)
		return (stock_slash(tool, data_comple));
	else if (ft_strchr(data_comple.path, '/') == NULL && \
				data_comple.string != NULL && data_comple.string[0] == '.')
	{
		if (ft_strlen(data_comple.string) > 1)
			return (tputs(tgetstr("bl", NULL), 1, &ft_termput));
		stock_slash(tool, data_comple);
	}
	else if (ft_strlen(data_comple.path) == 1 && data_comple.path[0] == '.' \
										&& check_line(tool, data_comple) != 0)
	{
		search_file_current(data_comple, tool);
	}
	else
		search_file_with_path(tool, data_comple);
	return (1);
}
