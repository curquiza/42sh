/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_init_reset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 14:48:11 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/17 11:55:25 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_get_comp_word(t_tc *tool)
{
	int		pos;
	int		i;

	pos = tool->curs_y * (tool->x_max + 1) + tool->curs_x - tool->prompt_len;
	i = pos - 1;
	while (i >= 0 && tool->buff[i] != '>' && tool->buff[i] != '<'\
			&& tool->buff[i] != ';' && tool->buff[i] != '|'\
			&& tool->buff[i] != '&'\
			&& ft_is_separator(tool->buff[i]) != 1)
		i--;
	i++;
	return (ft_strsub(tool->buff, i, pos - i));
}


int		ft_get_comp_status(t_tc *tool, t_comp_ctrl *ctrl)
{
	int	len;
	int	pos;
	int i;

	len = (ctrl->to_find ? ft_strlen(ctrl->to_find) : 0);
//	ft_putnbr2("len = ", len);
	pos = tool->curs_y * (tool->x_max + 1) + tool->curs_x - tool->prompt_len;
//	ft_putstr("\ntool->buff[pos] = ");
//	ft_putchar('"');
//	ft_putchar(tool->buff[pos]);
//	ft_putchar('"');
	i = pos - len;
	if (i != 0)
		--i;
	else
		return (1);
//	ft_putstr("\ndepart = ");
//	ft_putchar('"');
//	ft_putchar(tool->buff[i]);
//	ft_putchar('"');
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

//int		ft_get_comp_status(t_tc *tool, int status)
//{
//	int		i;
//	int		ret;
//
//	ret = status;
//	if (status == 0)
//		ret = 1;
//	i = tool->curs_y * (tool->x_max + 1) + tool->curs_x - tool->prompt_len;
//	while (i >= 0 && ft_is_separator(tool->buff[i]) != 1)
//		i--;
//	i++;
//	if (i != 0)
//	{
//		i--;
//		while (i >= 0 && ft_is_separator(tool->buff[i]) == 1)
//			i--;
//		if (i != -1)
//			ret = 2;
//	}
//	return (ret);
//}

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
	ft_strdel(&ctrl->to_find);
	ft_bzero(ctrl, sizeof(*ctrl));
}
