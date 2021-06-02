/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_unlock_semaphors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 12:25:09 by ibaali            #+#    #+#             */
/*   Updated: 2021/06/01 17:08:34 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_theree.h"

/*
 ** function used to lock the right & left forks of a philo
 ** and also lock the eat semaphor to dont kill the philo when eating
 ** and also unlock the door semaphor that locked before enter the infinite loop
*/
void	lock_forks_and_eat_sems(t_single_philo_info *philo, t_selected_philo *selected_philo, t_all_philos_info *all_philos)
{
		sem_wait(all_philos->sem->forks_sem);
		msg_print(selected_philo, FORK);
		sem_wait(all_philos->sem->forks_sem);
		msg_print(selected_philo, FORK);
		sem_post(all_philos->sem->door);
		sem_wait(all_philos->sem->eat_sem[philo->id]);
		msg_print(selected_philo, EATING);
}

/*
 ** function used to unlock the right & left forks of a philo
 ** and also unlock the eat semaphors to dont kill the philo when eating
*/
void	unlock_forks_and_eat_sems(t_single_philo_info *philo, t_all_philos_info *all_philos)
{	
		sem_post(all_philos->sem->eat_sem[philo->id]);
		sem_post(all_philos->sem->forks_sem);
		sem_post(all_philos->sem->forks_sem);
}
