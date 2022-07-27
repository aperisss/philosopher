/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:46:14 by aperis            #+#    #+#             */
/*   Updated: 2022/06/27 15:27:13 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(t_philo *philo, unsigned long int time)
{
	unsigned long int	start;

	start = get_time(philo->param);
	while (get_time(philo->param) - start < time)
	{
		pthread_mutex_lock(&(philo->param->death));
		if (philo->param->all_alive == 0)
		{
			pthread_mutex_unlock(&(philo->param->death));
			break ;
		}
		pthread_mutex_unlock(&(philo->param->death));
		usleep(100);
	}
}

void	*diner(t_philo *philo)
{
	take_right_fork(philo);
	take_left_fork(philo);
	eating(philo);
	if (philo->param->nb_pme != -1)
		finish_eat(philo);
	sleeping(philo);
	thinking(philo);
	pthread_mutex_lock(&(philo->param->death));
	if (philo->param->all_alive == 0)
	{
		pthread_mutex_unlock(&(philo->param->death));
		return (NULL);
	}
	else
		pthread_mutex_unlock(&(philo->param->death));
	return ((void *)philo);
}

void	*routine(void *phila)
{
	t_philo	*philo;

	philo = (t_philo *)phila;
	if (philo->id % 2 != 0)
	{
		if (philo->id == philo->param->nb_p)
		{
			ft_usleep(philo, 50);
		}
		ft_usleep(philo, 50);
	}
	if (philo->param->nb_pme == -1)
	{
		while (1)
		{
			if (diner(philo) == NULL)
				return (NULL);
		}
	}
	while (1 && philo->nb_eat < philo->param->nb_pme)
	{
		if (diner(philo) == NULL)
			return (NULL);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_param	*param;
	t_philo	*philo;

	if (check_arg(ac, av) == 0)
		return (0);
	if (one_philo(av) == 0)
		return (0);
	param = NULL;
	philo = NULL;
	param = malloc(sizeof(t_param));
	set_param(param, av);
	philo = malloc(sizeof(t_philo) * param->nb_p);
	init_philo(param, philo);
	param->philo = philo;
	param->start_time = get_time(param);
	lauch_philo(param, philo);
	return (free(param), free(philo), 0);
}
