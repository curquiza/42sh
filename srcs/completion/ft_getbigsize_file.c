/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getbigsize_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 07:11:19 by rcarette          #+#    #+#             */
/*   Updated: 2017/06/29 22:08:38 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_getbigsize_file(t_rlist *list)
{
	int		size;

	size = 0;
	while (list)
	{
		if (size < (int)ft_strlen(list->file))
			size = ft_strlen(list->file);
		list = list->next;
	}
	return (size);
}
