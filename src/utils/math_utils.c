/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:47:33 by yunlovex          #+#    #+#             */
/*   Updated: 2024/02/02 08:07:51 by iestero-         ###   ########.fr       */
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

/**
 * @brief 
 * 
 * @param s 
 * @return int 
 */
static int	size_dstr(const char *s)
{
	int		count;
	int		i;
	char	in_quotes;

	count = 0;
	in_quotes = UNQUOTED;
	i = -1;
	while (s[++i] != '\0')
	{
		if ((s[i] == '"' || s[i] == '\'') && !in_quotes)
			in_quotes = s[i];
		else if (in_quotes == s[i] && in_quotes)
		{
			in_quotes = UNQUOTED;
			count++;
		}
		else if ((s[i] == ' ' || s[i + 1] == '\0') && !in_quotes)
			count++;
	}
	if (in_quotes)
		return (-2);
	return (count);
}

static char	*save_memory(const char *s, size_t len)
{
	char	*substr;

	substr = (char *) malloc(sizeof(char) * (len + 2));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, (char *) s, len + 1);
	return (substr);
}

/**
 * @brief Get the next substring object
 * 
 * @param s 
 * @return char* 
 */
static char	*get_next_substring(int *start, const char *s)
{
	const char	*start_chr;
	char		in_quotes;
	int			i;

	start_chr = &s[*start];
	in_quotes = UNQUOTED;
	while (*start_chr == ' ')
		start_chr++;
	i = 0;
	while (start_chr[i] && (in_quotes || start_chr[i] != ' '))
	{
		if ((start_chr[i] == '"' || start_chr[i] == '\'') && !in_quotes)
			in_quotes = start_chr[i];
		else if (start_chr[i] == in_quotes && in_quotes)
		{
			in_quotes = UNQUOTED;
			i++;
			break ;
		}
		i++;
	}
	if (in_quotes)
		return (NULL);
	*start = *start + i + 1;
	return (save_memory(start_chr, i));
}

/**
 * @brief 
 * 
 * @param s 
 * @return char** 
 */
char	**split_command(const char *s)
{
	int			num_substrings;
	char		**substrings;
	int			start;
	int			i;

	if (s == NULL)
		return (NULL);
	num_substrings = size_dstr(s);
	substrings = malloc(sizeof(char *) * (num_substrings + 1));
	if (!substrings)
		return (NULL);
	start = 0;
	i = -1;
	while (++i < num_substrings)
	{
		substrings[i] = get_next_substring(&start, s);
		if (substrings[i] == NULL)
		{
			double_free(substrings);
			return (NULL);
		}
	}
	substrings[num_substrings] = NULL;
	return (substrings);
}
