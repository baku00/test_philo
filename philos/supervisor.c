/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgloriod <dgloriod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 02:16:58 by dgloriod          #+#    #+#             */
/*   Updated: 2022/11/13 06:31:35 by dgloriod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static int	have_the_time(t_philo *philo)
{
	return (get_actual_time() - philo->last_eat) < philo->config.time_to_die;
}

static int	reach_number_of_eat(t_philo *philo)
{
	return (philo->number_of_eat >= philo->config.number_of_eat && philo->config.number_of_eat >= 1);
}

int	have_to_stop(t_philo *philo)
{
	if (!have_the_time(philo))
		philo->table->have_to_stop = DEAD;
	else if (reach_number_of_eat(philo))
		philo->table->have_to_stop = REACH_MEAL;
	return (philo->table->have_to_stop);
}

static void	remove_all(t_philo *philo)
{
	while (philo->n != 1)
		philo = philo->next;
	while (philo->n != philo->config.number_of_philos)
	{
		pthread_detach(philo->thread);
		free(philo->thread);
		pthread_mutex_destroy(&philo->fork);
		if (philo->next)
			philo = philo->next;
		free(philo->prev);
		philo->prev = NULL;
	}
}

void	supervisor(t_philo *philos)
{
	while (philos->next && !philos->table->have_to_stop)
	{
		if (!have_to_stop(philos))
			philos = philos->next;
		else
			philos->table->philo = philos;
	}
	if (philos->table->have_to_stop == DEAD)
		printf("%ld %d is dead\n", get_current_time(philos->table->start_time), philos->n);
	else if (philos->table->have_to_stop == REACH_MEAL)
		printf("%ld %d has reach number of meal\n", get_current_time(philos->table->start_time), philos->n);
	remove_all(philos);
}