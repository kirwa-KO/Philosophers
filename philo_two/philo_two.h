/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 12:13:37 by ibaali            #+#    #+#             */
/*   Updated: 2021/06/03 07:13:40 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdint.h>
# include <semaphore.h>
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
# define PHILO_DONE_EAT 5

typedef struct s_philos_args
{
	int						nb_of_philos;
	long long				time_to_die;
	long long				time_to_eat;
	long long				time_to_sleep;
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
	uint64_t				last_eat;
	int						nb_eat;
	pthread_t				life;
}					t_single_philo_info;

typedef struct s_all_philos_info
{
	t_philos_args			*args;
	t_philos_sem			*sem;
	int						some_one_died;
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
int							create_threads(t_philos_args *args,
								t_philos_sem *sem);
void						free_all_and_exit(t_all_philos_info *all_philos);
void						lock_forks_and_eat_sems(t_single_philo_info *philo,
								t_selected_philo *selected_philo,
								t_all_philos_info *all_philos);
void						unlock_forks_and_eat_sems(
								t_single_philo_info *philo,
								t_all_philos_info *all_philos);
// void						*must_eat_control(void *param);
#endif
