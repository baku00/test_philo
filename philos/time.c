/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgloriod <dgloriod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:12:49 by dgloriod          #+#    #+#             */
/*   Updated: 2022/11/14 21:12:51 by dgloriod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

long int	get_actual_time(void)
{
	long int		time;
	long int		seconde;
	long int		microseconde;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	seconde = seconde_to_milliseconde(current_time.tv_sec);
	microseconde = microseconde_to_milliseconde(current_time.tv_usec);
	time = seconde + microseconde;
	return (time);
}

void	milliseconde_sleep(long int milliseconde)
{
	long int	start_time;
	long int	timer_ms;

	start_time = get_actual_time();
	timer_ms = get_time_pass(start_time, get_actual_time());
	while (timer_ms < milliseconde)
	{
		timer_ms = get_time_pass(start_time, get_actual_time());
		usleep(milliseconde / 1000);
	}
}

long int	get_current_time(long int start_time)
{
	return (get_actual_time() - start_time);
}
