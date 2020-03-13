/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali1 <ibaali1@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:51:58 by ibaali            #+#    #+#             */
/*   Updated: 2020/03/13 16:32:20 by ibaali1          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

pthread_t		*philo;
pthread_mutex_t	*forks;

typedef		struct	s_philo_one
{
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_times_each_philosopher_must_eat;
	int		nb_philo;
}					t_philo_one;

void	init_data(t_philo_one *this, int argc, char **argv)
{
	this->number_of_philosophers = ft_atoi(argv[1]);
	this->time_to_die = ft_atoi(argv[2]);
	this->time_to_eat = ft_atoi(argv[3]);
	this->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		this->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
}

int     main(int argc, char **argv)
{
	int				i;
	t_philo_one		*ph;

	if (argc != 6 && argc != 5)
		return (-1);
	ph = (t_philo_one*)malloc(ft_atoi(argv[1]) * sizeof(t_philo_one));
	init_data(ph, argc, argv);
	printf("%d\n", ph[0].number_of_philosophers);
	printf("%d\n", ph[0].time_to_die);
	printf("%d\n", ph[0].time_to_eat);
	printf("%d\n", ph[0].time_to_sleep);
}
