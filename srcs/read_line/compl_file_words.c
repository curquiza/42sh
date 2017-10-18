/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_file_words.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 11:23:45 by sfranc            #+#    #+#             */
/*   Updated: 2017/10/18 11:23:47 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ft_find_files_in(DIR *open, t_comp_ctrl *ctrl)
{
	struct dirent	*dir;
	int				len;

	len = ft_strlen(ctrl->clues);
	while ((dir = readdir(open)) != NULL)
	{
		if (ctrl->len >= COMP_SIZE)
			return (-1);
		if (ft_check_hidden_file(ctrl, dir->d_name) == 1
			&& ft_strncmp(dir->d_name, ctrl->clues, len) == 0)
		{
			ft_complst_pushback(ctrl, ft_complete_name(dir->d_name, ctrl));
			ctrl->len++;
		}
	}
	return (0);
}

int			ft_get_file_words(t_comp_ctrl *ctrl)
{
	int		ret;
	DIR		*open;

	ret = 0;
	if (!(open = opendir(ctrl->path)))
		return (ret);
	if (ft_find_files_in(open, ctrl) == -1)
		ret = -1;
	closedir(open);
	return (ret);
}
