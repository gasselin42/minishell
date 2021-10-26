/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:45:44 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/25 11:02:07 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strarr_dup(char **arr, int size_plus)
{
	char	**dup;
	int i;

	i = 0;
	if (arr)
		while (arr[i])
			i++;
	dup = (char **)malloc(sizeof(char *) * (i + 1 + size_plus));
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
	dup[i] = NULL;
	return (dup);
}