/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histo_put_eventerr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:51:06 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/23 17:51:08 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_put_eventerror(char *name, char *event)
{
	ft_putendl_fd("", 2);
	if (name)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (event)
	{
		ft_putstr_fd("!", 2);
		ft_putstr_fd(event, 2);
	}
	ft_putendl_fd(": event not found", 2);
}
