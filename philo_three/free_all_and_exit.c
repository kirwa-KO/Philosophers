/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_and_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:02:01 by ibaali            #+#    #+#             */
/*   Updated: 2021/06/02 20:07:18 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_theree.h"

int	unlink_eat_semaphores(t_all_philos_info *philo)
{
	int		i;
	char	*str;
	char	*number;

	str = malloc(BUFFER_SIZE);
	if (!(str))
		return (-1);
	str[0] = 0;
	i = -1;
	while (++i < philo->args->nb_of_philos)
	{
		ft_strcat(str, SEM_EAT_NAME);
		number = ft_itoa((uint64_t)i);
		ft_strcat(str, number);
		// if (sem_unlink(str) && sem_close(philo->sem->eat_sem[i]))
		if (sem_unlink(str))
			return (-1);
		str[0] = 0;
		free(number);
	}
	free(str);
	return (0);
}

void	free_all_and_exit(t_all_philos_info *all_philos)
{
	// if (sem_unlink(SEM_FORK_NAME) && sem_close(all_philos->sem->forks_sem))
	if (sem_unlink(SEM_FORK_NAME))
		exit (-1);
	if (unlink_eat_semaphores(all_philos))
		exit (-1);
	// if (sem_unlink(SEM_PRINT_NAME) && sem_close(all_philos->sem->print_sem))
	if (sem_unlink(SEM_PRINT_NAME))
		exit (-1);
	// if (sem_unlink(SEM_DOOR_NAME) && sem_close(all_philos->sem->door))
	if (sem_unlink(SEM_DOOR_NAME))
		exit (-1);
	free(all_philos->sem->eat_sem);
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

	sem_wait(philos_and_selected_id->philos->sem->print_sem);
	put_str("\033[1;37m");
	buffer = ft_itoa(get_time_in_milisecond() - g_time);
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
		exit(EXIT_BY_PHILO_DIE);
	}
	else if (state == SLEEPING)
		put_str(" \033[1;32msleeping\033[0m\n");
	sem_post(philos_and_selected_id->philos->sem->print_sem);
}

uint64_t	get_time_in_milisecond(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
