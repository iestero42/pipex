/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:47:33 by yunlovex          #+#    #+#             */
/*   Updated: 2023/09/07 15:46:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Calculate the size of a null-terminated string array.
 *
 * This function calculates and returns the size (number of elements) of a
 * null-terminated string array.
 *
 * @param pointer   A pointer to the null-terminated string array.
 *
 * @return          The number of elements in the string array.
 *
 * @details
 * The 'ft_size' function iterates through the null-terminated string array
 * 'pointer' and counts the number of elements until a NULL pointer is
 * encountered. It returns the count as the size of the array.
 */
int	ft_size(char **pointer)
{
	int	i;

	i = 0;
	while (pointer[i])
		i++;
	return (i);
}
