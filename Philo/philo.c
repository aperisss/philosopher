/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:17:28 by aperis            #+#    #+#             */
/*   Updated: 2022/06/27 14:35:00 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_param *param, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < param->nb_p)
	{
		philo[i].id = i + 1;
		philo[i].nb_eat = 0;
		philo[i].param = param;
		philo[i].last_meal = 0;
		philo[i].have_eat = 0;
		pthread_mutex_init(&(philo[i].right_fork), NULL);
		if (i == param->nb_p - 1)
			philo[0].left_fork = &(philo[philo->param->nb_p - 1].right_fork);
		else
			philo[i + 1].left_fork = &(philo[i].right_fork);
		i++;
	}
}

void	set_param(t_param *param, char **av)
{	
	pthread_mutex_init(&(param->msg), NULL);
	pthread_mutex_init(&(param->eat), NULL);
	pthread_mutex_init(&(param->death), NULL);
	pthread_mutex_init(&(param->meal), NULL);
	param->nb_p = ft_atoi(av[1]);
	param->ttd = ft_atoi(av[2]);
	param->tte = ft_atoi(av[3]);
	param->tts = ft_atoi(av[4]);
	param->all_alive = 1;
	param->finish_eat = 0;
	param->start_time = 0;
	param->philo = NULL;
	if (av[5])
		param->nb_pme = ft_atoi(av[5]);
	else
		param->nb_pme = -1;
}

void	print_action(t_philo *philo, int tmp)
{
	static int	die;

	pthread_mutex_lock(&(philo->param->msg));
	if (die == 0)
	{
		if (tmp == EATING)
			printf("%lld %d is eating\n", get_time(philo->param), philo->id);
		else if (tmp == SLEEPING)
			printf("%lld %d is sleeping\n", get_time(philo->param), philo->id);
		else if (tmp == TAKE_FORK)
			printf("%lld %d has taken a fork\n", get_time(philo->param),
				philo->id);
		else if (tmp == THINKING)
			printf("%lld %d is thinking\n", get_time(philo->param), philo->id);
		else if (tmp == DIE)
		{
			die = 1;
			printf("%lld %d died\n", get_time(philo->param), philo->id);
		}
	}
	pthread_mutex_unlock(&(philo->param->msg));
}

void	lauch_philo(t_param *param, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < param->nb_p)
	{
		pthread_create(&(philo[i].thread), NULL, &routine, &(philo[i]));
		i++;
	}
	i = 0;
	pthread_create(&param->control, NULL, &check_death, param);
	pthread_join(param->control, NULL);
	while (i < param->nb_p)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}
