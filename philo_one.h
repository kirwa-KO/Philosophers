/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:53:20 by ibaali            #+#    #+#             */
/*   Updated: 2020/03/07 22:24:51 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
#define PHILO_ONE_H
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

typedef     struct s_info
{
    int     number_of_philosophers;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     number_of_times_each_philosopher_must_eat;
}                   t_info;

typedef     struct s_philo_data
{
    uint64_t    time;
    int         nb_eat;
}                   t_philo_data;

int		ft_atoi(const char *str);
char	*ft_itoa(uint64_t n);
void	ft_strcat(char *dst, const char *src);
void	ft_putstr_fd(char *s, int fd);
void    msg_print(int nb_philo, int state, pthread_mutex_t message);
uint64_t    get_time_in_milisecond(void);

#endif
