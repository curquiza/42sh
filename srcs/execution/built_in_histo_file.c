#include "shell.h"

int			ft_histo_file_read(t_histo_ctrl *ctrl, char *file_name)
{
	int		fd;
	char	*line;
	int		ret;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (CMD_FAILURE);
	line = NULL;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		ft_clean_tab(line);
		if (line && *line)
			ft_histo_inside_addline(ctrl, line);
		ft_strdel(&line);
	}
	if (ret == -1)
		return (CMD_FAILURE);
	close(fd);
	return (CMD_SUCCESS);
}

int			ft_histo_file_write(t_histo_ctrl *ctrl, char *file_name, int mode)
{
	int		fd;
	t_histo	*tmp;

	if (mode == HISTO_WRITE && (fd = open(file_name, O_RDWR | O_CREAT\
					| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		return (CMD_FAILURE);
	if (mode == HISTO_APPEND && (fd = open(file_name, O_RDWR | O_CREAT\
					| O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		return (CMD_FAILURE);
	tmp = ctrl->end;
	while (tmp)
	{
		ft_putendl_fd(tmp->line, fd);
		tmp = tmp->prev;
	}
	close(fd);
	return (CMD_SUCCESS);
}
