/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_and_print_msgs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 15:22:38 by ibaali            #+#    #+#             */
/*   Updated: 2021/06/02 09:23:01 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	free_all_and_exit(t_all_philos_info *all_philos)
{
	int		i;

	if (pthread_detach(all_philos->must_eat))
		exit(-1);
	i = -1;
	while (++i < all_philos->args->nb_of_philos)
		if (pthread_detach(all_philos->philosopers[i].life))
			exit (-1);
	i = -1;
	while (++i < all_philos->args->nb_of_philos)
		if (pthread_mutex_destroy(&(all_philos->mutex->forks_mutex[i])))
			exit (-1);
	i = -1;
	while (++i < all_philos->args->nb_of_philos)
		if (pthread_mutex_destroy(&(all_philos->mutex->eat_mutex[i])))
			exit (-1);
	if (pthread_mutex_destroy(&(all_philos->mutex->print_mutex)))
		exit (-1);
	free(all_philos->mutex->forks_mutex);
	free(all_philos->mutex->eat_mutex);
	free(all_philos->philosopers);
	free(all_philos);
	exit(0);
}

void	put_str(char *s)
{
	if (s == NULL)
		return ;
	write(1, s, ft_strlen(s));
}

void	msg_print(t_selected_philo *philos_and_selected_id, int state)
{
	char	*buffer;

	pthread_mutex_lock(&(philos_and_selected_id->philos->mutex->print_mutex));
	put_str("\033[1;37m");
	buffer = ft_itoa(get_time_in_milisecond());
	put_str(buffer);
	free(buffer);
	put_str(" \033[0m\033[1;32m");
	buffer = ft_itoa(philos_and_selected_id->id_of_philo + 1);
	put_str(buffer);
	free(buffer);
	if (state == THINKING)
		put_str(" \033[1;34mthinking\033[0m\n");
	else if (state == EATING)
		put_str(" \033[1;33meating\033[0m\n");
	else if (state == FORK)
		put_str(" \033[1;36mhas taken a fork\033[0m\n");
	else if (state == DIE)
	{
		put_str(" \033[1;31mdied\033[0m\n");
		free_all_and_exit(philos_and_selected_id->philos);
	}
	else if (state == SLEEPING)
		put_str(" \033[1;32msleeping\033[0m\n");
	pthread_mutex_unlock(&(philos_and_selected_id->philos->mutex->print_mutex));
}

uint64_t	get_time_in_milisecond(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_sleep(uint64_t duration_in_mille_sec)
{
	uint64_t	start;

	start = get_time_in_milisecond();
	usleep(duration_in_mille_sec * 1000 - 20000);
	while (get_time_in_milisecond() - start < duration_in_mille_sec)
	{
	}
}
