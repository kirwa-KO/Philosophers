/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helped.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 16:46:37 by ibaali            #+#    #+#             */
/*   Updated: 2020/03/22 15:07:31 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

int		unlink_eat_semaphores(t_philo_three *philo)
{
	int		i;
	char	*str;
	char	*number;

	if (!(str = malloc(4096)))
		return (-1);
	str[0] = 0;
	i = -1;
	while (++i < philo->args->nb_of_philo)
	{
		ft_strcat(str, SEM_EAT_NAME);
		number = ft_itoa2((uint64_t)i);
		ft_strcat(str, number);
		if ((sem_close(philo->sem->eat_sem[i])) && (sem_unlink(str)))
			return (-1);
		str[0] = 0;
		free(number);
	}
	free(str);
	return (0);
}

void		free_all_and_exit(t_philo_three *philo)
{
	if (sem_close(philo->sem->forks_sem) && sem_unlink(SEM_FORK_NAME))
		exit (write(1, "close semaphore Error..!\n", 25) * 0 - 1);
	if (unlink_eat_semaphores(philo))
		exit (write(1, "close semaphore Error..!\n", 25) * 0 - 1);
	if (sem_close(philo->sem->print_sem) && sem_unlink(SEM_FORK_NAME))
		exit (write(1, "close semaphore Error..!\n", 25) * 0 - 1);
	free(philo->sem->eat_sem);
	free(philo);
}

void		msg_print(t_philo_three *philo, int state)
{
	char    *buff;

	sem_wait(philo->sem->print_sem);
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
		wait_child_process(philo, 0);
	}
	else if (state == SLEEPING)
		ft_strcat(buff, "sleeping\n");
	ft_putstr_fd2(buff, 1);
	free(buff);
	sem_post(philo->sem->print_sem);
}
