/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 11:09:11 by ibaali1           #+#    #+#             */
/*   Updated: 2020/03/20 18:18:41 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef philo_two_H
# define philo_two_H
# include <unistd.h>
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <semaphore.h>
# include <pthread.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdbool.h>
# include "libft.h"
# define THINKING 0
# define EATING 1
# define SLEEPING 2
# define FORK 3
# define DIE 4
# define SEM_PRINT_NAME "print semaphores"
# define SEM_FORK_NAME "forks semaphores"
# define SEM_EAT_NAME "sem eat number "
# define MIN(x, y) ((x) > (y) ? (y) : (x))
# define MAX(x, y) ((x) < (y) ? (y) : (x))

typedef		struct	s_philo_args
{
	int			nb_of_philo;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	int			nb_must_eat;
}					t_philo_args;

typedef		struct	s_philo_sem
{
	sem_t		*forks_sem;
	sem_t		**eat_sem;
	sem_t		*print_sem;
}					t_philo_sem;

typedef		struct	s_philo_there
{
	t_philo_args	*args;
	t_philo_sem		*sem;
	uint64_t		last_eat;
	int				nb_eat;
	int				nb_philo;
	pid_t			pid;
	pthread_t		die;
}					t_philo_three;

uint64_t	g_time;

int			create_process(t_philo_args *args, t_philo_sem *sem);
void		msg_print(t_philo_three *philo, int state);
uint64_t	get_time_in_milisecond(void);
void		ft_strcat(char *dst, const char *src);
void		ft_putstr_fd2(char *s, int fd);
int			ft_strlen1(const char *s);
char		*ft_itoa2(uint64_t n);
int			ft_atoi2(const char *str);
void		free_all_and_exit(t_philo_three *philo);

#endif
