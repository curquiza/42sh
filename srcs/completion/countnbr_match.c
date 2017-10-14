/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countnbr_match.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <rcarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 15:14:22 by rcarette          #+#    #+#             */
/*   Updated: 2017/07/07 05:25:10 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static void		init_match(t_match *match, t_list *list)
{
	match->i = -1;
	match->j = 0;
	match->nbr_character = 0;
	match->size = 0;
	match->list = list;
	match->size_list = lenght_list_s(list);
}

int				countnbr_match(t_list *list, char *small_str)
{
	t_match		match;

	init_match(&match, list);
	while (small_str[++match.i])
		while (match.list)
		{
			if (match.list->file[match.i] == small_str[match.i])
				match.nbr_character += (1);
			match.list = match.list->next;
			match.j++;
			if (match.j == match.size_list)
			{
				if (match.nbr_character == match.size_list)
				{
					++match.size;
					match.list = list;
					++match.i;
					match.j = 0;
					match.nbr_character = 0;
				}
				else
					return (match.size);
			}
		}
	return (0);
}
