/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgloriod <dgloriod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:12:38 by dgloriod          #+#    #+#             */
/*   Updated: 2022/11/14 21:12:39 by dgloriod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static void	*routine_for_one(t_philo *philo)
{
	print_has_taken_a_fork(philo);
	milliseconde_sleep(philo->config.time_to_die);
	philo->table->has_finish += 1;
	return (NULL);
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *) p;
	philo->last_eat = get_actual_time();
	philo->table->start_time = get_actual_time();
	if (philo->config.number_of_philos == 1)
		return (routine_for_one(philo));
	while (philo && !have_to_stop(philo))
	{
		if (!have_to_stop(philo) && philo->state == WAIT_FOR_START)
			make_start(philo);
		if (!have_to_stop(philo) && philo->state == WAIT_FOR_EAT_STATE)
			make_eat(philo);
		if (!have_to_stop(philo) && philo->state == SLEEPING_STATE)
			make_sleep(philo);
		if (!have_to_stop(philo) && philo->state == THINKING_STATE)
			make_think(philo);
	}
	philo->table->has_finish += 1;
	return (NULL);
}
