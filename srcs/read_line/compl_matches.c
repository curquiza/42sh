/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_matches.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 16:37:32 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/17 14:45:38 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_put_matched_part(t_tc *tool, char *to_find, char *match)
{
	int		i;

	i = ft_strlen(to_find);
	if (i > (int)ft_strlen(match))
		return ;
	ft_insert(match + i, tool);
}

int		ft_check_other_words(int i, int len, t_comp *comp)
{
	char	c;

	c = comp->word[len + i];
	while (comp)
	{
		if (len + i > (int)ft_strlen(comp->word))
			return (0);
		if (comp->word[len + i] != c)
			return (0);
		comp = comp->next;
	}
	return (1);
}

char	*ft_get_match(t_comp_ctrl *ctrl)
{
	int		len;
	int		i;

	len = ft_strlen(ctrl->to_find);
	if (!ctrl->len || !ctrl->start || len > (int)ft_strlen(ctrl->start->word)) //???
		return (NULL);
	if (ctrl->len == 1)
		return (ft_strdup(ctrl->start->word));
	i = -1;
	while (ctrl->start->word[len + ++i])
	{
		if (ft_check_other_words(i, len, ctrl->start) == 0)
			break ;
	}
	return (i ? ft_strsub(ctrl->start->word, 0, len + i) : NULL);
}
