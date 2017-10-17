/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_init_reset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 14:48:11 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/17 12:40:24 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_get_comp_word(t_tc *tool, t_comp_ctrl *ctrl)
{
	int		pos;
	int		i;
	char	*temp;

	pos = tool->curs_y * (tool->x_max + 1) + tool->curs_x - tool->prompt_len;
	i = pos - 1;
	while (i >= 0 && tool->buff[i] != '>' && tool->buff[i] != '<'\
			&& tool->buff[i] != ';' && tool->buff[i] != '|'\
			&& tool->buff[i] != '&'\
			&& ft_is_separator(tool->buff[i]) != 1)
		i--;
	i++;
	ctrl->word_to_comp = ft_strsub(tool->buff, i, pos - i);
	if ((temp = ft_strrchr(ctrl->word_to_comp, '/')))
	{
		ctrl->clues = ft_strdup(temp + 1);
		ctrl->path = ft_strsub(ctrl->word_to_comp, 0,\
				ft_strlen(ctrl->word_to_comp) - ft_strlen(ctrl->clues));
	}
	else
		ctrl->clues = ft_strdup(ctrl->word_to_comp);
}

int		ft_get_comp_status(t_tc *tool, t_comp_ctrl *ctrl)
{
	int	len;
	int	pos;
	int i;

	len = (ctrl->word_to_comp ? ft_strlen(ctrl->word_to_comp) : 0);
	pos = tool->curs_y * (tool->x_max + 1) + tool->curs_x - tool->prompt_len;
	i = pos - len;
	if (i != 0)
		--i;
	else
		return (1);
	while (i > 0)
	{
		if (tool->buff[i] == ';' || tool->buff[i] == '|'\
				|| tool->buff[i] == '&')
			return (1);
		else if (!ft_is_separator(tool->buff[i]))
			return (2);
		else
			--i;
	}
	return (0);
}

void	ft_erase_comp(t_comp_ctrl *ctrl)
{
	t_comp	*current;
	t_comp	*supp;

	current = ctrl->start;
	while (current)
	{
		supp = current;
		current = current->next;
		ft_strdel(&supp->word);
		free(supp);
	}
	ctrl->start = NULL;
	ctrl->end = NULL;
}

void	ft_reset_compl(t_comp_ctrl *ctrl)
{
	ft_erase_comp(g_shell->comp_ctrl);
	ft_strdel(&ctrl->word_to_comp);
	ft_strdel(&ctrl->path);
	ft_strdel(&ctrl->clues);
	ft_bzero(ctrl, sizeof(*ctrl));
}
