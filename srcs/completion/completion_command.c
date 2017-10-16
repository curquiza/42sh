/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 14:12:41 by rcarette          #+#    #+#             */
/*   Updated: 2017/10/16 17:47:39 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			ft_get_filecommand(t_rlist **list, char *path, \
													t_completion data_comple)
{
	DIR				*rep;
	struct dirent	*curr;

	rep = NULL;
	if (!(rep = opendir(path)))
		return ;
	while ((curr = readdir(rep)))
	{
		if (ft_strncmp(curr->d_name, data_comple.path, \
										ft_rstrlen(data_comple.path)) != 0)
			continue ;
		push_back_s(list, curr->d_name, -1);
	}
	closedir(rep);
}

static t_rlist		*ft_get_rlistcommand(char *path, t_completion data_comple)
{
	char	**board;
	int		i;
	t_rlist	*list;

	i = -1;
	list = NULL;
	board = ft_strsplit(path, ':');
	while (board[++i])
		ft_get_filecommand(&list, board[i], data_comple);
	clear_tab(board);
	return (list);
}

static void			stock_command(t_tc *tool, t_rlist *list, \
											t_completion data_comple, int i)
{
	ft_insert(list->file, tool);
	if (ft_rstrlen(data_comple.after_cursor) == 0 && i == 0)
		ft_insert(" ", tool);

	//char	*prompt;
	//int		t_cursor;

	//prompt = ft_strndup(line->buffer, ft_calc_position(tool) - \
	//											ft_rstrlen(data_comple.path));
	//ft_clear_all_line(line);
	//ft_memset(line->buffer, '\0', BUFF);
	//ft_strcpy(line->buffer, prompt);
	//ft_strcat(line->buffer, list->file);
	//if (ft_rstrlen(data_comple.after_cursor) == 0 && i == 0)
	//	ft_strcat(line->buffer, " ");
	//t_cursor = ft_rstrlen(line->buffer);
	//ft_strcat(line->buffer, data_comple.after_cursor);
	//line->nbr_character = ft_rstrlen(line->buffer);
	//ft_write_buffer(line);
	//ft_move_cursor(line, t_cursor);
	//free(prompt);
}

static void			stock_command_match(t_tc *tool, \
								t_completion data_comple, char *file, int nbr)
{
	t_rlist		*list;
	char		*str;

	list = NULL;
	//str = ft_strndup(file, nbr);
	str = ft_strsub(file, 0, nbr);
	(!str) ? str = ft_strnew(0) : 0; //s+c
	push_back_s(&list, str, -1);
	stock_command(tool, list, data_comple, -1);
	clear_list_s(&list);
	free(str);
}

int					completion_command(t_tc *tool, \
												t_completion data_comple)
{
	char	*path;
	t_rlist	*list;
	int		nbr;

	nbr = 0;
	if (!(path = ft_get_varvalue(g_shell->var_env, "PATH")))
		return (tputs(tgetstr("bl", NULL), 1, &ft_termput));
	if (!(list = ft_get_rlistcommand(path, data_comple)))
		return (tputs(tgetstr("bl", NULL), 1, &ft_termput));
	(lenght_rlist_s(list) == 1) ? stock_command(tool, list, data_comple, 0) : 0;
	if (lenght_rlist_s(list) > 1)
		nbr = countnbr_match(list, ft_getsmall_file(list));
	nbr = (nbr == (int)ft_rstrlen(data_comple.path)) ? 0 : nbr;
	if (!nbr && lenght_rlist_s(list) > 1)
		display_all_completion(list, tool, ft_getbigsize_file(list));
	else if (nbr > 0)
		stock_command_match(tool, data_comple, ft_getsmall_file(list), nbr);
	clear_list_s(&list);
	return (1);
}
