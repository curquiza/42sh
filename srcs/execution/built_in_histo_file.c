#include "shell.h"

int		ft_histo_file_read(t_histo_ctrl *ctrl, char *file_name)
{
	int	fd;

	errno = 0;
	if ((fd = open(file_name, O_RDONLY)) == -1) // ne filtre pas les dir
	{
/*		if (errno == ENOENT)
			ft_putendl_fd(SHELL_NAME": history: No such file or directory", 2);
		else if (errno == EACCES)
			ft_putendl_fd(SHELL_NAME": history: Permission denied", 2);
		else
			ft_putendl_fd(SHELL_NAME": history: file open error", 2);
*/		return (CMD_FAILURE);
	}
	
		
	(void)ctrl;

	close(fd);
	return (CMD_SUCCESS);
}
