#include "philos.h"

int	can_take_a_fork(t_philo *philo)
{
	return (pthread_mutex_lock(&philo->fork));
}

int	can_eat(t_philo *philo)
{
	return (philo->number_of_eat < philo->config.number_of_eat);
}
