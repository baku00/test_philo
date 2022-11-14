/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgloriod <dgloriod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:13:14 by dgloriod          #+#    #+#             */
/*   Updated: 2022/11/14 21:13:15 by dgloriod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Argument invalid\n");
		return (0);
	}
	init_philos(argc, argv);
	return (0);
}
