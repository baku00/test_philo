/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgloriod <dgloriod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:12:31 by dgloriod          #+#    #+#             */
/*   Updated: 2022/11/14 21:12:31 by dgloriod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H
# include "../main.h"
# define FORK_LOCK 1
# define FORK_UNLOCK 2

typedef struct s_config
{
	int	number_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_eat;
	int	error;
}	t_config;

typedef struct s_table
{
	int			have_to_stop;
	long int	start_time;
	int			has_finish;
	void		*philo;
}	t_table;

typedef struct s_philo
{
	int				n;
	long int		last_eat;
	long int		current_time;
	int				number_of_eat;
	t_config		config;
	t_table			*table;
	int				thread_id;
	int				fork_number;
	int				state;
	int				fork_state;
	pthread_mutex_t	fork;
	pthread_t		thread;
	void			*next;
	void			*prev;
}	t_philo;

void		init_philos(int argc, char **argv);
void		*routine(void *p);
long int	get_actual_time(void);
void		milliseconde_sleep(long int milliseconde);
long int	seconde_to_milliseconde(long int seconde);
long int	microseconde_to_milliseconde(long int microseconde);
long int	get_time_pass(long int start, long int end);
void		supervisor(t_philo *philos);
long int	get_current_time(long int start_time);
int			have_to_stop(t_philo *philo);
void		remove_all(t_philo *philo);
void		make_eat(t_philo *philo);
void		make_sleep(t_philo *philo);
void		make_think(t_philo *philo);
void		make_start(t_philo *philo);
int			can_take_a_fork(t_philo *philo);
int			can_eat(t_philo *philo);
void		print_has_taken_a_fork(t_philo *philo);
void		print_eat(t_philo *philo);
void		print_sleep(t_philo *philo);
void		print_think(t_philo *philo);
void		print_dead(t_philo *philo);
#endif