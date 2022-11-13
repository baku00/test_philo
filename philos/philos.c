#include "philos.h"

static t_config	create_config(int argc, char **argv)
{
	t_config	config;

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

static t_philo *create_philos(t_philo *prev, t_config config, int i, t_table *table)
{
	t_philo	*philo;

	philo = ft_calloc(sizeof(t_philo), 1);
	if (!philo)
		return (NULL);
	philo->n = i + 1;
	philo->config = config;
	philo->config.total_time = philo->n + 1;
	philo->last_eat = get_actual_time();
	philo->table = table;
	philo->table->have_to_stop = 0;
	philo->number_of_eat = 0;
	if (philo->n % 2)
		philo->state = WAIT_FOR_START;
	else
		philo->state = WAIT_FOR_EAT_STATE;
	pthread_mutex_init(&philo->fork, NULL);
	philo->prev = prev;
	if (++i < config.number_of_philos)
		philo->next = create_philos(philo, config, i, table);
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
}

t_philo	*init_philos(int argc, char **argv)
{
	t_philo		*philo;
	t_config	config;
	t_table		table;

	config = create_config(argc, argv);
	philo = create_philos(NULL, config, 0, &table);
	philo = save_last(philo);
	create_thread(&philo);
	supervisor(philo);
	return (philo);
}