/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_all_current.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <rcarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 15:35:57 by rcarette          #+#    #+#             */
/*   Updated: 2017/10/16 14:28:53 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_rlist		*ft_getfiles_space(char *path, char *temporary, int type)
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
										ft_strcmp(curr->d_name, "..") == 0)
			continue ;
		temporary = ft_strjoin(path, curr->d_name);
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

void				display_all_current(t_tc *tool, t_completion data_comple)
{
	t_rlist		*list;
	char		*temporary;

	(void)data_comple;
	temporary = NULL;
	list = ft_getfiles_space("./", temporary, 2);
	display_all_completion(list, tool, ft_getbigsize_file(list));
	clear_list_s(&list);
}
