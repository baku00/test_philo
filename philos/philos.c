/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgloriod <dgloriod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:22:56 by dgloriod          #+#    #+#             */
/*   Updated: 2022/11/11 00:30:49 by dgloriod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static t_config	create_config(int argc, char **argv)
{
	t_config	config;
	// int			i;

	// i = -1;
	// while (argv[++i])
	// 	printf("Argv[%d]: %s\n", i, argv[i]);
	config.number_of_philos = ft_atoi(argv[1]);
	config.time_to_die = ft_atoi(argv[2]);
	config.time_to_eat = ft_atoi(argv[3]);
	config.time_to_sleep = ft_atoi(argv[4]);
	config.total_time = 0;
	if (argc == 6)
		config.number_of_eat = ft_atoi(argv[5]);
	else
		config.number_of_eat = -1;
	return (config);
}

static t_philo *create_philos(t_philo *prev, t_config config, int i)
{
	t_philo	*philo;

	philo = ft_calloc(sizeof(t_philo), 1);
	if (!philo)
		return (NULL);
	philo->n = i + 1;
	philo->config = config;
	philo->last_eat = 0;
	philo->fork_number = 0;
	if (philo->n % 2)
		philo->state = SLEEPING_STATE;
	else
		philo->state = EATING_STATE;
	pthread_mutex_init(&philo->fork, NULL);
	philo->prev = prev;
	if (++i < config.number_of_philos)
		philo->next = create_philos(philo, config, i);
	return (philo);
}

static t_philo	*save_last(t_philo *philo)
{
	t_philo	*last;

	last = philo;
	while (last->next)
		last = last->next;
	last->next = philo;
	philo->prev = last;
	return (philo);
}

static void	create_thread(t_philo **philos)
{
	while ((*philos)->n < (*philos)->config.number_of_philos)
	{
		pthread_create(&(*philos)->thread, NULL, &routine, *philos);
		*philos = (*philos)->next;
	}
	pthread_create(&(*philos)->thread, NULL, &routine, *philos);
	while ((*philos)->n < (*philos)->config.number_of_philos)
	{
		pthread_join((*philos)->thread, NULL);
		*philos = (*philos)->next;
	}
	pthread_join((*philos)->thread, NULL);
}

t_philo	*init_philos(int argc, char **argv)
{
	t_philo		*philo;
	t_config	config;

	config = create_config(argc, argv);
	philo = create_philos(NULL, config, 0);
	philo = save_last(philo);
	create_thread(&philo);
	return (philo);
}