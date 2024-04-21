/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 08:36:41 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/21 11:47:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * Calculates the size of a delimited string.
 *
 * This function counts the number of delimited substrings in a given string.
 * Delimiters are spaces (' ') and the characters enclosed in single or double 
 * quotes (' or ").
 * The function returns the count of delimited substrings.
 * If the string has an unclosed quote, the function returns -2.
 *
 * @param s The input string to calculate the size of.
 * @return The count of delimited substrings in the string, or -2 if there is an 
 * 			unclosed quote.
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

/**
 * @brief Allocates memory and copies a string into it.
 *
 * This function allocates memory for a string of a given length plus 2, and
 * copies the input string into the newly allocated memory. The function uses
 * 'ft_strlcpy' to copy the string.
 *
 * @param s    The input string to be copied.
 * @param len  The length of the input string.
 *
 * @return     On success, the function returns a pointer to the newly allocated
 *             memory containing the copied string. If memory allocation fails,
 *             the function returns NULL.
 */
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
 * @brief Extracts the next substring from a string.
 *
 * This function extracts the next substring from a string 's', starting from
 * the position pointed to by 'start'. It skips any leading spaces and then
 * extracts characters until it encounters a space or the end of the string.
 * If a substring is enclosed in quotes, it includes the enclosed spaces.
 *
 * @param start  A pointer to the start position in the string 's'.
 * @param s      The input string from which to extract the substring.
 *
 * @return       On success, the function returns a pointer to the newly
 *               allocated memory containing the extracted substring. If the
 *               substring is still enclosed in quotes at the end of the string,
 *               the function returns NULL.
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
 * @brief Splits a command into its constituent substrings.
 *
 * This function splits a command string 's' into its constituent substrings,
 * using spaces as delimiters. It first counts the number of substrings in 's'
 * using the 'size_dstr' function. It then allocates memory for an array of
 * pointers to the substrings. It initializes 'start' to 0 and 'i' to -1, and
 * enters a loop where it extracts the next substring from 's' using the
 * 'get_next_substring' function and assigns it to the 'i'th element of the
 * array. If 'get_next_substring' returns NULL, it frees the array using the
 * 'double_free' function and returns NULL. After the loop, it sets the last
 * element of the array to NULL and returns the array.
 *
 * @param s  The command string to be split.
 *
 * @return   On success, the function returns a pointer to the array of
 *           substrings. If 's' is NULL, or if memory allocation fails, or if
 *           'get_next_substring' returns NULL, the function returns NULL.
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
