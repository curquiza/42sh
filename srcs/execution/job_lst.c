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

//t_job	*ft_joblst_last(t_job *lst)
//{
//	if (lst == NULL)
//		return (NULL);
//	while (lst->next)
//		lst = lst->next;
//	return (lst);
//}
//
//void	ft_job_suppr_elem(t_job **elem)
//{
//	t_job	*suppr;
//
//	suppr = *elem;
//	*elem = (*elem)->next;
//	ft_strdel(&suppr->cmd_name);
//	suppr->pgid = 0;
//	suppr->next = NULL;
//	free(suppr);
//}
//
//void	ft_joblstdel(t_job **alst)
//{
//	t_job	*current;
//
//	if (!alst)
//		return ;
//	current = *alst;
//	while (current)
//		ft_job_suppr_elem(&(current));
//	*alst = NULL;
//}
