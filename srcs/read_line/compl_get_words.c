/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_get_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 14:44:22 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/17 15:42:23 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_complst_pushback(t_comp_ctrl *ctrl, char *word)
{
	t_comp			*new;
	t_comp			*tmp;

	new = ft_memalloc(sizeof(*new));
	new->word = word;
	if (!ctrl->start)
	{
		ctrl->start = new;
		ctrl->end = new;
	}
	else
	{
		tmp = ctrl->end;
		tmp->next = new;
		new->prev = tmp;
		ctrl->end = new;
	}
}

char	*ft_complete_name(char *word, t_comp_ctrl *ctrl)
{
	struct stat		temp_stat;
	char			*new;
	char			*temp;

	temp = ft_strjoin(ctrl->path, word);
	if ((stat(temp, &temp_stat)) == -1)
		new = ft_strdup(word);
	else if (S_ISDIR(temp_stat.st_mode))
		new = ft_strjoin(word, "/");
	else
		new = ft_strjoin(word, " ");
	free(temp);
	return (new);
}

int		ft_find_words_in(DIR *open, t_comp_ctrl *ctrl)
{
	struct dirent	*dir;
	int				len;

	len = ft_strlen(ctrl->clues);
	while ((dir = readdir(open)) != NULL)
	{
		if (ctrl->len >= COMP_SIZE)
			return (-1);
		if ((dir->d_name[0] != '.' || ctrl->clues[0] == '.')
			&& ft_strncmp(dir->d_name, ctrl->clues, len) == 0)
		{
			//ft_complst_pushback(ctrl, dir->d_name);
			ft_complst_pushback(ctrl, ft_complete_name(dir->d_name, ctrl));
			ctrl->len++;
		}
	}
	return (0);
}

int		ft_check_user_right(t_comp_ctrl *ctrl, char *name)
{
	struct stat		temp_stat;
	char			*temp;

	temp = ft_strjoin(ctrl->path, name);
	if ((stat(temp, &temp_stat)) != -1\
			&& ((temp_stat.st_mode & S_IXUSR) == S_IXUSR))
	{
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}

int		ft_check_is_dir(t_comp_ctrl *ctrl, char *name)
{
	struct stat		temp_stat;
	char			*temp;

	temp = ft_strjoin(ctrl->path, name);
	if ((stat(temp, &temp_stat)) != -1 && S_ISDIR(temp_stat.st_mode))
	{
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}

int		ft_find_exec_in(DIR *open, t_comp_ctrl *ctrl, int mode_dir)
{
	struct dirent	*dir;
	int				len;

	(void)mode_dir;
	len = ft_strlen(ctrl->clues);
	while ((dir = readdir(open)) != NULL)
	{
		if (ctrl->len >= COMP_SIZE)
			return (-1);
		if ((dir->d_name[0] != '.' || ctrl->clues[0] == '.')
			&& ft_strncmp(dir->d_name, ctrl->clues, len) == 0)
		{
			if (ft_check_user_right(ctrl, dir->d_name) == 1)
			{
				ft_complst_pushback(ctrl, ft_complete_name(dir->d_name, ctrl));
				ctrl->len++;
			}
		}
	}
	return (0);
}

//int		ft_get_bin_words(t_comp_ctrl *ctrl)
//{
//	char	**pathtab;
//	DIR		*open;
//	int		i;
//	int		len;
//
////	if (ft_strcmp(ctrl->to_find, ".") == 0)
////		return (0);
//	if (!(pathtab = ft_get_pathtab(g_shell)))
//		return (0);
//	len = ft_tablen(pathtab);
//	i = -1;
//	while (++i < len)
//	{
//		if (!(open = opendir(pathtab[i])))
//			continue;
//		if (ft_find_words_in(open, ctrl) == -1)
//		{
//			ft_tabdel(&pathtab);
//			closedir(open);
//			return (-1);
//		}
//		closedir(open);
//	}
//	ft_tabdel(&pathtab);
//	return (0);
//}

int		ft_get_cmd_words(t_comp_ctrl *ctrl)
{
	DIR		*open;
	int		ret;

	ret = 0;
	if (ft_strchr(ctrl->word_to_comp, '/'))
	{
		if (!(open = opendir(ctrl->path)))
			return (ret);
		if (ft_find_exec_in(open, ctrl, 1) == -1)
			ret = -1;
		closedir(open);
	}
	return (ret);
}


int		ft_get_file_words(t_comp_ctrl *ctrl)
{
	int		ret;
	DIR		*open;

	ret = 0;
	//if (!(open = opendir(".")))
	if (!(open = opendir(ctrl->path)))
		return (ret);
	if (ft_find_words_in(open, ctrl) == -1)
		ret = -1;
	closedir(open);
	return (ret);
}

int		ft_get_all_candidates(t_comp_ctrl *ctrl, t_tc *tool)
{
	int		ret;

	ret = 0;
	if (ctrl->status == 1)
		ret = ft_get_cmd_words(ctrl);
	else if (ctrl->status == 2)
		ret = ft_get_file_words(ctrl);
	if (ret == -1)
	{
		tputs(tool->down, 1, ft_termput);
		ft_putendl(COMP_MSG);
		ft_put_comp_prompt(tool);
		return (-1);
	}
	return (0);
}
