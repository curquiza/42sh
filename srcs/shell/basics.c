/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:04:37 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/24 18:04:37 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_is_separator :
** Check si le char est un séparateur de token.
*/

int		ft_is_separator(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

/*
** ft_next_squote :
** Renvoie l'index de la chaine de char *s qui contient la prochaine simple
** quote ou l'index de la fin de la chaine ('\0') s'il n'y en a pas.
*/

int		ft_next_squote(int i, char *s)
{
	i++;
	while (s[i] && s[i] != 39)
		i++;
	return (i);
}

/*
** ft_next_dquote :
** Renvoie l'index de la chaine de char *s qui contient la prochaine double
** quote ou l'index de la fin de la chaine ('\0') s'il n'y en a pas.
*/

int		ft_next_dquote(int i, char *s)
{
	i++;
	while (s[i] && s[i] != 34)
	{
		if (s[i] == 92 && s[i + 1])
			i = i + 2;
		else
			i++;
	}
	return (i);
}

/*
** ft_is_uns_nbr :
** Renvoie 1 si la chaine de caractères est un nombre positive, 0 sinon.
*/

int		ft_is_uns_nbr(char *s)
{
	if (s)
	{
		while (*s)
		{
			if (ft_isdigit(*s) == 0)
				return (0);
			s++;
		}
		return (1);
	}
	return (0);
}

/*
** ft_tab_to_str :
** prends un tableau et le tranforme en une chaine, charque argument du tableau
** est séparé par un espace.
*/

char	*ft_tab_to_str(char **array)
{
	char	*str;
	char	*tmp;
	int		i;

	if (!array || !array[0])
		return (NULL);
	str = ft_strdup(array[0]);
	i = 1;
	while (array[i])
	{
		tmp = str;
		str = ft_strjoin3(str, " ", array[i]);
		free(tmp);
		++i;
	}
	return (str);
}
