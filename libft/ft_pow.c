/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 18:22:41 by seongjki          #+#    #+#             */
/*   Updated: 2021/09/26 13:57:11 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pow(int num, int power)
{
	if (power == 1)
		return (num);
	if (power == 0)
		return (1);
	return (2 * ft_pow(num, power - 1));
}
