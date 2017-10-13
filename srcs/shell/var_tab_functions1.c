/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_tab_functions1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:12:49 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:12:50 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_get_varvalue(char **vartab, char *varname)
{
	int		len;
	int		varlen;

	if (vartab)
	{
		varlen = ft_strlen(varname);
		while (*vartab)
		{
			len = 0;
			while ((*vartab)[len] && (*vartab)[len] != '=')
				len++;
			if (len == varlen && ft_strncmp(*vartab, varname, len) == 0)
				return (ft_strchr(*vartab, '=') + 1);
			vartab++;
		}
	}
	return (NULL);
}

int		ft_get_varindex(char **vartab, char *varname)
{
	int		len;
	int		index;
	int		varlen;

	if (vartab)
	{
		varlen = ft_strlen(varname);
		index = 0;
		while (vartab[index])
		{
			len = 0;
			while (vartab[index][len] && vartab[index][len] != '=')
				len++;
			if (len == varlen && ft_strncmp(vartab[index], varname, len) == 0)
				return (index);
			index++;
		}
	}
	return (-1);
}

int		ft_exist_in(char **vartab, char *varname)
{
	int		varlen;
	int		len;

	if (vartab)
	{
		varlen = ft_strlen(varname);
		while (*vartab)
		{
			len = 0;
			while ((*vartab)[len] && (*vartab)[len] != '=')
				len++;
			if (varlen == len && ft_strncmp(*vartab, varname, len) == 0)
				return (1);
			vartab++;
		}
	}
	return (0);
}
