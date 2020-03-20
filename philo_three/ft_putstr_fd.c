/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:15:59 by ibaali            #+#    #+#             */
/*   Updated: 2020/03/20 13:26:28 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	ft_strlen1(const char *s)
{
	unsigned int lenght;

	lenght = 0;
	while (s[lenght] != '\0')
		lenght++;
	return (lenght);
}

void	ft_putstr_fd2(char *s, int fd)
{
	if (s == NULL)
		return ;
	write(fd, s, ft_strlen1(s));
}
