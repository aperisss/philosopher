/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:40:29 by aperis            #+#    #+#             */
/*   Updated: 2022/07/05 11:07:42 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>

typedef enum e_state
{
	EATING,
	THINKING,
	SLEEPING,
	TAKE_FORK,
	DIE,
}	t_state;

typedef struct s_philo
{
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	pthread_t		thread;
	struct s_param	*param;
	int				id;
	int				have_eat;
	int				nb_eat;
	long long		last_meal;
}	t_philo;

typedef struct s_param
{
	pthread_mutex_t	eat;
	pthread_mutex_t	msg;
	pthread_mutex_t	death;
	pthread_mutex_t	meal;
	pthread_t		control;
	t_philo			*philo;
	long long		start_time;
	int				nb_p;
	int				ttd;
	int				tte;
	int				tts;
	int				nb_pme;
	int				all_alive;
	int				finish_eat;
}	t_param;

int			ft_atoi(char *nptr);
int			die(t_philo *philo);
int			one_philo(char **av);
int			check_arg(int ac, char **av);
int			check_ac(int ac);
void		set_param(t_param *param, char **av);
void		init_philo(t_param *param, t_philo *philo);
void		init_fork(t_philo *philo);
void		lauch_philo(t_param *param, t_philo *philo);
void		print_action(t_philo *philo, int tmp);
void		*routine(void *philo);
void		*diner(t_philo *philo);
void		take_right_fork(t_philo *philo);
void		take_left_fork(t_philo *philo);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
void		have_eat(t_philo *philo);
void		*check_death(void *phila);
void		dead_philo(t_param *param);
void		*check_death(void *params);
void		ft_usleep(t_philo *philo, unsigned long int time);
void		finish_eat(t_philo *philo);
long long	get_time(t_param *param);

//gcc -g -phtread *.c
#endif
