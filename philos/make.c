#include "philos.h"

void	make_eat(t_philo *philo)
{
	t_philo	*next;

	if (!philo || !(&philo->fork))
		return ;
	next = philo->next;
	if (!(&next->fork))
		return ;
	if (can_take_a_fork(philo) == 0 && can_eat(philo) && !have_to_stop(philo))
	{
		printf("%ld %d has taken a fork\n", get_current_time(philo->table->start_time), philo->n);
		if (can_take_a_fork(next) == 0 && !have_to_stop(philo))
		{
			printf("%ld %d has taken a fork\n", get_current_time(philo->table->start_time), philo->n);
			printf("%ld %d is eating\n", \
			get_current_time(philo->table->start_time), philo->n);
			milliseconde_sleep(philo->config.time_to_eat);
			pthread_mutex_unlock(&philo->fork);
			pthread_mutex_unlock(&next->fork);
			if (philo->config.number_of_eat >= 1)
				philo->number_of_eat += 1;
			philo->last_eat = get_actual_time();
			philo->state = SLEEPING_STATE;
		}
	}
}

void	make_sleep(t_philo *philo)
{
	if (!philo && !have_to_stop(philo))
		return ;
	printf("%ld %d is sleeping\n", \
	get_current_time(philo->table->start_time), philo->n);
	milliseconde_sleep(philo->config.time_to_sleep);
	philo->state = THINKING_STATE;
}

void	make_think(t_philo *philo)
{
	if (!philo && !have_to_stop(philo))
		return ;
	printf("%ld %d is thinking\n", \
	get_current_time(philo->table->start_time), philo->n);
	philo->state = WAIT_FOR_EAT_STATE;
}

void	make_start(t_philo *philo)
{
	if (!philo && !have_to_stop(philo))
		return ;
	milliseconde_sleep(2);
	philo->state = WAIT_FOR_EAT_STATE;
}
