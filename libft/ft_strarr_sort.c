/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:39:41 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/19 17:10:20 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strarr_sort(char **arr, int size)
{
	int		i;
	int		j;
	char	*tmp1;
	char	*tmp2;
	
	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				tmp1 = ft_strdup(arr[i]);
				tmp2 = ft_strdup(arr[j]);
				free (arr[i]);
				free (arr[j]);
				arr[i] = tmp2;
				arr[j] = tmp1;
			}
			j++;
		}
		i++;
	}
}