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

int		ft_wait_for_job(t_job *job)
{
	int		ret;
	pid_t	pid;

	ret = 0;
	pid = waitpid(job->pgid, &ret, WUNTRACED);
	if (WIFSTOPPED(ret))
	{
		if (ft_job_exists(g_shell->job_lst, job) == 0)
			ft_joblst_addback(&g_shell->job_lst, job);
	}
	return (ret);
}

