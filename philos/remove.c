/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgloriod <dgloriod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:12:36 by dgloriod          #+#    #+#             */
/*   Updated: 2022/11/14 21:12:36 by dgloriod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static void	remove_one(t_philo *philo)
{
	if (&philo->fork)
		pthread_mutex_destroy(&philo->fork);
	pthread_join(philo->thread, NULL);
	if (philo)
		free(philo);
	philo = NULL;
}

void	remove_all(t_philo *philo)
{
	t_philo	*iter;
	int		number_of_philos;

	number_of_philos = philo->config.number_of_philos + 1;
	while (--number_of_philos && philo)
	{
		if (philo->next)
			iter = philo->next;
		remove_one(philo);
		if (iter)
			philo = iter;
	}
}
