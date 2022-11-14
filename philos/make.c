/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgloriod <dgloriod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:12:26 by dgloriod          #+#    #+#             */
/*   Updated: 2022/11/14 21:12:26 by dgloriod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	make_eat(t_philo *philo)
{
	t_philo	*next;

	if (!philo || !(&philo->fork))
		return ;
	next = philo->next;
	if (!(&next->fork))
		return ;
	if (can_take_a_fork(philo) == 0 && can_eat(philo) && !have_to_stop(philo))
	{
		print_has_taken_a_fork(philo);
		if (can_take_a_fork(next) == 0 && !have_to_stop(philo))
		{
			print_has_taken_a_fork(philo);
			print_eat(philo);
			milliseconde_sleep(philo->config.time_to_eat);
			pthread_mutex_unlock(&philo->fork);
			pthread_mutex_unlock(&next->fork);
			if (philo->config.number_of_eat >= 1)
				philo->number_of_eat += 1;
			philo->last_eat = get_actual_time();
			philo->state = SLEEPING_STATE;
		}
		if (have_to_stop(philo))
			pthread_mutex_unlock(&philo->fork);
	}
}

void	make_sleep(t_philo *philo)
{
	if (!philo && !have_to_stop(philo))
		return ;
	print_sleep(philo);
	milliseconde_sleep(philo->config.time_to_sleep);
	philo->state = THINKING_STATE;
}

void	make_think(t_philo *philo)
{
	if (!philo && !have_to_stop(philo))
		return ;
	print_think(philo);
	philo->state = WAIT_FOR_EAT_STATE;
}

void	make_start(t_philo *philo)
{
	if (!philo && !have_to_stop(philo))
		return ;
	milliseconde_sleep(2);
	philo->state = WAIT_FOR_EAT_STATE;
}
