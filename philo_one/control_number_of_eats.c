/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_number_of_eats.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 09:44:37 by ibaali            #+#    #+#             */
/*   Updated: 2021/06/02 09:20:39 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
 ** check if all philos eat number of eat based of table that
 ** must_eat_controlfunction give it
*/
static	void	check_eaten_philos(t_all_philos_info *philos, int *done_eating)
{
	int		i;
	int		stop_simulation;

	i = -1;
	stop_simulation = 0;
	while (++i < philos->args->nb_of_philos)
		stop_simulation += done_eating[i];
	if (stop_simulation == philos->args->nb_of_philos)
	{
		free(done_eating);
		free_all_and_exit(philos);
	}
}

/*
 ** must_eat_control function responsible for stop simulation if a philos
 ** eat number of must eat
 ** it lock the eat mutex to dont kill philo when eating
*/
void	*must_eat_control(void *param)
{
	t_all_philos_info		*philos;
	int						*done_eating;
	int						i;

	philos = (t_all_philos_info *)param;
	done_eating = (int *)malloc(sizeof(int) * philos->args->nb_of_philos);
	if (!done_eating)
		return (NULL);
	i = -1;
	while (++i < philos->args->nb_of_philos)
		done_eating[i] = 0;
	while (1)
	{
		i = -1;
		while (++i < philos->args->nb_of_philos)
		{
			pthread_mutex_lock(&(philos->mutex->eat_mutex[i]));
			if (philos->philosopers[i].nb_eat >= philos->args->nb_must_eat)
				done_eating[i] = 1;
			pthread_mutex_unlock(&(philos->mutex->eat_mutex[i]));
		}
		check_eaten_philos(philos, done_eating);
	}
	return (NULL);
}
