/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 18:28:19 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/17 12:33:47 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_print_comp(t_comp_ctrl *ctrl)
{
	ft_putendl2_fd("\nword_to_comp : ", ctrl->word_to_comp, 1);
	if (ctrl->path)
		ft_putendl2_fd("path : ", ctrl->path, 1);
	else
		ft_putendl2_fd("path : ", "NULL", 1);
	ft_putendl2_fd("clues : ", ctrl->clues, 1);
	ft_putnbr2("len : ", ctrl->len);
	ft_putnbr2("status = ", ctrl->status);
}

void	ft_completion(t_tc *tool, t_comp_ctrl *ctrl)
{
	//char	*match;

	ft_get_comp_word(tool, ctrl);
	ctrl->status = ft_get_comp_status(tool, ctrl);
	//ctrl->to_find = ft_get_comp_word(tool);
//	ft_putnbr2("status = ", ctrl->status);
	ft_print_comp(ctrl);
//	if (ft_get_all_words(ctrl, tool) != -1) // ft_get_all_candidats
//	{
//		match = ft_get_match(ctrl); //get_matched_part
//		if (match || (ctrl->len == 1 && ctrl->start && match)) //???
//			ft_put_matched_part(tool, ctrl->to_find, match);
//		else if (ctrl->len > 1 && !match && ctrl->start)
//		{
//			ft_ascii_sort_words(&ctrl->start);
//			ft_put_all_words(tool, ctrl->start);
//			ft_put_comp_prompt(tool);
//		}
//		ft_strdel(&match);
//	}
}
