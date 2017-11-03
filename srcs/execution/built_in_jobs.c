/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_jobs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 12:29:57 by sfranc            #+#    #+#             */
/*   Updated: 2017/11/03 12:30:00 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_builtin_jobs(t_ast *ast)
{
	int		i;
	t_job	*tmp;

	(void)ast;
	tmp = g_shell->job_lst;
	i = 1;
	while (tmp)
	{
		ft_putchar('[');
		ft_putnbr(i);
		ft_putstr("]        ");
		ft_putnbr(tmp->pgid);
		ft_putstr("	");
		ft_putendl(tmp->cmd_name);
		i++;
		tmp = tmp->next;
	}
	return (CMD_SUCCESS);
}
