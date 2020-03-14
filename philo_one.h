/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali1 <ibaali1@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 11:09:11 by ibaali1           #+#    #+#             */
/*   Updated: 2020/03/14 13:15:48 by ibaali1          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# define THINKING 0
# define EATING 1
# define SLEEPING 2
# define FORK 3
# define DIE 4
# define MIN(x, y) ((x) > (y) ? (y) : (x))
# define MAX(x, y) ((x) < (y) ? (y) : (x))

typedef	struct		s_philo
{
	uint64_t	number_of_philosophers;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	tim_to_sleep;
	uint64_t	number_of_times_each_philosopher_must_eat;
	uint64_t	last_eat;
	int			left_fork;
	int			right_fork;
	int			nb_eat;
	int			nb_philo;
	int			state;
}					t_philo;

t_philo				*g_philo_one;
uint64_t			g_time;
pthread_t			*g_thread_id;
pthread_t			*g_die_thread_id;
pthread_mutex_t		*g_forks;
pthread_mutex_t		*g_message;

void		msg_print(int nb_philo, int state);
uint64_t	get_time_in_milisecond(void);
void		ft_strcat(char *dst, const char *src);
void		ft_putstr_fd(char *s, int fd);
int			ft_strlen(const char *s);
char		*ft_itoa(uint64_t n);
int			ft_atoi(const char *str);
void		*philosophere(void *parametre);
void		*die(void *parametre);

#endif
