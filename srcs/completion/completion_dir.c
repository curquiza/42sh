/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <rcarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:27:01 by rcarette          #+#    #+#             */
/*   Updated: 2017/07/07 05:23:36 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		completion_dir(t_completion data_comple, t_line_edit *line)
{
	t_rlist		*list;
	char		*temporary;
	int			nbr;

	init_var(&temporary, &nbr);
	if (!(ft_strlen(data_comple.string)))
	{
		if (!(list = ft_getfiles(data_comple, temporary, 2)))
			return (tputs(tgetstr("bl", NULL), 1, &ft_putchar));
	}
	else
	{
		if (!(list = ft_getfiles_opt(data_comple, temporary, 2)))
			return (tputs(tgetstr("bl", NULL), 1, &ft_putchar));
	}
	(lenght_rlist_s(list) == 1) ? stock_completion(list, data_comple, line) : 0;
	if (lenght_rlist_s(list) > 1)
		nbr = countnbr_match(list, ft_getsmall_file(list));
	nbr = (nbr == (int)ft_strlen(data_comple.string)) ? 0 : nbr;
	if (!nbr && lenght_rlist_s(list) > 1)
		display_all_completion(list, line, ft_getbigsize_file(list));
	else if (nbr > 0)
		stock_completion_match(data_comple, nbr, ft_getsmall_file(list), line);
	clear_list_s(&list);
	return (1);
}
