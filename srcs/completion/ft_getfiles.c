/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <rcarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 17:35:23 by rcarette          #+#    #+#             */
/*   Updated: 2017/07/28 01:53:09 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_rlist		*ft_getfiles(t_completion data_comple, char *temporary, int type)
{
	t_rlist			*list;
	DIR				*rep;
	struct dirent	*cur;
	struct stat		inf;

	list = NULL;
	if (!(rep = opendir(data_comple.path)))
		return (NULL);
	while ((cur = readdir(rep)))
	{
		if (ft_strcmp(cur->d_name, ".") == 0 || \
										ft_strcmp(cur->d_name, "..") == 0)
			continue ;
		temporary = ft_strjoin(data_comple.path, cur->d_name);
		lstat(temporary, &inf);
		free(temporary);
		type = (S_ISDIR(inf.st_mode)) ? 0 : 2;
		if (S_ISREG(inf.st_mode) && (inf.st_mode & S_IXUSR) && \
						(inf.st_mode & S_IXGRP) && (inf.st_mode & S_IXOTH))
			type = 1;
		push_back_s(&list, cur->d_name, type);
	}
	closedir(rep);
	return (list);
}

t_rlist		*ft_getfiles_opt(t_completion data_comple, char *temporary, \
																	int type)
{
	t_rlist			*list;
	DIR				*rep;
	struct dirent	*cur;
	struct stat		inf;

	list = NULL;
	if (!(rep = opendir(data_comple.path)))
		return (NULL);
	while (rep != NULL && (cur = readdir(rep)))
	{
		if (ft_strcmp(cur->d_name, ".") == 0 || \
									ft_strcmp(cur->d_name, "..") == 0 || \
ft_strncmp(cur->d_name, data_comple.string, ft_rstrlen(data_comple.string)) != 0)
			continue ;
		temporary = ft_strjoin(data_comple.path, cur->d_name);
		lstat(temporary, &inf);
		free(temporary);
		type = (S_ISDIR(inf.st_mode)) ? 0 : 2;
		if (S_ISREG(inf.st_mode) && (inf.st_mode & S_IXUSR) && \
						(inf.st_mode & S_IXGRP) && (inf.st_mode & S_IXOTH))
			type = 1;
		push_back_s(&list, cur->d_name, type);
	}
	closedir(rep);
	return (list);
}

t_rlist		*ft_getfiles_curr(t_completion *data_comple, char *temporary, \
																	int type)
{
	t_rlist			*list;
	DIR				*rep;
	struct dirent	*cur;
	struct stat		inf;

	list = NULL;
	rep = opendir(data_comple->path);
	while ((cur = readdir(rep)))
	{
		if (cur->d_name[0] != '.')
			continue;
		temporary = ft_strjoin("./", cur->d_name);
		lstat(temporary, &inf);
		free(temporary);
		type = (S_ISDIR(inf.st_mode)) ? 0 : 2;
		if (S_ISREG(inf.st_mode) && (inf.st_mode & S_IXUSR) && \
						(inf.st_mode & S_IXGRP) && (inf.st_mode & S_IXOTH))
			type = 1;
		push_back_s(&list, cur->d_name, type);
	}
	closedir(rep);
	return (list);
}

t_rlist		*ft_getfiles_all(t_completion data_comple, char *temporary, \
																	int type)
{
	t_rlist			*list;
	DIR				*rep;
	struct dirent	*cur;
	struct stat		inf;

	list = NULL;
	if (!(rep = opendir(data_comple.path)))
		return (NULL);
	while ((cur = readdir(rep)))
	{
		if (ft_strcmp(cur->d_name, "..") == 0 || \
							ft_strcmp(cur->d_name, ".") == 0)
			continue ;
		temporary = ft_strjoin(data_comple.path, cur->d_name);
		lstat(temporary, &inf);
		free(temporary);
		type = (S_ISDIR(inf.st_mode)) ? 0 : 2;
		if (S_ISREG(inf.st_mode) && (inf.st_mode & S_IXUSR) && \
						(inf.st_mode & S_IXGRP) && (inf.st_mode & S_IXOTH))
			type = 1;
		push_back_s(&list, cur->d_name, type);
	}
	closedir(rep);
	return (list);
}

t_rlist		*ft_getfiles_all_opt(t_completion data_comple, char *temporary, \
																	int type)
{
	t_rlist			*list;
	DIR				*rep;
	struct dirent	*c;
	struct stat		inf;

	list = NULL;
	rep = opendir(data_comple.path);
	while ((c = readdir(rep)))
	{
		if (ft_strcmp(c->d_name, "..") == 0 || ft_strcmp(c->d_name, ".") == 0)
			continue ;
		if (ft_strncmp(c->d_name, data_comple.string, \
									ft_rstrlen(data_comple.string)) != 0)
			continue ;
		temporary = ft_strjoin(data_comple.path, c->d_name);
		lstat(temporary, &inf);
		free(temporary);
		type = (S_ISDIR(inf.st_mode)) ? 0 : 2;
		if (S_ISREG(inf.st_mode) && (inf.st_mode & S_IXUSR) && \
						(inf.st_mode & S_IXGRP) && (inf.st_mode & S_IXOTH))
			type = 1;
		push_back_s(&list, c->d_name, type);
	}
	closedir(rep);
	return (list);
}
