/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali1 <ibaali1@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:53:20 by ibaali            #+#    #+#             */
/*   Updated: 2020/03/13 20:20:44 by ibaali1          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
#define PHILO_ONE_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef		struct	s_philo
{
	int			nb_eat;
	uint16_t	last_time_eat;
}					t_philo;

pthread_t			*philo_thread;
pthread_mutex_t		*forks;
pthread_mutex_t		*print_message;
uint16_t			time_to_eat;
uint16_t			time_to_sleep;
uint16_t			time_to_die;
int					number_of_philosophers;
int					number_of_times_each_philosopher_must_eat;
t_philo				*philo_data;

#endif
