/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:18:40 by kotatabe          #+#    #+#             */
/*   Updated: 2021/06/30 16:18:40 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int	built_pwd(void)
{
	if (!g_data.pwd)
		return (EXIT_FAILURE);
	ft_putendl_fd(g_data.pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
