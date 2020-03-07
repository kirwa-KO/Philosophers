/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:36:05 by ibaali            #+#    #+#             */
/*   Updated: 2020/03/07 18:48:55 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int		nb_size(uint64_t n, uint64_t *nb_ten)
{
	int		size;

	size = 1;
	while ((n / *nb_ten) > 9)
	{
		*nb_ten *= 10;
		size++;
	}
	return (size);
}

char			*ft_itoa(uint64_t n)
{
	char		*str;
	int			i;
	uint64_t	nb_ten;
	int			size;

	i = 0;
	nb_ten = 1;
	size = nb_size(n, &nb_ten);
	str = (char*)malloc(size + 1);
	if (str == NULL)
		return (NULL);
	while (nb_ten != 0)
	{
		str[i++] = (n / nb_ten) + '0';
		n -= (n / nb_ten) * nb_ten;
		nb_ten /= 10;
	}
	str[i] = '\0';
	return (str);
}
