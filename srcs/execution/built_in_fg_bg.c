#include "shell.h"

static int	ft_check_arg(t_job *job_lst, char **arg, char *builtin)
{
	if (!arg)
		return (-1);
	if (job_lst == NULL)
	{
		ft_put_errmsg(g_shell->name, builtin, "no job");
		return (-1);
	}
	else if (arg[0] == NULL && job_lst)
		return (0);
	if (ft_tablen(arg) > 1)
	{
		ft_put_errmsg(g_shell->name, builtin, "too many arguments");
		return (-1);
	}
	if (ft_is_uns_nbr(arg[0]) == 0
		|| ft_atoi(arg[0]) == 0 || ft_atoi(arg[0]) > ft_joblst_len(job_lst))
	{
		ft_put_errmsg(g_shell->name, builtin, "no such job");
		return (-1);
	}
	return (0);
}

static t_job	*ft_get_job(t_job *lst, char *job_pos)
{
	(void)lst;
	(void)job_pos;
	return (NULL);
}

int		ft_builtin_fg(t_ast *ast)
{
	t_job	*curr_job;

	if (ft_check_arg(g_shell->job_lst, ast->argtab + 1, "fg") == -1)
		return (CMD_FAILURE);
	curr_job = ft_get_job(g_shell->job_lst, ast->argtab[1]);
	return (CMD_SUCCESS);
}

int		ft_builtin_bg(t_ast *ast)
{
	(void)ast;
	ft_putendl("BUILTIN BG");
	return (CMD_SUCCESS);
}

