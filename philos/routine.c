#include "philos.h"

static void	*routine_for_one(t_philo *philo)
{
	printf("%ld %d has taken a fork\n", get_current_time(philo->table->start_time), philo->n);
	milliseconde_sleep(philo->config.time_to_die);
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
	while (philo && !philo->table->have_to_stop)
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
	return (NULL);
}
