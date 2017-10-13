/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_parameter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 16:12:46 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:54:46 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_replace_parameter(char **s, int *i, int len, t_shell *shell)
{
	char	*name;
	char	*value;
	char	*tmp;
	int		value_len;
	int		name_len;

	name = ft_strsub(*s, *i + 1, len);
	if (!(value = ft_get_varvalue(shell->var_env, name))
		&& !(value = ft_get_varvalue(shell->var_loc, name))
		&& !(value = ft_get_varvalue(shell->var_priv, name)))
		value = ft_strdup("");
	else
		value = ft_strdup(value);
	value_len = ft_strlen(value);
	name_len = ft_strlen(name);
	tmp = *s;
	*s = ft_strnew(ft_strlen(tmp) - (name_len + 1) + value_len);
	ft_strncpy(*s, tmp, *i);
	ft_strncpy(*s + *i, value, value_len);
	ft_strcpy(*s + *i + value_len, tmp + *i + 1 + name_len);
	free(tmp);
	free(name);
	free(value);
	*i = *i + value_len;
}

void	ft_param_exp_loop(char **s, t_shell *shell, int *i)
{
	int		len;

	if ((*s)[*i] == 92 && (*s)[*i + 1])
		*i = *i + 2;
	else if ((*s)[*i] == 39)
	{
		*i = ft_next_squote(*i, *s);
		(*s)[*i] ? (*i)++ : 0;
	}
	else if ((*s)[*i] == '$'
				&& (ft_isdigit((*s)[*i + 1]) == 1 || (*s)[*i + 1] == '?'))
		ft_replace_parameter(s, i, 1, shell);
	else if ((*s)[*i] == '$' && (*s)[*i + 1] && !ft_isdigit((*s)[*i + 1])
			&& (*s)[*i + 1] != '_' && !ft_isalnum((*s)[*i + 1]))
		*i = *i + 2;
	else if ((*s)[*i] == '$' && (*s)[*i + 1] && (*s)[*i + 1] != '\n'
							&& !ft_is_separator((*s)[*i + 1]))
	{
		len = 0;
		while ((*s)[*i + 1 + len] == '_' || ft_isalnum((*s)[*i + 1 + len]))
			len++;
		ft_replace_parameter(s, i, len, shell);
	}
	else
		(*i)++;
}

/*
** ft_parameter_expansion :
** Gestion de la parameter expansion, càd du dollar.
** Remplace $MY_VAR par la valeur de la variable MY_VAR.
*/

void	ft_parameter_expansion(char **s, t_shell *shell)
{
	int		i;

	if (!s || !*s)
		return ;
	i = 0;
	while ((*s)[i])
		ft_param_exp_loop(s, shell, &i);
}
