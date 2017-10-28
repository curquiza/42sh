#include "shell.h"

static int	ft_job_exists(t_job *job_lst, t_job *current)
{
	while (job_lst)
	{
		if (current->pgid == job_lst->pgid)
			return (1);
		job_lst = job_lst->next;
	}
	return (0);
}

//void	ft_lexlst_remove_if(t_lexeme **begin_list, void *ref, int mode)
//{
//	t_lexeme	*current;
//
//	if (*begin_list)
//	{
//		current = *begin_list;
//		while (current->next)
//		{
//			if (mode == 0 && ft_strcmp(current->next->s, ref) == 0)
//				ft_lex_suppr_elem(&(current->next));
//			else if (mode == 1 && current->next->token == *(int *)ref)
//				ft_lex_suppr_elem(&(current->next));
//			else
//				current = current->next;
//		}
//		if (*begin_list)
//		{
//			if (mode == 0 && ft_strcmp((*begin_list)->s, ref) == 0)
//				ft_lex_suppr_elem(begin_list);
//			else if (mode == 1 && (*begin_list)->token == *(int *)ref)
//				ft_lex_suppr_elem(begin_list);
//		}
//	}
//}

static void	ft_job_suppr_elem(t_job **elem)
{
	t_job	*suppr;

	suppr = *elem;
	*elem = (*elem)->next;
	ft_strdel(&suppr->cmd_name);
	suppr->pgid = 0;
	suppr->next = NULL;
	free(suppr);
}

static void	ft_del_job(t_job **lst, t_job **current)
{
	t_job 	*prev;
	t_job	*tmp;

	if (!lst)
		return ;
	if (*lst && *lst == *current)
	{
		ft_job_suppr_elem(lst);
		return ;
	}
	tmp = *lst;
	while (tmp)
	{
		prev = tmp;
		if (tmp == *current)
		{
			ft_job_suppr_elem(&tmp);
			return ;
		}
		tmp = tmp->next;
	}
}

int		ft_wait_for_job(t_job **job)
{
	int		ret;
	pid_t	pid;

	ret = 0;
	pid = waitpid((*job)->pgid, &ret, WUNTRACED);
	if (WIFSTOPPED(ret))
	{
		if (ft_job_exists(g_shell->job_lst, *job) == 0)
			ft_joblst_addback(&g_shell->job_lst, *job);
	}
	else
	{
		if (ft_job_exists(g_shell->job_lst, *job) == 1)
			ft_del_job(&g_shell->job_lst, job);
		else
		{
			ft_strdel(&(*job)->cmd_name);
			free(*job);
			*job = NULL;
		}
	}
	return (ret);
}

