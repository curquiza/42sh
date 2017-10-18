#include "shell.h"

int		ft_check_user_right(char *path, char *name)
{
	struct stat		temp_stat;
	char			*temp;
	int				ret;

	temp = ft_strjoin3(path, "/", name);
	if ((ret = stat(temp, &temp_stat)) != -1\
			&& ((temp_stat.st_mode & S_IXUSR) == S_IXUSR))
	{
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}

int		ft_check_is_dir(char *path, char *name)
{
	struct stat		temp_stat;
	char			*temp;

	temp = ft_strjoin3(path, "/", name);
	if ((stat(temp, &temp_stat)) == -1)
	{
		free(temp);
		return (0);
	}
	else if (S_ISDIR(temp_stat.st_mode))
	{
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}
