/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:45:44 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/25 11:26:42 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strarr_dup(char **arr, int size_plus)
{
	char	**dup;
	int		i;

	i = 0;
	if (arr)
		while (arr[i])
			i++;
	dup = (char **)ft_calloc((i + 1 + size_plus), sizeof(char *));
	if (!dup)
		return (NULL);
	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			dup[i] = ft_strdup(arr[i]);
			i++;
		}
	}
	return (dup);
}
