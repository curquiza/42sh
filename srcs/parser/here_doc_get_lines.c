/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_get_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 19:03:23 by curquiza          #+#    #+#             */
/*   Updated: 2017/11/03 12:37:45 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_manage_bslash_in_hdoc :
** Gestion du bslash (dans le cas "non-quoté", cf shell grammar).
** Renvoie -1 si un Ctrl C ou un Ctrl D a été capté, 0 sinon.
*/

static int	ft_manage_bslash_in_hdoc(char **line, char **word)
{
	char	*buff;
	char	*tmp;

	ft_rm_bslash_newline(line);
	buff = ft_strdup(*line);
	ft_read_line(line, ft_strlen(BSLASH_PROMPT));
	if (ft_check_ctrl_c(line, g_shell) == 1)
	{
		ft_strdel(&buff);
		free(*word);
		return (-1);
	}
	if (ft_check_and_restore_ctrld(g_shell) == 1)
	{
		ft_putendl3_fd(g_shell->name, ": ", UNEXP_CTRLD_MSG, 2);
		ft_strdel(&buff);
		free(*word);
		free(*line);
		return (-1);
	}
	tmp = *line;
	*line = ft_strjoin(buff, tmp);
	free(buff);
	free(tmp);
	return (0);
}

/*
** ft_manage_hdoc_line :
** Gestion de la boucle h_doc.
** Renvoie 1 si nécessite un break de la boucle, -1 si Ctrl D (dans
** ft_manage_bslash_in_hdoc) ou si Ctrl C a été capté, 0 si ok.
*/

static int	ft_manage_hdoc_line(t_lexeme *lex, int quoted, char **line,
								char **word)
{
	char	*tmp;

	if (ft_check_ctrl_c(line, g_shell) == 1)
	{
		free(*word);
		return (-1);
	}
	if (ft_check_and_restore_ctrld(g_shell) == 1 || !*line)
		return (1);
	while (!quoted && ft_strlen(*line) > 1
			&& (*line)[ft_strlen(*line) - 2] == 92)
	{
		g_shell->inhib = 1;
		ft_putstr(BSLASH_PROMPT);
		if (ft_manage_bslash_in_hdoc(line, word) == -1)
			return (-1);
		g_shell->inhib = 0;
	}
	if (ft_strcmp(*line, *word) == 0)
		return (1);
	tmp = lex->hdoc;
	lex->hdoc = ft_strjoin(tmp, *line);
	free(tmp);
	return (0);
}

/*
** ft_get_hdoc_lines :
** Récupère les arguments du hdoc en fonction du delimiteur (quoté ou non)
** Cf shell grammar.
*/

int			ft_get_hdoc_lines(t_lexeme *lex, int quoted)
{
	char	*line;
	int		ret;
	char	*word;

	word = ft_strjoin(lex->next->s, "\n");
	line = NULL;
	while (1)
	{
		g_shell->inhib = 1;
		ft_putstr(HDOC_PROMPT);
		ft_read_line(&line, ft_strlen(HDOC_PROMPT));
		g_shell->inhib = 0;
		if ((ret = ft_manage_hdoc_line(lex, quoted, &line, &word)) == -1)
			return (-1);
		else if (ret == 1)
			break ;
	}
	free(line);
	free(word);
	return (0);
}
