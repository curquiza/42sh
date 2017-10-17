/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 18:28:19 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/17 11:55:41 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_completion(t_tc *tool, t_comp_ctrl *ctrl)
{
	char	*match;

	ctrl->to_find = ft_get_comp_word(tool);
	ctrl->status = ft_get_comp_status(tool, ctrl);
	//ctrl->to_find = ft_get_comp_word(tool);
//	ft_putnbr2("status = ", ctrl->status);
	if (ft_get_all_words(ctrl, tool) != -1) // ft_get_all_candidats
	{
		match = ft_get_match(ctrl); //get_matched_part
		if (match || (ctrl->len == 1 && ctrl->start && match)) //???
			ft_put_matched_part(tool, ctrl->to_find, match);
		else if (ctrl->len > 1 && !match && ctrl->start)
		{
			ft_ascii_sort_words(&ctrl->start);
			ft_put_all_words(tool, ctrl->start);
			ft_put_comp_prompt(tool);
		}
		ft_strdel(&match);
	}
}
