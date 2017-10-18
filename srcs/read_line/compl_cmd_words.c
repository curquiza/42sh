/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_cmd_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 11:23:58 by sfranc            #+#    #+#             */
/*   Updated: 2017/10/18 11:25:34 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		ft_find_exec_in_currentpath(DIR *open, t_comp_ctrl *ctrl)
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
			if (ft_check_user_right(ctrl->path, dir->d_name) == 1)
			{
				ft_complst_pushback(ctrl, ft_complete_name(dir->d_name, ctrl));
				ctrl->len++;
			}
		}
	}
	return (0);
}

static int		ft_find_exec_in_envpath(DIR *open, t_comp_ctrl *ctrl,\
		char *envpath)
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
			if (ft_check_user_right(envpath, dir->d_name) == 1
				&& ft_check_is_dir(envpath, dir->d_name) == 0)
			{
				ft_complst_pushback(ctrl, ft_strjoin(dir->d_name, " "));
				ctrl->len++;
			}
		}
	}
	return (0);
}

int				ft_exec_in_env_path(t_comp_ctrl *ctrl)
{
	char	**pathtab;
	DIR		*open;
	int		i;
	int		len;

	if (!(pathtab = ft_get_pathtab(g_shell)))
		return (0);
	len = ft_tablen(pathtab);
	i = -1;
	while (++i < len)
	{
		if (!(open = opendir(pathtab[i])))
			continue;
		if (ft_find_exec_in_envpath(open, ctrl, pathtab[i]) == -1)
		{
			ft_tabdel(&pathtab);
			closedir(open);
			return (-1);
		}
		closedir(open);
	}
	ft_tabdel(&pathtab);
	return (0);
}

int				ft_get_cmd_words(t_comp_ctrl *ctrl)
{
	DIR		*open;
	int		ret;

	ret = 0;
	if (ft_strchr(ctrl->word_to_comp, '/'))
	{
		if (!(open = opendir(ctrl->path)))
			return (ret);
		if (ft_find_exec_in_currentpath(open, ctrl) == -1)
			ret = -1;
		closedir(open);
	}
	else
	{
		if (ft_exec_in_env_path(ctrl) == -1)
			return (-1);
		if (!(open = opendir(ctrl->path)))
			return (ret);
		if (ft_find_exec_in_currentpath(open, ctrl) == -1)
			ret = -1;
		closedir(open);
	}
	return (ret);
}
