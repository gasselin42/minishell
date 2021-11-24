/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_triple.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 10:31:49 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/24 17:03:41 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_triple(const char *s1, const char *s2, const char *s3)
{
	size_t	size;
	char	*str;
	int		i;
	int		j;

	if (s1 && s2 && s3)
	{
		size = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
		str = (char *)ft_calloc((size + 1), sizeof(char));
		if (!str)
			return (NULL);
		j = 0;
		i = 0;
		while (s1[i])
			str[j++] = s1[i++];
		i = 0;
		while (s2[i])
			str[j++] = s2[i++];
		i = 0;
		while (s3[i])
			str[j++] = s3[i++];
		return (str);
	}
	return (NULL);
}
