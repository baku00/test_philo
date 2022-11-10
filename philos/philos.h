/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgloriod <dgloriod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 21:51:58 by dgloriod          #+#    #+#             */
/*   Updated: 2022/11/11 00:30:47 by dgloriod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H
# include "../main.h"

typedef struct s_config
{
	int	number_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_eat;
	int	total_time;
}	t_config;

typedef struct s_philo
{
	int				n;
	long int		last_eat;
	long int		current_time;
	int				number_of_eat;
	t_config		config;
	int				thread_id;
	int				fork_number;
	int				state;
	pthread_mutex_t	fork;
	pthread_t		thread;
	void			*next;
	void			*prev;
}   t_philo;

t_philo	*init_philos(int argc, char **argv);
void	*routine();
#endif