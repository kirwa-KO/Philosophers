/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_theree.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 14:21:48 by ibaali            #+#    #+#             */
/*   Updated: 2021/06/02 20:06:57 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THEREE_H
# define PHILO_THEREE_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdint.h>
# include <semaphore.h>
# include <signal.h>
# define THINKING 0
# define EATING 1
# define SLEEPING 2
# define FORK 3
# define DIE 4
# define SEM_PRINT_NAME "print semaphores5"
# define SEM_FORK_NAME "forks semaphores5"
# define SEM_EAT_NAME "sem eat number5 "
# define SEM_DOOR_NAME "sem for door5"
# define BUFFER_SIZE 4096
# define EXIT_BY_PHILO_DIE 2
# define EXIT_BY_FINISH_NB_EAT 3

typedef struct s_philos_args
{
	int						nb_of_philos;
	uint64_t				time_to_die;
	uint64_t				time_to_eat;
	uint64_t				time_to_sleep;
	int						nb_must_eat;
}					t_philos_args;

typedef struct s_philos_sem
{
	sem_t					*forks_sem;
	sem_t					**eat_sem;
	sem_t					*print_sem;
	sem_t					*door;
}					t_philos_sem;

typedef struct s_single_philo_info
{
	int						id;
	pid_t					pid;
	uint64_t				last_eat;
	int						nb_eat;
	pthread_t				life;
}					t_single_philo_info;

typedef struct s_all_philos_info
{
	t_philos_args			*args;
	t_philos_sem			*sem;
	t_single_philo_info		*philosopers;
}					t_all_philos_info;

typedef struct s_selected_philo
{
	int						id_of_philo;
	t_all_philos_info		*philos;
}					t_selected_philo;

int							ft_strlen(char *s);
void						put_str(char *s);
int							ft_atoi(const char *str);
uint64_t					get_time_in_milisecond(void);
char						*ft_itoa(uint64_t n);
void						ft_sleep(uint64_t duration_in_mille_sec);
void						msg_print(t_selected_philo *philos_and_selected_id,
								int state);
void						ft_strcat(char *dst, const char *src);
void						free_all_and_exit(t_all_philos_info *all_philo);
int							create_process(t_philos_args *args,
								t_philos_sem *sem);
int							wait_child_process(t_all_philos_info *all_philos);
void						lock_forks_and_eat_sems(t_single_philo_info *philo,
								t_selected_philo *selected_philo,
								t_all_philos_info *all_philos);
void						unlock_forks_and_eat_sems(
								t_single_philo_info *philo,
								t_all_philos_info *all_philos);

uint64_t g_time;

#endif
