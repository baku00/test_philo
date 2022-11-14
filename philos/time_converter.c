/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_converter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgloriod <dgloriod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:12:44 by dgloriod          #+#    #+#             */
/*   Updated: 2022/11/14 21:12:45 by dgloriod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

long int	seconde_to_milliseconde(long int seconde)
{
	return (seconde * 1000);
}

long int	microseconde_to_milliseconde(long int microseconde)
{
	return (microseconde / 1000);
}

long int	get_time_pass(long int start, long int end)
{
	return (end - start);
}
