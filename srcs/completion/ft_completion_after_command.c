/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion_after_command.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <rcarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 16:46:38 by rcarette          #+#    #+#             */
/*   Updated: 2017/07/07 07:24:57 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		completion_with_path(t_line_edit *line, \
													t_completion data_comple)
{
	t_rlist		*list;
	char		*temporary;
	int			nbr;

	init_var(&temporary, &nbr);
	if (!(ft_strlen(data_comple.string)))
	{
		if (!(list = ft_getfiles(data_comple, temporary, 2)))
			return (tputs(tgetstr("bl", NULL), 1, &ft_termput));
	}
	else
	{
		if (!(list = ft_getfiles_opt(data_comple, temporary, 2)))
			return (tputs(tgetstr("bl", NULL), 1, &ft_termput));
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
	return (0);
}

static t_rlist	*getfile_opt(char *path, t_completion data_comple,\
												char *temporary, int type)
{
	t_rlist			*list;
	DIR				*rep;
	struct dirent	*curr;
	struct stat		inf;

	list = NULL;
	rep = opendir(path);
	while ((curr = readdir(rep)))
	{
		if (ft_strcmp(curr->d_name, ".") == 0 || \
							ft_strcmp(curr->d_name, "..") == 0 || \
							ft_strncmp(curr->d_name, data_comple.path, \
							ft_strlen(data_comple.path)) != 0)
			continue ;
		temporary = ft_strjoin("./", curr->d_name);
		lstat(temporary, &inf);
		free(temporary);
		type = (S_ISDIR(inf.st_mode)) ? 0 : 2;
		if (S_ISREG(inf.st_mode) && (inf.st_mode & S_IXUSR) && \
						(inf.st_mode & S_IXGRP) && (inf.st_mode & S_IXOTH))
			type = 1;
		push_back_s(&list, curr->d_name, type);
	}
	closedir(rep);
	return (list);
}

static int		completion_current(t_line_edit *line, t_completion data_c)
{
	t_rlist		*list;
	char		*temporary;
	int			nbr;

	temporary = NULL;
	nbr = 0;
	if (!(list = getfile_opt("./", data_c, temporary, 2)))
		return (tputs(tgetstr("bl", NULL), 1, &ft_termput));
	(lenght_rlist_s(list) == 1) ? stockafter_command(line, data_c, list) : 0;
	if (lenght_rlist_s(list) > 1)
		nbr = countnbr_match(list, ft_getsmall_file(list));
	nbr = (nbr == (int)ft_strlen(data_c.path)) ? 0 : nbr;
	if (!nbr && lenght_rlist_s(list) > 1)
		display_all_completion(list, line, ft_getbigsize_file(list));
	else if (nbr > 0)
		stock_after_match(line, data_c, list, nbr);
	clear_list_s(&list);
	return (0);
}

void			ft_completion_after_command(t_line_edit *line, \
												t_completion data_comple)
{
	if (ft_strchr(data_comple.path, '/'))
		completion_with_path(line, data_comple);
	else
		completion_current(line, data_comple);
}
