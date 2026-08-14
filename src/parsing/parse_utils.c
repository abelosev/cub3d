#include "parsing.h"

int	is_space_char(char c)
{
	return (c == ' ' || c == '\t');
}

char	*skip_spaces(char *s)
{
	while (*s && is_space_char(*s))
		s++;
	return (s);
}

int	parse_int_strict(char *s, int *out)
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
		if (!is_space_char(line[i]))
			return (0);
		i++;
	}
	return (1);
}