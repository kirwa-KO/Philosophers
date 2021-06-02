/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 12:13:37 by ibaali            #+#    #+#             */
/*   Updated: 2021/06/02 09:34:09 by ibaali           ###   ########.fr       */
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
# define THINKING 0
# define EATING 1
# define SLEEPING 2
# define FORK 3
# define DIE 4

typedef struct s_philos_args
{
	int						nb_of_philos;
	uint64_t				time_to_die;
	uint64_t				time_to_eat;
	uint64_t				time_to_sleep;
	int						nb_must_eat;
}					t_philos_args;

typedef struct s_philos_mutex
{
	pthread_mutex_t			*forks_mutex;
	pthread_mutex_t			*eat_mutex;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			door;
}					t_philos_mutex;

typedef struct s_single_philo_info
{
	int						id;
	uint64_t				last_eat;
	int						left_fork;
	int						right_fork;
	int						nb_eat;
	pthread_t				life;
}					t_single_philo_info;

typedef struct s_all_philos_info
{
	t_philos_args			*args;
	t_philos_mutex			*mutex;
	pthread_t				must_eat;
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
void						msg_print(t_selected_philo *philos_and_selected_id,
								int state);
void						free_all_and_exit(t_all_philos_info *all_philos);
void						ft_sleep(uint64_t duration_in_mille_sec);
int							create_threads(t_philos_args *args,
								t_philos_mutex *mutex);
void						lock_forks_and_eat_mutexs(
								t_single_philo_info *philo,
								t_selected_philo *selected_philo,
								t_all_philos_info *all_philos);
void						unlock_forks_and_eat_mutexs(
								t_single_philo_info *philo,
								t_all_philos_info *all_philos);
void						*must_eat_control(void *param);

#endif
