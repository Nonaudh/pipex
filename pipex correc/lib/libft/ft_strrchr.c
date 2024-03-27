/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:50:34 by ahuge             #+#    #+#             */
/*   Updated: 2023/11/07 20:43:57 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *src, int c)
{
	int	i;
	int	x;

	i = 0;
	x = -1;
	while (src[i])
	{
		if (src[i] == (char)c)
			x = i;
		i++;
	}
	if (c == '\0')
		return ((char *)src + i);
	if (x == -1)
		return (0);
	else
		return ((char *)src + x);
}
