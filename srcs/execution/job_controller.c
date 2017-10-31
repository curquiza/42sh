#include "shell.h"

static int	ft_job_exists(t_job *job_lst, t_job *current)
{
	while (job_lst)
	{
		//if (current->pgid == job_lst->pgid)
		if (current == job_lst)
			return (1);
		job_lst = job_lst->next;
	}
	return (0);
}

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

static void	ft_del_job(t_job *current)
{
	t_job	*tmp;

	if (!g_shell->job_lst)
		return ;
	if (g_shell->job_lst == current)
	{
		ft_job_suppr_elem(&g_shell->job_lst);
		return ;
	}
	tmp = g_shell->job_lst;
	while (tmp->next)
	{
		if (tmp->next == current)
		{
			ft_job_suppr_elem(&tmp->next);
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
			ft_del_job(*job);
		else
		{
			ft_strdel(&(*job)->cmd_name);
			free(*job);
			*job = NULL;
		}
		if (WIFSIGNALED(ret))
		{
			ft_putnbr((int)pid);
			ft_putstr(" : Terminated by signal ");
			ft_putnbr(WTERMSIG(ret));
			ft_putchar('\n');
		}
	}
	return (ret);
}

void		ft_exit_job(int sig)
{
	t_job	*tmp;
	t_job	*supp;
	int		i;

	i = 1;
	tmp = g_shell->job_lst;
	while (tmp)
	{
		ft_putendl_fd("titi", 2);
		if (waitpid(tmp->pgid, &i, WNOHANG | WCONTINUED | WUNTRACED) == -1
			&& errno == 10 && sig)
		{
			ft_putchar('[');
			ft_putnbr(i);
			ft_putstr("]    ");
			ft_putnbr(tmp->pgid);
			ft_putstr(" done	");
			ft_putendl(tmp->cmd_name);
			supp = tmp;
			ft_del_job(supp);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
		i++;
	}
	signal(SIGCHLD, SIG_DFL);
}
