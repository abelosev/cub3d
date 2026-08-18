/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 14:21:50 by anbelose          #+#    #+#             */
/*   Updated: 2026/08/18 14:21:51 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

char	*skip_spaces(char *s)
{
	while (*s && is_space(*s))
		s++;
	return (s);
}

int	parse_int(char *s, int *out)
{
	int	value;
	int	i;

	i = 0;
	if (!s[0])
		return (0);
	value = 0;
	while (s[i])
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (0);
		value = value * 10 + (s[i] - '0');
		if (value > 255)
			return (0);
		i++;
	}
	*out = value;
	return (1);
}

int	is_blank_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	strip_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len && line[len - 1] == '\n')
		line[len - 1] = '\0';
}
