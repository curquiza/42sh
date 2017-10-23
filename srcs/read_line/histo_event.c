#include "shell.h"

void	ft_histo_event(t_tc *tool, t_histo_ctrl *ctrl)
{
	(void)ctrl;
	ft_putstr("HISTO EVENT");
	tool->nbr_char = ft_strlen(tool->buff);
}
