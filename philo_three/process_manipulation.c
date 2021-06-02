/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manipulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 14:31:39 by ibaali            #+#    #+#             */
/*   Updated: 2021/06/02 11:43:01 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_theree.h"

void	*die(void *param)
{
	t_selected_philo	selected_philo;
	uint64_t			time;
	t_single_philo_info	*philo;
	t_all_philos_info	*all_philos;

	selected_philo = *((t_selected_philo *)param);
	free(param);
	all_philos = selected_philo.philos;
	philo = &(selected_philo.philos->philosopers[selected_philo.id_of_philo]);
	philo->id = selected_philo.id_of_philo;
	while (1)
	{
		sem_wait(all_philos->sem->eat_sem[philo->id]);
		time = get_time_in_milisecond();
		if ((time - philo->last_eat) > all_philos->args->time_to_die)
			msg_print(&selected_philo, DIE);
		if (all_philos->args->nb_must_eat != -1)
			if (philo->nb_eat >= all_philos->args->nb_must_eat)
				exit(EXIT_BY_FINISH_NB_EAT);
		sem_post(all_philos->sem->eat_sem[philo->id]);
	}
	return (NULL);
}

void	*eat_sleep_think_for_a_philo(void *param)
{
	t_selected_philo	selected_philo;
	t_single_philo_info	*philo;
	t_all_philos_info	*all_philos;

	selected_philo = *((t_selected_philo *)param);
	all_philos = selected_philo.philos;
	philo = &(selected_philo.philos->philosopers[selected_philo.id_of_philo]);
	philo->id = selected_philo.id_of_philo;
	if (pthread_create(&(philo->die), NULL, die, param))
		return (NULL);
	sem_wait(all_philos->sem->door);
	while (1)
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

int	wait_child_process(t_all_philos_info *all_philos)
{
	int		philos_done_eating;
	int		status;
	int		i;
	int		j;

	i = -1;
	philos_done_eating = 0;
	while (++i < all_philos->args->nb_of_philos)
	{
		if (waitpid(-1, &status, 0) == -1)
			return (-1);
		if (WEXITSTATUS(status) == EXIT_BY_PHILO_DIE)
		{
			j = -1;
			while (++j < all_philos->args->nb_of_philos)
				kill(all_philos->philosopers[j].pid, SIGINT);
		}
		if (WEXITSTATUS(status) == EXIT_BY_FINISH_NB_EAT)
		{
			philos_done_eating += 1;
			if (philos_done_eating == all_philos->args->nb_of_philos)
				free_all_and_exit(all_philos);
		}
	}
	return (0);
}

/*
 ** initialize the philosophers variabels and run it
*/
static int	initialize_the_process_and_run_it(t_all_philos_info *philos)
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
		philos->philosopers[i].pid = fork();
		if ((philos->philosopers[i].pid) == -1)
			return (-1);
		else if (philos->philosopers[i].pid == 0)
			eat_sleep_think_for_a_philo(selected_philo);
	}
	return (0);
}

int	create_process(t_philos_args *args, t_philos_sem *sem)
{
	t_all_philos_info	*philos;

	philos = (t_all_philos_info *)malloc(sizeof(t_all_philos_info));
	if (!philos)
		return (-1);
	philos->philosopers = (t_single_philo_info *)malloc(
			sizeof(t_single_philo_info) * args->nb_of_philos);
	if (!(philos->philosopers))
		return (-1);
	philos->args = args;
	philos->sem = sem;
	initialize_the_process_and_run_it(philos);
	return (wait_child_process(philos));
}
