/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 21:14:04 by sehattor          #+#    #+#             */
/*   Updated: 2021/07/03 20:40:26 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;

	s_len = 0;
	while (s[s_len])
		s_len++;
	if (start > s_len)
	{
		sub = (char *)malloc(sizeof(char));
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	sub = (char *)malloc(len * sizeof(char) + 1);
	if (!sub)
		return (NULL);
	sub[len] = '\0';
	while (len--)
		sub[len] = s[start + len];
	return (sub);
}
