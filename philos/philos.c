/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgloriod <dgloriod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:12:28 by dgloriod          #+#    #+#             */
/*   Updated: 2022/11/14 21:12:29 by dgloriod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static t_config	create_config(int argc, char **argv)
{
	t_config	config;

	config.error = 0;
	config.number_of_philos = ft_atoi(argv[1]);
	config.time_to_die = ft_atoi(argv[2]);
	if (config.number_of_philos < 1 || config.time_to_die < 1)
		config.error = 1;
	config.time_to_eat = ft_atoi(argv[3]);
	config.time_to_sleep = ft_atoi(argv[4]);
	if (config.time_to_sleep < 1 || config.time_to_eat < 1)
		config.error = 1;
	if (argc == 6)
	{
		config.number_of_eat = ft_atoi(argv[5]);
		if (config.number_of_eat < 1)
			config.error = 1;
	}
	else
		config.number_of_eat = 0;
	return (config);
}

static t_philo	*create_philos(t_philo *prev, t_config config, \
int i, t_table *table)
{
	t_philo	*philo;

	philo = (t_philo *)ft_calloc(sizeof(t_philo), 1);
	if (!philo)
		return (NULL);
	philo->n = i + 1;
	philo->config = config;
	philo->last_eat = get_actual_time();
	philo->table = table;
	philo->table->have_to_stop = 0;
	philo->table->has_finish = 0;
	philo->number_of_eat = -1;
	philo->fork_state = FORK_UNLOCK;
	if (philo->n % 2)
		philo->state = WAIT_FOR_START;
	else
		philo->state = WAIT_FOR_EAT_STATE;
	pthread_mutex_init(&philo->fork, NULL);
	philo->prev = prev;
	if (++i < config.number_of_philos)
		philo->next = create_philos(philo, config, i, table);
	else
		philo->next = NULL;
	return (philo);
}

static void	create_thread(t_philo *philos)
{
	while (philos->n < philos->config.number_of_philos)
	{
		pthread_create(&philos->thread, NULL, &routine, philos);
		philos = philos->next;
	}
	pthread_create(&philos->thread, NULL, &routine, philos);
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

void	init_philos(int argc, char **argv)
{
	t_philo		*philo;
	t_config	config;
	t_table		table;

	config = create_config(argc, argv);
	if (config.error)
	{
		printf("Argument invalide\n");
		return ;
	}
	philo = create_philos(NULL, config, 0, &table);
	philo = save_last(philo);
	create_thread(philo);
	supervisor(philo);
}
