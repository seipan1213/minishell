/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:03:15 by kotatabe          #+#    #+#             */
/*   Updated: 2021/06/30 16:03:16 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	exec_builtin(char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (built_echo(args));
	if (ft_strcmp(args[0], "cd") == 0)
		return (built_cd(args));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (built_pwd());
	if (ft_strcmp(args[0], "export") == 0)
		return (built_export(args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (built_unset(args));
	if (ft_strcmp(args[0], "env") == 0)
		return (built_env());
	if (ft_strcmp(args[0], "exit") == 0)
		return (built_exit(args));
	return (EXIT_FAILURE);
}
