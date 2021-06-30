/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:15:39 by kotatabe          #+#    #+#             */
/*   Updated: 2021/06/30 16:15:39 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

static void	print_envs(t_env *envs)
{
	while (envs)
	{
		if (envs->value)
		{
			ft_putstr_fd(envs->name, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(envs->value, STDOUT_FILENO);
		}
		envs = envs->next;
	}
}

int	built_env(void)
{
	print_envs(g_data.envs);
	return (EXIT_SUCCESS);
}
