/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 14:41:43 by seongjki          #+#    #+#             */
/*   Updated: 2021/10/28 12:41:15 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	make_cnt(int n, int base_len)
{
	int	cnt;

	cnt = 0;
	while (n > 0)
	{
		n /= base_len;
		cnt++;
	}
	return (cnt + (cnt == 0));
}

char	*ft_convert_base(int n, char *base)
{
	int		base_len;
	char	*ret;
	int		cnt;
	int		idx;

	base_len = ft_strlen(base);
	cnt = make_cnt(n, base_len);
	idx = cnt - 1;
	ret = (char *)malloc(sizeof(char) * (cnt + 1));
	if (!ret)
		return (0);
	ret[cnt] = '\0';
	if (n == 0)
		ret[0] = '0';
	while (n > 0)
	{
		ret[idx] = base[n % base_len];
		n /= base_len;
		idx--;
	}
	return (ret);
}
