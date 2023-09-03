/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:47:33 by yunlovex          #+#    #+#             */
/*   Updated: 2023/09/03 11:48:20 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Ft_size:
 * * Calculates the size (number of elements) in a 
 * * null-terminated array of strings.
 *
 * @param pointer   Pointer to the array of strings.
 * @return          The number of elements (size) in the array.
 */
int	ft_size(char **pointer)
{
	int	i;

	i = 0;
	while (pointer[i])
		i++;
	return (i);
}
