/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_and_sleep.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:00:23 by ibaali            #+#    #+#             */
/*   Updated: 2021/06/01 17:01:42 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_theree.h"

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

void	ft_sleep(uint64_t duration_in_mille_sec)
{
	uint64_t start;

	start = get_time_in_milisecond();
	usleep(duration_in_mille_sec * 1000 - 20000);
	while (get_time_in_milisecond() - start < duration_in_mille_sec);
}
