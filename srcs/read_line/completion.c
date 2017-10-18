/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 18:28:19 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/18 11:32:49 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_completion(t_tc *tool, t_comp_ctrl *ctrl)
{
	char	*match;

	ft_get_comp_word(tool, ctrl);
	ctrl->status = ft_get_comp_status(tool, ctrl);
	if (ft_get_all_candidates(ctrl, tool) != -1)
	{
		match = ft_get_matched_part(ctrl);
		if (match || (ctrl->len == 1 && ctrl->start && match))
			ft_put_matched_part(tool, ctrl->clues, match);
		else if (ctrl->len > 1 && !match && ctrl->start)
		{
			ft_ascii_sort_words(&ctrl->start);
			ft_put_all_words(tool, ctrl->start);
			ft_put_comp_prompt(tool);
		}
		ft_strdel(&match);
	}
	ft_reset_compl(g_shell->comp_ctrl);
}
