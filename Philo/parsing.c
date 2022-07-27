/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:45:16 by aperis            #+#    #+#             */
/*   Updated: 2022/06/27 15:35:54 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *s)
{
	int			i;
	long int	nb;
	int			sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (s[i] == '\t' || s[i] == '\v' || s[i] == '\n'
		|| s[i] == '\r' || s[i] == '\f' || s[i] == ' ')
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		nb = nb * 10 + s[i] - 48;
		i++;
	}
	if (nb > 2147483647 || nb < -2147483648)
		return (-1);
	return (nb * sign);
}

int	check_ac(int ac)
{
	if (ac != 5 && ac != 6)
	{
		printf("Wrong number of arguments\n");
		return (0);
	}
	return (1);
}

int	check_arg(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (check_ac(ac) == 0)
		return (0);
	while (av[i])
	{
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j++] > '9')
			{
				printf("Wrong arguments\n");
				return (0);
			}
		}
		if (atoi(av[i++]) == -1)
		{
			printf("Wrong arguments\n");
			return (0);
		}
		j = 0;
	}
	return (1);
}

long long	get_time(t_param *param)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - param->start_time);
}

int	one_philo(char **av)
{
	if (atoi(av[1]) == 1)
	{
		printf("0 1 has taken a fork\n%d 1 died\n", atoi(av[2]));
		return (0);
	}
	return (1);
}
