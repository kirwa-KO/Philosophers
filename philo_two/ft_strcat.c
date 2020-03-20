/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 21:43:28 by ibaali            #+#    #+#             */
/*   Updated: 2020/03/20 11:45:32 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
