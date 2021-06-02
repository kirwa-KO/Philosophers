/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_unlock_mutexes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 09:42:21 by ibaali            #+#    #+#             */
/*   Updated: 2021/06/02 09:26:12 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
 ** function used to lock the right & left forks of a philo
 ** and also lock the eat mutex to dont kill the philo when eating
 ** and also unlock the door mutex that locked before enter the infinite loop
*/
void	lock_forks_and_eat_mutexs(t_single_philo_info *philo,
									t_selected_philo *selected_philo,
									t_all_philos_info *all_philos)
{
	pthread_mutex_lock(&(all_philos->mutex->forks_mutex[philo->left_fork]));
	msg_print(selected_philo, FORK);
	pthread_mutex_lock(&(all_philos->mutex->forks_mutex[philo->right_fork]));
	pthread_mutex_unlock(&(all_philos->mutex->door));
	msg_print(selected_philo, FORK);
	pthread_mutex_lock(&(all_philos->mutex->eat_mutex[philo->id]));
	msg_print(selected_philo, EATING);
}

/*
 ** function used to unlock the right & left forks of a philo
 ** and also unlock the eat mutex to dont kill the philo when eating
*/
void	unlock_forks_and_eat_mutexs(t_single_philo_info *philo,
									t_all_philos_info *all_philos)
{
	pthread_mutex_unlock(&(all_philos->mutex->eat_mutex[philo->id]));
	pthread_mutex_unlock(&(all_philos->mutex->forks_mutex[philo->right_fork]));
	pthread_mutex_unlock(&(all_philos->mutex->forks_mutex[philo->left_fork]));
}
