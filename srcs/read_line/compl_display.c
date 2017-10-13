/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:16:28 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:17:22 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_put_comp_prompt(t_tc *tool)
{
	char	*tmp;
	int		old_pos;
	int		new_pos;
	int		i;

	ft_putstr(COMP_PROMPT);
	tmp = ft_strdup(tool->buff);
	old_pos = tool->curs_y * (tool->x_max + 1)
			+ tool->curs_x - tool->prompt_len;
	ft_init_struct_tc(tool, ft_strlen(COMP_PROMPT));
	ft_insert(tmp, tool);
	ft_strdel(&tmp);
	new_pos = tool->curs_y * (tool->x_max + 1)
			+ tool->curs_x - tool->prompt_len;
	i = new_pos;
	while (i > old_pos)
	{
		ft_move_left(tool);
		i--;
	}
}

int			ft_word_len_max(t_comp *comp)
{
	int		max;
	int		len;

	if (!comp)
		return (0);
	max = ft_strlen(comp->word);
	while (comp)
	{
		if (comp->word)
			len = ft_strlen(comp->word);
		else
			len = 0;
		if (max < len)
			max = len;
		comp = comp->next;
	}
	return (max);
}

static void	ft_put_blank(int len_max, int *i, t_comp *comp, int w_per_col)
{
	int		len;

	if (comp->word)
		len = len_max - ft_strlen(comp->word);
	else
		len = 0;
	while (len--)
		ft_putchar(' ');
	ft_putstr("  ");
	(*i)++;
	if (*i == w_per_col && comp->next)
	{
		*i = 0;
		ft_putchar('\n');
	}
}

void		ft_put_all_words(t_tc *tool, t_comp *comp)
{
	int		len_max;
	int		w_per_col;
	int		i;

	len_max = ft_word_len_max(comp);
	w_per_col = (tool->x_max + 1) / (len_max + 2);
	ft_putendl("");
	if (w_per_col == 0)
		return ;
	i = 0;
	while (comp)
	{
		ft_putstr(comp->word);
		ft_put_blank(len_max, &i, comp, w_per_col);
		comp = comp->next;
	}
	ft_putchar('\n');
}
