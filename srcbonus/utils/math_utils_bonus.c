/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:47:33 by yunlovex          #+#    #+#             */
/*   Updated: 2023/12/11 12:13:34 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

/**
 * @brief Compare two strings lexicographically with limited length.
 *
 * This function compares two strings 's1' and 's2' lexicographically up to
 * the length of the shorter string. It returns an integer less than, equal to,
 * or greater than zero if 's1' is found to be less than, equal to, or greater
 * than 's2', respectively.
 *
 * @param s1   The first string to compare.
 * @param s2   The second string to compare.
 *
 * @return     An integer less than, equal to, or greater than zero if 's1' is
 *             found to be less than, equal to, or greater than 's2',
 * 			   respectively.
 *
 * @details
 * The 'ft_strcmp' function performs lexicographic comparison between two
 * strings, 's1' and 's2', up to the length of the shorter string.
 * It returns an integer value that indicates the relationship between
 * the two strings. If 's1' is found to be less than 's2', it returns
 * a negative value. If 's1' is equal to 's2', it returns zero.
 * If 's1' is greater than 's2', it returns a positive value. This function
 * is designed to work with strings of different lengths and avoids
 * buffer overflow issues.
 */
int	ft_strcmp(char *s1, char *s2)
{
	int	len_s1;
	int	len_s2;

	len_s2 = ft_strlen(s2);
	len_s1 = ft_strlen(s1);
	if (len_s1 > len_s2)
		return (ft_strncmp(s1, s2, len_s1));
	else
		return (ft_strncmp(s1, s2, len_s2));
}
