/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_all_completion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <rcarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 02:01:43 by rcarette          #+#    #+#             */
/*   Updated: 2017/10/16 15:21:53 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//static void		manage_display_all_completion(t_line_edit *line)
//{
//	write(1, "\n", 1);
//	ft_calc_position(tool) = (0);
//	line->t_size_screen = line->size_screen;
//	line->nbr_lines = (1);
//	ft_write_buffer(line);
//}

static void		print_file(t_rlist *list)
{
	(list->type == 0) ? write(1, BLUE, ft_rstrlen(BLUE)) : 0;
	(list->type == 1) ? write(1, GREEN, ft_rstrlen(GREEN)) : 0;
	write(1, list->file, list->size_file);
	(list->type == 0) ? write(1, "/", 1) : 0;
	write(1, DEF, ft_rstrlen(DEF));
	(list->type > 0) ? write(1, " ", 1) : 0;
}

static void		print_nspaces(int n_spaces)
{
	while (--n_spaces)
		write(1, " ", 1);
}

void			display_all_completion(t_rlist *list, t_tc *tool, int big_size)
{
	int		nbr_character;
	int		n_spaces;
	int		t_cursor;

	nbr_character = 0;
	n_spaces = 0;
	t_cursor = ft_calc_position(tool);
	//ft_end_of_line(tool);
	ft_move_end(tool);
	write(1, "\n", 1);
	while (list)
	{
		n_spaces = ((big_size - (ft_rstrlen(list->file))) + 3);
		nbr_character += ((ft_rstrlen(list->file) + 1) + n_spaces);
		if (nbr_character >= (int)tool->x_max)
		{
			nbr_character = 0;
			nbr_character += n_spaces + ft_rstrlen(list->file);
			write(1, "\n", 1);
		}
		print_file(list);
		(list->next != NULL) ? print_nspaces(n_spaces) : 0;
		list = list->next;
	}
	ft_put_comp_prompt(tool);
	//write(1, COMP_PROMPT, ft_rstrlen(COMP_PROMPT));

	//ATTENTION
	//manage_display_all_completion(tool);
	//ft_move_cursor(tool, t_cursor);
}
