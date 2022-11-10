/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgloriod <dgloriod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:37:57 by dgloriod          #+#    #+#             */
/*   Updated: 2022/11/11 00:30:36 by dgloriod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static long int	gettime(void)
{
	long int		time;
	long int		second;
	long int		microsecond;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	microsecond = current_time.tv_usec;
	second = current_time.tv_sec;
	time = second * 1000000 + microsecond;
	return (time);
}

static void	make_eat(t_philo *philo)
{
	t_philo	*next;

	next = philo->next;
	pthread_mutex_lock(&philo->fork);
	printf("%ld %d has taken a fork\n", philo->current_time, philo->n);
	pthread_mutex_lock(&next->fork);
	printf("%ld %d has taken a fork\n", philo->current_time, philo->n);
	printf("%ld %d is eating\n", philo->current_time, philo->n);
	usleep(philo->config.time_to_eat * 1);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&next->fork);
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *) p;
	printf("HELLO\n");
	printf("%d\n", philo->state);
	while (1)
	{
		philo->current_time = gettime();
		if (philo->last_eat && philo->config.time_to_die + philo->current_time > philo->last_eat + philo->config.time_to_sleep)
		{
			printf("1\n");
			printf("Philo: %d\n", philo->n);
			printf("Current time: %ld\n", philo->current_time);
			printf("Time to die: %d\n", philo->config.time_to_die);
			printf("Last eat: %ld\n", philo->last_eat);
			printf("Time to sleep: %d\n", philo->config.time_to_sleep);
			printf("DEAD %d %ld\n", philo->n, philo->current_time);
			exit(0);
		}
		if (philo->state == EATING_STATE)
		{
			printf("2\n");
			make_eat(philo);
			philo->last_eat = gettime() + philo->config.time_to_eat;
			philo->state = SLEEPING_STATE;
		}
		else if (philo->state == SLEEPING_STATE)
		{
			printf("3\n");
			printf("%ld %d is sleeping\n", philo->current_time, philo->n);
			usleep(philo->config.time_to_sleep * 1);
			philo->state = THINKING_STATE;
		}
		else if (philo->state == THINKING_STATE)
		{
			printf("4\n");
			printf("%ld %d is thinking\n", philo->current_time, philo->n);
			philo->state = EATING_STATE;
		}
	}
	return (NULL);
}