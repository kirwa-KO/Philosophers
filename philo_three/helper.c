/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 12:20:18 by ibaali            #+#    #+#             */
/*   Updated: 2021/06/01 17:02:51 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_theree.h"

/*
 ** this file just contain libft functions that we use it in this project
*/

int		ft_strlen(char *s)
{
	unsigned int lenght;

	lenght = 0;
	while (s[lenght] != '\0')
		lenght++;
	return (lenght);
}

static	int		ft_sign(char c, int *i)
{
	if (c == '-')
	{
		*i += 1;
		return (-1);
	}
	if (c == '+')
	{
		*i += 1;
		return (1);
	}
	return (1);
}

int				ft_atoi(const char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' ||
			str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	sign = ft_sign(str[i], &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res >= 922337203685477580 && (str[i] - '0') >= 7)
		{
			if (str[i] - '0' >= 8 && sign == -1)
				return (0);
			return (-1);
		}
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (sign * (int)res);
}

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
