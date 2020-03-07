/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 21:41:25 by ibaali            #+#    #+#             */
/*   Updated: 2020/03/08 00:12:21 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int					*state;
int					i;
pthread_t			*thread_id;
pthread_t			*die_philo;
pthread_mutex_t		*forks;
pthread_mutex_t		message;
t_info  			argument_data;
t_philo_data  		*philo_data;


t_info  fill_philo_argument_data(t_info argument_data, char **argv, int argc)
{
	argument_data.number_of_philosophers = ft_atoi(argv[1]);
	argument_data.time_to_die = ft_atoi(argv[2]);
	argument_data.time_to_eat = ft_atoi(argv[3]);
	argument_data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		argument_data.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	return (argument_data);
}



void	*eating(int *n)
{
	while(1)
	{
		msg_print(*n, THINKING, message);

		pthread_mutex_lock(&(forks[*n]));
		msg_print(*n, FORK, message);
		pthread_mutex_lock(&forks[((*n) + 1) % argument_data.number_of_philosophers]);
		state[*n] = EATING;
		msg_print(*n, FORK, message);
		msg_print(*n, EATING, message);
		philo_data[*n].time = get_time_in_milisecond();
        philo_data[*n].nb_eat += 1;
		usleep(argument_data.time_to_eat);
		pthread_mutex_unlock(&forks[*n]);
		pthread_mutex_unlock(&forks[((*n) + 1) % argument_data.number_of_philosophers]);

		state[*n] = SLEEPING;
		msg_print(*n, SLEEPING, message);
		usleep(argument_data.time_to_sleep);
		state[*n] = THINKING;
	}
	return (NULL);
}

// void	*die(int *nb_philo)
// {
// 	while (1)
// 	{
// 		if (state[*nb_philo] != EATING &&
// 		(uint64_t)(philo_data[*nb_philo].time + argument_data.time_to_die) < get_time_in_milisecond())
// 		{
// 			msg_print(*nb_philo, DIE, message);
// 			exit(1);
// 		}
// 	}
// 	return (NULL);
// }

int     main(int argc, char **argv)
{
	if (argc != 6 && argc != 5)
		return (-1);
	argument_data = fill_philo_argument_data(argument_data, argv, argc);
	state = (int*)malloc(argument_data.number_of_philosophers * sizeof(int));
	thread_id = (pthread_t*)malloc(argument_data.number_of_philosophers * sizeof(pthread_t));
	die_philo = (pthread_t*)malloc(argument_data.number_of_philosophers * sizeof(pthread_t));
	forks = (pthread_mutex_t*)malloc(argument_data.number_of_philosophers * sizeof(pthread_mutex_t));
	philo_data = (t_philo_data*)malloc(argument_data.number_of_philosophers * sizeof(t_philo_data));
	i = 0;
	while (i < argument_data.number_of_philosophers)
	{
		philo_data[i].nb_eat = 0;
		philo_data[i].time = 0;
		state[i++] = THINKING;
	}

	i = 0;
	while (i < argument_data.number_of_philosophers)
		if (pthread_mutex_init(&forks[i++], NULL) != 0)
			return (-1);

	int tab[argument_data.number_of_philosophers];
	
	pthread_mutex_init(&message, NULL);
	
	i = 0;
	while (i < argument_data.number_of_philosophers)
	{
		tab[i] = i;
		if (pthread_create(&thread_id[i], NULL, (void*)eating, &tab[i]) != 0)
			return (-1);
		// usleep(100);
		i++;
	}
	
	// i = 0;
	// while (i < argument_data.number_of_philosophers)
	// {
	// 	tab[i] = i;
	// 	if (pthread_create(&die_philo[i], NULL, (void*)die, &tab[i]) != 0)
	// 		return (-1);
	// 	// pthread_detach(die_philo[i]);
	// 	i++;
	// }
	
	i = 0;
	while (i < argument_data.number_of_philosophers)
		if (pthread_join(thread_id[i++], NULL) != 0)
			return (-1);

	// i = 0;
	// while (i < argument_data.number_of_philosophers)
	// 	if (pthread_join(die_philo[i++], NULL) != 0)
	// 		return (-1);
	i = 0;
	while (i < argument_data.number_of_philosophers)
		pthread_mutex_destroy(&forks[i++]);
	pthread_mutex_destroy(&message);
	return (0);
}
