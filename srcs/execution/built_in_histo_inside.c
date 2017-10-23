#include "shell.h"

void	ft_histo_inside_clearall(t_histo_ctrl *ctrl)
{
	t_histo *tmp;
	t_histo *prev;

	tmp = ctrl->start;
	while (tmp)
	{
		ft_strdel(&tmp->line);
		prev = tmp;
		tmp = tmp->next;
		free(prev);
	}
	ctrl->start = NULL;
	ctrl->end = NULL;
	ctrl->len = 0;
}

int		ft_histo_inside_delone(t_histo_ctrl *ctrl, int offset)
{
	int	i;
	t_histo	*tmp;

	if (!offset || offset > ctrl->len)
	{
		ft_putendl_fd(SHELL_NAME": history: offset out of range", 2);
		return (CMD_FAILURE);
	}
	i = 1;
	tmp = ctrl->end;
	while (i++ != offset && tmp)
		tmp = tmp->prev;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	else
		ctrl->start = tmp->next;
	
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	else
		ctrl->end = tmp->prev;
	ctrl->len--;
	ft_strdel(&tmp->line);
	free(tmp);
	return (CMD_SUCCESS);
}

void	ft_histo_inside_addline(t_histo_ctrl *ctrl, char *to_add)
{
	t_histo	*new;
	t_histo	*tmp;

	new = ft_memalloc(sizeof(*new));
	new->line = ft_strdup(to_add);
	if (!ctrl->start)
	{
		ctrl->start = new;
		ctrl->end = new;
	}
	else
	{
		tmp = ctrl->start;
		ctrl->start = new;
		new->next = tmp;
		tmp->prev = new;
	}
	ctrl->len++;
	if (ctrl->len > HISTO_SIZE)
	{
		ft_del_old_histo(ctrl);
		ctrl->len--;
	}
}
