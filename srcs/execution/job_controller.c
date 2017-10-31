#include "shell.h"

static int	ft_job_exists(t_job *job_lst, t_job *current)
{
	while (job_lst)
	{
		if (current == job_lst)
			return (1);
		job_lst = job_lst->next;
	}
	return (0);
}

void	ft_stopped_msg(t_job *job)
{
	int		i;
	t_job	*tmp;

	tmp = g_shell->job_lst;
	i = 1;
	while (tmp)
	{
		if (job == tmp)
			break ;
		tmp = tmp->next;
		i++;
	}
	ft_putstr("\n[");
	ft_putnbr(i);
	ft_putstr("]    ");
	ft_putnbr(tmp->pgid);
	ft_putendl2_fd(" Stopped    ", tmp->cmd_name, 1);
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
		ft_stopped_msg(*job);
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
		if (waitpid(tmp->pgid, &i, WNOHANG | WCONTINUED | WUNTRACED) == -1
			&& errno == 10 && sig)
		{
			ft_putchar('[');
			ft_putnbr(i);
			ft_putstr("]    ");
			ft_putnbr(tmp->pgid);
			ft_putendl2_fd(" Done    ", tmp->cmd_name, 1);
			supp = tmp;
			tmp = tmp->next;
			ft_del_job(supp);
		}
		else
			tmp = tmp->next;
		i++;
	}
	signal(SIGCHLD, SIG_DFL);
}
