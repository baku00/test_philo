/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgloriod <dgloriod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:13:12 by dgloriod          #+#    #+#             */
/*   Updated: 2022/11/14 21:13:12 by dgloriod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "../../main.h"

int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
int		ft_isdigit(int d);
int		ft_isspace(int c);
int		ft_strlen(char *str);
#endif