/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:11:11 by kotatabe          #+#    #+#             */
/*   Updated: 2021/06/30 16:11:11 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

static void	swap_str(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	sort_str(char **envs)
{
	int	i;
	int	j;

	i = 0;
	while (envs[i])
	{
		j = i;
		while (envs[j])
		{
			if (ft_strcmp(envs[i], envs[j]) > 0)
				swap_str(&envs[i], &envs[j]);
			j++;
		}
		i++;
	}
}

void	sort_envs(t_env *envs)
{
	t_env	*top;
	t_env	*back;

	top = envs;
	while (top)
	{
		back = top->next;
		while (back)
		{
			if (ft_strcmp(top->name, back->name) > 0)
			{
				swap_str(&top->name, &back->name);
				swap_str(&top->value, &back->value);
			}
			back = back->next;
		}
		top = top->next;
	}
	return ;
}
