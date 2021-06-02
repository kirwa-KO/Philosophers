/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 10:40:07 by ibaali            #+#    #+#             */
/*   Updated: 2021/06/02 19:35:58 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

/*
 ** function used to make the philo take both forks
 ** and start eating after that sleep and finally
 ** make the philo thinking
 ** this function sleep 2 times
 ** first for sleep time to eat
 ** and second in time to sleep
*/

void	*eat_sleep_think_for_a_philo(void *param)
{
	t_selected_philo	selected_philo;
	t_single_philo_info	*philo;
	t_all_philos_info	*all_philos;

	selected_philo = *((t_selected_philo *)param);
	free(param);
	all_philos = selected_philo.philos;
	philo = &(selected_philo.philos->philosopers[selected_philo.id_of_philo]);
	philo->id = selected_philo.id_of_philo;
	sem_wait(all_philos->sem->door);
	while (!(all_philos->some_one_died) && (philo->nb_eat < all_philos->args->nb_must_eat || !(all_philos->args->nb_must_eat)))
	{
		lock_forks_and_eat_sems(philo, &selected_philo, all_philos);
		philo->nb_eat += 1;
		philo->last_eat = get_time_in_milisecond();
		ft_sleep(all_philos->args->time_to_eat);
		msg_print(&selected_philo, SLEEPING);
		unlock_forks_and_eat_sems(philo, all_philos);
		ft_sleep(all_philos->args->time_to_sleep);
		msg_print(&selected_philo, THINKING);
	}
	return (NULL);
}

/*
 ** die function responsible for stop simulation if a philo die
 ** get every philo and get her last eat time and compare it with
 ** the current time and check is great than time to die
 ** if it is great it free all allocated memory
 ** and make exit
 ** make the free and exit when call msg_print functino with DIE key
*/
static int	die(t_all_philos_info *philos)
{
	t_single_philo_info		*philo;
	t_selected_philo		selected_philo;
	uint64_t				time;
	int						i;

	while (1)
	{
		i = -1;
		while (++i < philos->args->nb_of_philos)
		{
			philo = &(philos->philosopers[i]);
			selected_philo.id_of_philo = philo->id;
			selected_philo.philos = philos;
			sem_wait(philos->sem->eat_sem[philo->id]);
			if (philos->philosopers[i].nb_eat >= philos->args->nb_must_eat && philos->args->nb_must_eat != 0)
				return (PHILO_DONE_EAT);

				
			time = get_time_in_milisecond();
			if ((time - philo->last_eat) > philos->args->time_to_die)
				msg_print(&selected_philo, DIE);
			sem_post(philos->sem->eat_sem[philo->id]);
		}
	}
}

/*
 ** initialize the philosophers variabels and run it
*/

static int	initialize_the_thread_and_run_it(t_all_philos_info *philos)
{
	t_selected_philo	*selected_philo;
	int					i;

	i = -1;
	while (++i < philos->args->nb_of_philos)
	{
		philos->philosopers[i].id = i;
		philos->philosopers[i].last_eat = get_time_in_milisecond();
		philos->philosopers[i].nb_eat = 0;
		selected_philo = (t_selected_philo *)malloc(sizeof(t_selected_philo));
		selected_philo->id_of_philo = i;
		selected_philo->philos = philos;
		if (pthread_create(&(philos->philosopers[i].life), NULL,
				eat_sleep_think_for_a_philo, selected_philo))
			return (-1);
	}
	return (0);
}

/*
 ** create the philosophers threads
 ** and check stop simulation
 ** with the die function and philos->must_eat thread
*/
int	create_threads(t_philos_args *args, t_philos_sem *sem)
{
	t_all_philos_info		*philos;
	int						i;

	philos = (t_all_philos_info *)malloc(
			sizeof(t_all_philos_info) * args->nb_of_philos);
	if (!philos)
		return (-1);
	philos->philosopers = (t_single_philo_info *)malloc(
			sizeof(t_single_philo_info) * args->nb_of_philos);
	if (!(philos->philosopers))
		return (-1);
	philos->args = args;
	philos->sem = sem;
	philos->some_one_died = 0;
	// if (philos->args->nb_must_eat != -1)
	// 	if (pthread_create(&(philos->must_eat), NULL, must_eat_control, philos))
	// 		return (-1);
	initialize_the_thread_and_run_it(philos);
	if (die(philos) == PHILO_DONE_EAT)
	{
		i = -1;
		while (++i < philos->args->nb_of_philos)
			pthread_join(philos->philosopers[i].life, NULL);
		free_all_and_exit(philos);
	}
	return (0);
}
