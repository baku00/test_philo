/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgloriod <dgloriod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 01:32:30 by dgloriod          #+#    #+#             */
/*   Updated: 2022/11/13 16:34:46 by dgloriod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static int	can_use_fork(t_philo *philo, pthread_mutex_t *fork)
{
	if (pthread_mutex_lock(fork) == 0)
	{
		printf("%ld %d has token a fork\n", get_current_time(philo->table->start_time), philo->n);
		return (1);
	}
	return (0);
}

static int	make_eat(t_philo *philo)
{
	t_philo	*next;

	next = philo->next;
	if (have_to_stop(philo))
		return (0);
	if (can_use_fork(philo, &philo->fork) && can_use_fork(philo, &next->fork))
	{
		printf("%ld %d is eating\n", get_current_time(philo->table->start_time), philo->n);
		philo->state = EATING_STATE;
		if (philo->config.number_of_eat >= 1)
			philo->number_of_eat += 1;
		philo->last_eat = get_actual_time();
		milliseconde_sleep(philo->config.time_to_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&next->fork);
		return (1);
	}
	return (0);
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *) p;
	philo->last_eat = get_actual_time();
	philo->table->start_time = get_actual_time();
	while (!philo->table->have_to_stop)
	{
		if (philo->state == WAIT_FOR_START)
		{
			milliseconde_sleep(2);
			philo->state = WAIT_FOR_EAT_STATE;
		}
		if (!have_to_stop(philo) && philo->state == WAIT_FOR_EAT_STATE && make_eat(philo))
		{
			philo->state = SLEEPING_STATE;
		}
		if (!have_to_stop(philo) && philo->state == SLEEPING_STATE)
		{
			printf("%ld %d is sleeping\n", get_current_time(philo->table->start_time), philo->n);
			milliseconde_sleep(philo->config.time_to_sleep * 1);
			philo->state = THINKING_STATE;
		}
		if (!have_to_stop(philo) && philo->state == THINKING_STATE)
		{
			printf("%ld %d is thinking\n", get_current_time(philo->table->start_time), philo->n);
			philo->state = WAIT_FOR_EAT_STATE;
		}
	}
	return (NULL);
}