/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 14:03:22 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:45:07 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_put_usage :
** Affiche l'usage du builtin.
*/

void	ft_put_usage(char *cmd, char flag_error, char *legal_flags)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": illegal option -- ", 2);
	ft_putchar_fd(flag_error, 2);
	ft_putendl_fd("", 2);
	ft_putstr_fd("usage: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" [-", 2);
	ft_putstr_fd(legal_flags, 2);
	ft_putendl_fd("] [...]", 2);
}

/*
** ft_check_illegal_flags :
** Retourne l'illegal option si trouvée, -1 sinon.
*/

char	ft_check_illegal_flags(char *flags, char *legal_flags)
{
	int		i;

	if (!flags || !legal_flags)
		return (0);
	i = 0;
	while (flags[i])
	{
		if (ft_strchr(legal_flags, flags[i]) == NULL)
			return (flags[i]);
		i++;
	}
	return (0);
}

/*
** ft_get_flags & ft_fill_flagstab :
** Remplit un tableau mallocé de char avec les flags trouvés (dans l'ordre).
*/

char	*ft_get_flags(char **array)
{
	char	*flags;
	int		i;
	int		cpt_flags;

	if (!array)
		return (NULL);
	flags = ft_strnew(TC_SIZE);
	i = 0;
	cpt_flags = 0;
	while (array[i])
	{
		if (array[i][0] != '-' || !ft_strcmp(array[i], "-"))
			break ;
		ft_fill_flagstab(array[i], flags, &cpt_flags);
		i++;
	}
	return (flags);
}

void	ft_fill_flagstab(char *s, char *flags, int *cpt_flags)
{
	int		i;

	i = 1;
	while (s[i])
	{
		flags[*cpt_flags] = s[i];
		*cpt_flags = *cpt_flags + 1;
		i++;
	}
}

/*
** ft_get_firstarg_index :
** Retourne l'index du 1er argument du char ** array.
*/

char	**ft_get_arg(char **array, char flag_error)
{
	int		i;

	i = 0;
	while (array[i])
	{
		if (array[i][0] != '-' || !ft_strcmp(array[i], "-")
			|| (flag_error && ft_strchr(array[i], flag_error)))
			return (array + i);
		i++;
	}
	return (array + i);
}
