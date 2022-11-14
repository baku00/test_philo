#include "philos.h"

static t_philo	*first_philo(t_philo *philo)
{
	while (philo->n != 1)
		philo = philo->next;
	return (philo);
}

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

	if (philo->config.number_of_philos == 1)
		return (remove_one(philo));
	iter = first_philo(philo)->next;
	philo = iter->prev;
	if (&philo->fork)
		pthread_mutex_destroy(&philo->fork);
	pthread_join(philo->thread, NULL);
	if (philo)
		free(philo);
	philo = NULL;
	philo = iter;
	number_of_philos = philo->config.number_of_philos;
	while (--number_of_philos)
	{
		iter = philo->next;
		if (&philo->fork)
			pthread_mutex_destroy(&philo->fork);
		pthread_join(philo->thread, NULL);
		if (philo)
			free(philo);
		philo = NULL;
		philo = iter;
	}
}
