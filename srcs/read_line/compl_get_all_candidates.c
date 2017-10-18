/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_get_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 14:44:22 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/18 10:52:28 by curquiza         ###   ########.fr       */
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

/*
** ft_check_hidden_file :
** Returns 1 if hidden file taken.
*/

int		ft_check_hidden_file(t_comp_ctrl *ctrl, char *name)
{
	if (ctrl->clues[0] == '.')
		return (1);
	else if (!ft_strcmp(name, ".") || !ft_strcmp(name, ".."))
		return (0);
	return (1);
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
