/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helped.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 16:46:37 by ibaali            #+#    #+#             */
/*   Updated: 2020/03/19 21:43:01 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

uint64_t	get_time_in_milisecond(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

char	*put_data_before_state(char *buff, int nb_philo)
{
	int		space;
	char	*nbr;
	char	*str;

	str = ft_itoa2(get_time_in_milisecond() - g_time);
	ft_strcat(buff, str);
	ft_strcat(buff, " ");
	space = 0;
	space = 10 - ft_strlen1(str);
	while (space-- > 0)
		ft_strcat(buff, " ");
	nbr = ft_itoa2(nb_philo);
	ft_strcat(buff, nbr);
	free(nbr);
	ft_strcat(buff, " is ");
	free(str);
	return (buff);
}

void		free_all_and_exit(t_philo_one *philo)
{
	int		i;

	i = -1;
	while (++i < philo->args->nb_of_philo)
		if (pthread_detach(philo[i].die))
			exit(-1);
	i = -1;
	while (++i < philo->args->nb_of_philo)
		if (pthread_detach(philo[i].life))
			exit (-1);
	i = -1;
	while (++i < philo->args->nb_of_philo)
		if (pthread_mutex_destroy(&(philo->mutex->forks_mutex[i])))
			exit (-1);
	i = -1;
	while (++i < philo->args->nb_of_philo)
		if (pthread_mutex_destroy(&(philo->mutex->eat_mutex[i])))
			exit (-1);
	if (pthread_mutex_destroy(&(philo->mutex->print_mutex)))
		exit (-1);
	free(philo->mutex->forks_mutex);
	free(philo->mutex->eat_mutex);
	free(philo);
	exit(-1);
}

void		msg_print(t_philo_one *philo, int state)
{
	char    *buff;

	pthread_mutex_lock(&(philo->mutex->print_mutex));
	buff = malloc(4096);
	buff[0] = 0;
	put_data_before_state(buff, philo->nb_philo + 1);
	if (state == THINKING)
		ft_strcat(buff, "thinking\n");
	else if (state == EATING)
		ft_strcat(buff, "eating\n");
	else if (state == FORK)
		ft_strcat(buff, "has taken a fork\n");
	else if (state == DIE)
	{
		ft_strcat(buff, "died\n");
		ft_putstr_fd2(buff, 1);
		free_all_and_exit(philo);
	}
	else if (state == SLEEPING)
		ft_strcat(buff, "sleeping\n");
	ft_putstr_fd2(buff, 1);
	free(buff);
	pthread_mutex_unlock(&(philo->mutex->print_mutex));
}
