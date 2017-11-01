/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_tab_functions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:12:54 by curquiza          #+#    #+#             */
/*   Updated: 2017/11/01 20:05:13 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_add_var(char ***vartab, char *newvar, char *value)
{
	char	**tmp;
	int		i;

	if (!(tmp = (char **)malloc(sizeof(**vartab) * (ft_tablen(*vartab) + 2))))
		ft_exit("malloc error", 1);
	i = 0;
	while ((*vartab) && (*vartab)[i])
	{
		tmp[i] = (*vartab)[i];
		i++;
	}
	if (value == NULL)
		tmp[i] = ft_strdup(newvar);
	else
		tmp[i] = ft_strjoin3(newvar, "=", value);
	tmp[i + 1] = NULL;
	free(*vartab);
	*vartab = tmp;
}

void	ft_chg_varval(char **vartab, char *newvar, char *value)
{
	char	*name;
	int		len;
	int		index;

	if (value == NULL)
	{
		len = 0;
		while (newvar[len] && newvar[len] != '=')
			len++;
		name = ft_strsub(newvar, 0, len);
	}
	else
		name = newvar;
	index = ft_get_varindex(vartab, name);
	free(vartab[index]);
	if (value == NULL)
	{
		vartab[index] = ft_strdup(newvar);
		free(name);
	}
	else
		vartab[index] = ft_strjoin3(newvar, "=", value);
}

void	ft_chg_varval_or_add(char ***vartab, char *newvar, char *value)
{
	int		len;
	char	*tmpvar;

	len = 0;
	if (value == NULL)
	{
		while (newvar[len] && newvar[len] != '=')
			len++;
		tmpvar = ft_strsub(newvar, 0, len);
	}
	else
		tmpvar = newvar;
	if (ft_exist_in(*vartab, tmpvar) == 1)
		ft_chg_varval(*vartab, newvar, value);
	else
		ft_add_var(vartab, newvar, value);
	if (value == NULL)
		ft_strdel(&tmpvar);
}

void	ft_suppr_var(char ***vartab, char *varname)
{
	int		index;
	char	**tmp;
	int		i;
	int		j;

	if ((index = ft_get_varindex(*vartab, varname)) == -1)
		return ;
	tmp = *vartab;
	if (!(*vartab = (char **)malloc(sizeof(**vartab) * ft_tablen(tmp))))
		ft_exit("malloc error", 1);
	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (i != index)
		{
			(*vartab)[j] = tmp[i];
			j++;
		}
		i++;
	}
	(*vartab)[j] = NULL;
	ft_strdel(&tmp[index]);
	free(tmp);
}

/*
** For READ builtin: check if the var exists in env, if so, change it, else
** add or change the varaible within the local variables.
*/

void	ft_check_env_before_chg_or_add(char *var, char *value)
{
	if (ft_exist_in(g_shell->var_env, var))
		ft_chg_varval(g_shell->var_env, var, value);
	else
		ft_chg_varval_or_add(&g_shell->var_loc, var, value);
}
