/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <rcarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:27:01 by rcarette          #+#    #+#             */
/*   Updated: 2017/10/16 14:23:56 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		completion_dir(t_completion data_comple, t_tc *tool)
{
	t_rlist		*list;
	char		*temporary;
	int			nbr;

	init_var(&temporary, &nbr);
	if (!(ft_strlen(data_comple.string)))
	{
		if (!(list = ft_getfiles(data_comple, temporary, 2)))
			return (tputs(tgetstr("bl", NULL), 1, &ft_termput));
	}
	else
	{
		if (!(list = ft_getfiles_opt(data_comple, temporary, 2)))
			return (tputs(tgetstr("bl", NULL), 1, &ft_termput));
	}
	(lenght_rlist_s(list) == 1) ? stock_completion(list, data_comple, tool) : 0;
	if (lenght_rlist_s(list) > 1)
		nbr = countnbr_match(list, ft_getsmall_file(list));
	nbr = (nbr == (int)ft_strlen(data_comple.string)) ? 0 : nbr;
	if (!nbr && lenght_rlist_s(list) > 1)
		display_all_completion(list, tool, ft_getbigsize_file(list));
	else if (nbr > 0)
		stock_completion_match(data_comple, nbr, ft_getsmall_file(list), tool);
	clear_list_s(&list);
	return (1);
}
