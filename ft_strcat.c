/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 21:43:28 by ibaali            #+#    #+#             */
/*   Updated: 2020/03/07 16:53:28 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		ft_strcat(char *dst, const char *src)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (dst == NULL)
		return ;
	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0')
		dst[i++] = src[j++];
	dst[i] = '\0';
}
