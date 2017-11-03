/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 14:01:26 by sfranc            #+#    #+#             */
/*   Updated: 2017/11/03 14:05:52 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_fill_history_from_file(t_shell *shell)
{
	char	*histo_file;

	if ((histo_file = ft_get_varvalue(shell->var_priv, "42SH_HISTO_FILE")))
		ft_histo_file_read(shell->histo_ctrl, histo_file);
}
