/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgloriod <dgloriod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 01:17:22 by dgloriod          #+#    #+#             */
/*   Updated: 2022/11/09 21:32:59 by dgloriod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv)
{
	t_philo	*philos;

	philos = init_philos(argc, argv);
	while (philos->next)
	{
		printf("%d\n", philos->n);
		philos = philos->next;
		usleep(100000);
	}
	return (0);
}

/*
2 Philo
410 time to die
200			eat
200			sleep
5			number eat

-> think 
*/
