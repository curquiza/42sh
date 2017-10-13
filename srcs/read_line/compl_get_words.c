/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_get_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 14:44:22 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:31:57 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_complst_pushback(t_comp_ctrl *ctrl, char *word)
{
	t_comp			*new;
	t_comp			*tmp;

	new = ft_memalloc(sizeof(*new));
	new->word = ft_strdup(word);
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

int		ft_find_words_in(DIR *open, t_comp_ctrl *ctrl)
{
	struct dirent	*dir;
	int				len;

	len = ft_strlen(ctrl->to_find);
	while ((dir = readdir(open)) != NULL)
	{
		if (ctrl->len >= COMP_SIZE)
			return (-1);
		if ((dir->d_name[0] != '.' || ctrl->to_find[0] == '.')
			&& ft_strncmp(dir->d_name, ctrl->to_find, len) == 0)
		{
			ft_complst_pushback(ctrl, dir->d_name);
			ctrl->len++;
		}
	}
	return (0);
}

int		ft_get_bin_words(t_comp_ctrl *ctrl)
{
	char	**pathtab;
	DIR		*open;
	int		i;
	int		len;

	if (ft_strcmp(ctrl->to_find, ".") == 0)
		return (0);
	if (!(pathtab = ft_get_pathtab(g_shell)))
		return (0);
	len = ft_tablen(pathtab);
	i = -1;
	while (++i < len)
	{
		if (!(open = opendir(pathtab[i])))
			continue;
		if (ft_find_words_in(open, ctrl) == -1)
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

int		ft_get_file_words(t_comp_ctrl *ctrl)
{
	int		ret;
	DIR		*open;

	ret = 0;
	if (!(open = opendir(".")))
		return (ret);
	if (ft_find_words_in(open, ctrl) == -1)
		ret = -1;
	closedir(open);
	return (ret);
}

int		ft_get_all_words(t_comp_ctrl *ctrl, t_tc *tool)
{
	int		ret;

	ret = 0;
	if (ctrl->status == 1)
		ret = ft_get_bin_words(ctrl);
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
