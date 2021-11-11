/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_addback.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 11:55:47 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/11 14:23:24 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strarr_addback(char **arr, char *str)
{
	char	**dup;
	int		i;

	i = 0;
	if (arr)
		while (arr[i])
			i++;
	dup = ft_strarr_dup(arr, 1);
	dup[i++] = (char *)str;
	dup[i] = NULL;
	ft_strarr_free(arr);
	return (dup);
}
