/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 11:09:11 by ibaali1           #+#    #+#             */
/*   Updated: 2020/03/19 21:25:42 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdbool.h>
# define THINKING 0
# define EATING 1
# define SLEEPING 2
# define FORK 3
# define DIE 4
# define MIN(x, y) ((x) > (y) ? (y) : (x))
# define MAX(x, y) ((x) < (y) ? (y) : (x))

typedef		struct	s_philo_args
{
	int			nb_of_philo;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	uint64_t	nb_must_eat;
}					t_philo_args;

typedef		struct	s_philo_mutex
{
	pthread_mutex_t		*forks_mutex;
	pthread_mutex_t		*eat_mutex;
	pthread_mutex_t		print_mutex;
}					t_philo_mutex;

typedef		struct	s_philo_one
{
	t_philo_args	*args;
	t_philo_mutex	*mutex;
	uint64_t		last_eat;
	int				left_fork;
	int				right_fork;
	int				nb_eat;
	int				nb_philo;
	pthread_t		life;
	pthread_t		die;
}					t_philo_one;

uint64_t	g_time;

int		create_threads(t_philo_args *args, t_philo_mutex *mutex);
void		msg_print(t_philo_one *philo, int state);
uint64_t	get_time_in_milisecond(void);
void		ft_strcat(char *dst, const char *src);
void		ft_putstr_fd2(char *s, int fd);
int			ft_strlen1(const char *s);
char		*ft_itoa2(uint64_t n);
int			ft_atoi2(const char *str);

#endif
