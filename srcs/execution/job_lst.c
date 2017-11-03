/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 12:35:20 by sfranc            #+#    #+#             */
/*   Updated: 2017/11/03 12:35:27 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_joblst_addback(t_job **alst, t_job *new)
{
	t_job	*tmp;

	if (alst == NULL)
		return ;
	tmp = *alst;
	if (*alst == NULL)
		*alst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_job	*ft_joblst_new(char *cmdname, int pgid)
{
	t_job		*new;

	if (!(new = (t_job *)malloc(sizeof(*new))))
		ft_exit("malloc error", 1);
	if (cmdname)
		new->cmd_name = ft_strdup(cmdname);
	else
		new->cmd_name = NULL;
	new->pgid = pgid;
	new->next = NULL;
	return (new);
}

int		ft_joblst_len(t_job *lst)
{
	int		cpt;

	cpt = 0;
	while (lst)
	{
		cpt++;
		lst = lst->next;
	}
	return (cpt);
}

t_job	*ft_joblst_last(t_job *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_job	*ft_joblst_at(t_job *lst, size_t n)
{
	size_t	i;

	if (!lst)
		return (NULL);
	i = 1;
	while (lst)
	{
		if (i == n)
			return (lst);
		lst = lst->next;
		i++;
	}
	return (NULL);
}
