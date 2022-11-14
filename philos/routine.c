#include "philos.h"

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *) p;
	philo->last_eat = get_actual_time();
	philo->table->start_time = get_actual_time();
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
