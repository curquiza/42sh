/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_return.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:50:45 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:50:46 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_get_cmdret(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGSEGV)
			ft_putendl_fd("Segmentation Fault", 2);
		else if (WTERMSIG(status) == SIGABRT)
			ft_putendl_fd("Abort", 2);
		else if (WTERMSIG(status) == SIGBUS)
			ft_putendl_fd("Bus Error", 2);
	}
	return (CMD_FAILURE);
}

void	ft_fill_cmd_return(int ret, t_shell *shell)
{
	char	*ret_char;

	ret_char = ft_itoa(ret);
	ft_chg_varval_or_add(&shell->var_priv, "?", ret_char);
	ft_strdel(&ret_char);
}
