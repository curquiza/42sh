/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfile_op_curr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <rcarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 15:16:30 by rcarette          #+#    #+#             */
/*   Updated: 2017/07/07 05:24:22 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static void		ft_fuck_norm(struct stat *sb, int *type, char **temporary, \
																	char *data)
{
	lstat(data, sb);
	free(*temporary);
	*type = (S_ISDIR(sb->st_mode)) ? 0 : 2;
}

static void		ft_fuck_norm_comple(t_list **list, char *data, int type)
{
	char	*temporary;

	temporary = ft_strdup(data);
	push_back_s(list, temporary, type);
	free(temporary);
}

t_list			*ft_getfiles_opt_curr(t_completion *data_comple, \
													char *temporary, int type)
{
	t_list			*list;
	DIR				*rep;
	struct dirent	*curr;
	struct stat		inf;

	list = NULL;
	rep = opendir(data_comple->path);
	while ((curr = readdir(rep)))
	{
		if (curr->d_name[0] != '.')
			continue ;
		temporary = ft_strjoin(".", data_comple->string);
		if (ft_strncmp(temporary, curr->d_name, ft_strlen(temporary)) != 0)
		{
			ft_memdel((void *)&temporary);
			continue ;
		}
		ft_fuck_norm(&inf, &type, &temporary, curr->d_name);
		if (S_ISREG(inf.st_mode) && (inf.st_mode & S_IXUSR) && \
						(inf.st_mode & S_IXGRP) && (inf.st_mode & S_IXOTH))
			type = 1;
		ft_fuck_norm_comple(&list, curr->d_name + 1, type);
	}
	closedir(rep);
	return (list);
}
