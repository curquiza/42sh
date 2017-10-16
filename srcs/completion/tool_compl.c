#include "shell.h"

void	clear_list_s(t_rlist **li)
{
	t_rlist	*temporary;

	if (*li == NULL)
		return ;
	while (*li)
	{
		temporary = (*li);
		(*li) = (*li)->next;
		free(temporary->file);
		free(temporary);
	}
	*li = NULL;
}

//char	*ft_strndup(char *str, int size) //attention memallocde romain
//{
//	char	*new_str;
//	int		i;
//
//	i = -1;
//	if (!str || *str == '\0')
//		return (ft_strnew(1));
//	new_str = ft_memalloc((size + 1));
//	new_str[size + 1] = '\0';
//	while (++i < size)
//		new_str[i] = str[i];
//	return (new_str);
//}

size_t		ft_rstrlen(const char *s)
{
	int		i;

	if (s == NULL)
		return (0);
	if (*s == '\0')
		return (0);
	i = -1;
	while (s[++i])
		;
	return (i);
}

int		lenght_rlist_s(t_rlist *li)
{
	int		size_li;

	size_li = 0;
	while (li)
	{
		++size_li;
		li = li->next;
	}
	return (size_li);
}

static t_rlist		*new_list(void) // WTF
{
	return (NULL);
}

static t_rlist		*creat_new_elem_s(const char *str, int type)
{
	t_rlist		*new_link;
	int			size_str;

	size_str = (ft_rstrlen(str) + 1);
	new_link = new_list();
	if (!(new_link = (t_rlist *)malloc(sizeof(t_rlist))))
		exit(EXIT_FAILURE);
	if (!(new_link->file = (char *)malloc(sizeof(char) * size_str)))
		exit(EXIT_FAILURE);
	new_link->size_file = ft_rstrlen(str);
	new_link->type = type;
	ft_memcpy(new_link->file, str, size_str);
	new_link->next = NULL;
	return (new_link);
}

void	push_back_s(t_rlist **list, const char *str, int type)
{
	t_rlist		*temporary;
	t_rlist		*new_link;

	new_link = NULL;
	temporary = (*list);
	if (*list == NULL)
		*list = creat_new_elem_s(str, type);
	else
	{
		new_link = creat_new_elem_s(str, type);
		while (temporary->next)
			temporary = temporary->next;
		temporary->next = new_link;
	}
}

int		clear_tab(char **board)
{
	int		i;

	i = -1;
	while (board[++i])
		free(board[i]);
	free(board);
	return (0);
}

int		ft_calc_position(t_tc *tool)
{
	return (tool->curs_y * tool->x_max + tool->curs_x - tool->prompt_len);
}
