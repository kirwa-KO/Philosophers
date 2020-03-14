/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helped.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali1 <ibaali1@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 16:46:37 by ibaali            #+#    #+#             */
/*   Updated: 2020/03/14 13:06:47 by ibaali1          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

uint64_t	get_time_in_milisecond(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void		msg_print(int nb_philo, int state)
{
	char    buff[4096];
	char	*str;
	int		space;

	pthread_mutex_lock(g_message);
	str = ft_itoa(get_time_in_milisecond() - g_time);
	ft_strcat(buff, str);
	ft_strcat(buff, " ");
	space = 0;
	space = 10 - ft_strlen(str);
	while (space--)
		ft_strcat(buff, " ");
	ft_strcat(buff, ft_itoa(nb_philo + 1));
	ft_strcat(buff, " is ");
	if (state == THINKING)
		ft_strcat(buff, "thinking\n");
	else if (state == EATING)
		ft_strcat(buff, "eating\n");
	else if (state == FORK)
		ft_strcat(buff, "has taken a fork\n");
	else if (state == DIE)
		ft_strcat(buff, "died\n");
	else if (state == SLEEPING)
		ft_strcat(buff, "sleeping\n");
	ft_putstr_fd(buff, 1);
	pthread_mutex_unlock(g_message);
}
