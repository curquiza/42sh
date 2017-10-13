/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:43:35 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 20:09:55 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_check_flag_n(char **array)
{
	int		i;
	int		j;

	i = 0;
	while (array[i])
	{
		if (array[i][0] != '-' || !ft_strcmp(array[i], "-"))
			return (0);
		j = 1;
		while (array[i][j] == 'n')
			j++;
		if (j == (int)ft_strlen(array[i]))
			return (1);
		else
			return (0);
		i++;
	}
	return (0);
}

char	**ft_get_arg_echo(char **array)
{
	int		i;
	int		j;

	i = 0;
	while (array[i])
	{
		if (array[i][0] != '-' || !ft_strcmp(array[i], "-"))
			return (array + i);
		j = 1;
		while (array[i][j] == 'n')
			j++;
		if (j != (int)ft_strlen(array[i]))
			return (array + i);
		i++;
	}
	return (array + i);
}

int		ft_builtin_echo(t_ast *ast)
{
	int		i;
	int		nbr_arg;
	char	**arg;
	char	flag_n;

	flag_n = ft_check_flag_n(ast->argtab + 1);
	arg = ft_get_arg_echo(ast->argtab + 1);
	nbr_arg = ft_tablen(arg);
	i = 0;
	while (arg[i])
	{
		ft_putstr(arg[i]);
		if (i != nbr_arg - 1)
			ft_putchar(' ');
		i++;
	}
	if (flag_n == 0)
		ft_putchar('\n');
	return (CMD_SUCCESS);
}
