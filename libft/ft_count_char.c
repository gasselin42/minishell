/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 09:38:09 by gasselin          #+#    #+#             */
/*   Updated: 2021/07/19 15:15:49 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_char(const char *s, const char *set)
{
	int		count;
	int		i;
	int		j;

	count = 0;
	i = 0;
	if (!s || !set)
		return (0);
	while (s[i])
	{
		j = 0;
		while (set[j])
			if (s[i] == set[j++])
				count++;
		i++;
	}
	return (count);
}
