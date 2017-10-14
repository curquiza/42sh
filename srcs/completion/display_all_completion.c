/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_all_completion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <rcarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 02:01:43 by rcarette          #+#    #+#             */
/*   Updated: 2017/07/07 05:24:03 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static void		manage_display_all_completion(t_line_edit *line)
{
	write(1, "\n", 1);
	line->position = (0);
	line->t_size_screen = line->size_screen;
	line->nbr_lines = (1);
	ft_write_buffer(line);
}

static void		print_file(t_list *list)
{
	(list->type == 0) ? write(1, BLUE, ft_strlen(BLUE)) : 0;
	(list->type == 1) ? write(1, GREEN, ft_strlen(GREEN)) : 0;
	write(1, list->file, list->size_file);
	(list->type == 0) ? write(1, "/", 1) : 0;
	write(1, DEFAULT_COMPLE, ft_strlen(DEFAULT_COMPLE));
	(list->type > 0) ? write(1, " ", 1) : 0;
}

static void		print_nspaces(int n_spaces)
{
	while (--n_spaces)
		write(1, " ", 1);
}

void			display_all_completion(t_list *list, t_line_edit *line, \
																int big_size)
{
	int		nbr_character;
	int		n_spaces;
	int		t_cursor;

	nbr_character = 0;
	n_spaces = 0;
	t_cursor = line->position;
	ft_end_of_line(line);
	write(1, "\n", 1);
	while (list)
	{
		n_spaces = ((big_size - (ft_strlen(list->file))) + 3);
		nbr_character += ((ft_strlen(list->file) + 1) + n_spaces);
		if (nbr_character >= (int)line->size_screen)
		{
			nbr_character = 0;
			nbr_character += n_spaces + ft_strlen(list->file);
			write(1, "\n", 1);
		}
		print_file(list);
		(list->next != NULL) ? print_nspaces(n_spaces) : 0;
		list = list->next;
	}
	manage_display_all_completion(line);
	ft_move_cursor(line, t_cursor);
}
