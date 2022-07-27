/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:33:44 by aperis            #+#    #+#             */
/*   Updated: 2022/06/27 14:34:50 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	finish_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->param->eat));
	if (philo->nb_eat >= philo->param->nb_pme && philo->param->nb_pme != -1
		&& philo->have_eat == 0)
	{
		philo->param->finish_eat++;
		philo->have_eat = 1;
	}
	pthread_mutex_unlock(&(philo->param->eat));
}

int	die(t_philo *philo)
{
	pthread_mutex_lock(&(philo->param->meal));
	if (get_time(philo->param) - philo->last_meal >= philo->param->ttd)
	{
		pthread_mutex_unlock(&(philo->param->meal));
		return (0);
	}
	pthread_mutex_unlock(&(philo->param->meal));
	return (1);
}

int	check_meal(t_param *param)
{
	pthread_mutex_lock(&(param->eat));
	if (param->finish_eat == param->nb_p && param->nb_p != -1)
	{
		pthread_mutex_lock(&(param->death));
		param->all_alive = 0;
		pthread_mutex_unlock(&(param->death));
		pthread_mutex_unlock(&(param->eat));
		return (0);
	}
	pthread_mutex_unlock(&(param->eat));
	return (1);
}

void	*check_death(void *params)
{
	int			i;
	t_param		*param;

	i = 0;
	param = (t_param *)params;
	while (1)
	{
		if (check_meal(param) == 0)
			return (NULL);
		if (!die(&(param->philo[i])) && param->all_alive)
		{
			pthread_mutex_lock(&(param->death));
			print_action(param->philo, 4);
			param->all_alive = 0;
			pthread_mutex_unlock(&(param->death));
			return (NULL);
		}
		i++;
		if (i >= param->nb_p)
			i = 0;
	}
	return (NULL);
}
