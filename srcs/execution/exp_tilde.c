/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_tilde.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 10:38:01 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:57:02 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_get_new_home(t_shell *shell)
{
	struct passwd		*pwd;

	if ((pwd = getpwuid(ft_atoi(ft_get_varvalue(shell->var_priv, "UID")))))
		return (ft_strjoin("/Users/", pwd->pw_name));
	else
		return (ft_strdup("/Users"));
}

void	ft_replace_tilde(char **s, t_shell *shell, int *i)
{
	char	*home;
	char	*tilde;
	int		tilde_len;
	char	*tmp;

	if (!(home = ft_get_varvalue(shell->var_env, "HOME"))
		&& !(home = ft_get_varvalue(shell->var_env, "HOME")))
		tilde = ft_get_new_home(shell);
	else
		tilde = ft_strdup(home);
	tmp = *s;
	tilde_len = ft_strlen(tilde);
	*s = ft_strnew(ft_strlen(tmp) + tilde_len - 1);
	ft_strncpy(*s, tmp, *i);
	ft_strncpy(*s + *i, tilde, tilde_len);
	ft_strcpy(*s + *i + tilde_len, tmp + *i + 1);
	ft_strdel(&tmp);
	ft_strdel(&tilde);
	*i = *i + tilde_len - 1;
}

void	ft_tilde_expansion(char **s, t_shell *shell)
{
	int		i;

	if (!s || !*s)
		return ;
	i = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == 92)
			i++;
		else if ((*s)[i] == 39)
			i = ft_next_squote(i, *s);
		else if ((*s)[i] == 34)
			i = ft_next_dquote(i, *s);
		else if ((*s)[i] == '~')
		{
			ft_replace_tilde(s, shell, &i);
		}
		if (i < 0 || (*s)[i])
			i++;
	}
}
