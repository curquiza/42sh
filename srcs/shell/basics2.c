/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 14:05:08 by sfranc            #+#    #+#             */
/*   Updated: 2017/11/03 14:05:27 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	ft_clean_tab remove `\t' from line (nothing is done for `\n')
*/

void	ft_clean_tab(char *line)
{
	int	i;

	if (!line)
		return ;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\t' || !ft_isprint(line[i]))
			line[i] = ' ';
		++i;
	}
}

/*
**	remove only the escape char
*/

void	ft_escape_removal_only(char **s)
{
	int		i;

	if (!*s)
		return ;
	i = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == 92 && (*s)[i + 1])
			ft_escape_char(s, &i, (*s)[i + 1]);
		else
			i++;
	}
}
