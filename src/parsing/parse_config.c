#include "parsing.h"

/*
** Идентификатор совпадает, если сразу за ним идёт пробел/таб ИЛИ
** конец строки. Второй случай обязателен: строка вроде "NO" (без
** пути и вообще без пробела после идентификатора) всё равно должна
** распознаваться как идентификатор NO с отсутствующим аргументом -
** и корректно давать "missing path for north texture" (через
** set_texture -> skip_spaces("") -> !*path), а не молча проваливаться
** мимо всех identifier-проверок и ошибочно считаться началом карты.
** Без этой проверки на '\0' такая строка не матчилась НИ под один
** идентификатор и уходила в cub->map, где давала гораздо менее
** внятную ошибку (или вовсе не ту, что нужно) через
** validate_map_chars.
**
** Ложных срабатываний это не создаёт: "NOTHING" по-прежнему не
** матчится под "NO", потому что line[len] в этом случае - 'T', а не
** пробел и не '\0'.
*/
static int	match_identifier(char *line, char *id)
{
	size_t	len;

	len = ft_strlen(id);
	if (ft_strncmp(line, id, len) != 0)
		return (0);
	return (line[len] == '\0' || is_space_char(line[len]));
}

/*
** Собирает "part1part2part3" через ft_strjoin (snprintf не входит в
** список разрешённых функций сабжекта). Программа завершается сразу
** после использования этого сообщения через parse_error, поэтому
** промежуточные буферы освобождает ОС при exit.
*/
static char	*build_msg(char *p1, char *p2, char *p3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(p1, p2);
	if (!tmp)
		return (p1);
	res = ft_strjoin(tmp, p3);
	free(tmp);
	if (!res)
		return (p1);
	return (res);
}

/*
** Путь к текстуре не может содержать пробелов (валидные Unix-пути
** без пробелов покрывают subject), поэтому конец пути - это первый
** пробельный символ после него. Если после skip_spaces(end) там
** ещё что-то осталось - это лишний аргумент -> ошибка. Иначе путь
** обрезается на месте (end становится '\0'), чтобы open()/strdup()
** ниже видели только сам путь, без хвостовых пробелов.
*/
static void	cut_trailing_args(t_cub *cub, char *path, char *name)
{
	char	*end;

	end = path;
	while (*end && !is_space_char(*end))
		end++;
	if (*end)
	{
		if (*skip_spaces(end))
			parse_error(cub, build_msg("unexpected extra arguments after ",
					name, " texture path"));
		*end = '\0';
	}
}

static void	set_texture(t_cub *cub, char **field, char *rest, char *name)
{
	char	*path;
	int		fd;

	if (*field)
		parse_error(cub, build_msg("duplicate ", name, " texture identifier"));
	path = skip_spaces(rest);
	if (!*path)
		parse_error(cub, build_msg("missing path for ", name, " texture"));
	cut_trailing_args(cub, path, name);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		parse_error(cub, build_msg("cannot open ", name, " texture file"));
	close(fd);
	*field = ft_strdup(path);
	if (!*field)
		parse_error(cub, "malloc failure while storing a texture path");
}

/*
** Обрезает пробелы/табы по краям одного RGB-токена ПРЯМО В ЕГО
** БУФЕРЕ (это безопасно: буфер принадлежит нам, а free_tokens()
** всё равно освобождает исходный указатель tokens[i], который мы
** не меняем — меняется только содержимое и локальный указатель
** start). Внутренние пробелы (например "1 0") не трогаются и
** по-прежнему приводят к ошибке в parse_int_strict, потому что это
** не является допустимым числом.
**
** Это позволяет принимать варианты вроде "F 220, 100, 0" или
** "F 220 ,100,0", а не только "F 220,100,0", оставаясь при этом
** строгим ко всему остальному (буквы, лишние символы, пустой
** компонент).
*/
static int	parse_rgb_token(char *token, int *out)
{
	char	*start;
	char	*end;

	start = skip_spaces(token);
	end = start + ft_strlen(start);
	while (end > start && is_space_char(end[-1]))
		end--;
	*end = '\0';
	return (parse_int_strict(start, out));
}

static int	extract_rgb(char **tokens, int *values)
{
	int	i;

	i = 0;
	while (tokens[i] && i < 4)
		i++;
	if (i != 3)
		return (0);
	if (!parse_rgb_token(tokens[0], &values[0]))
		return (0);
	if (!parse_rgb_token(tokens[1], &values[1]))
		return (0);
	if (!parse_rgb_token(tokens[2], &values[2]))
		return (0);
	return (1);
}

static void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

static void	parse_color(t_cub *cub, t_color *color, char *rest, char *name)
{
	char	**tokens;
	int		values[3];

	if (color->is_set)
		parse_error(cub, build_msg("duplicate ", name, " color identifier"));
	tokens = ft_split(skip_spaces(rest), ',');
	if (!tokens)
		parse_error(cub, "malloc failure while parsing a color");
	if (!extract_rgb(tokens, values))
	{
		free_tokens(tokens);
		parse_error(cub, build_msg(name,
				" color must be formatted as R,G,B with values 0-255", ""));
	}
	free_tokens(tokens);
	color->r = values[0];
	color->g = values[1];
	color->b = values[2];
	color->is_set = 1;
}

/*
** Возвращает 1, если строка была распознанным config-идентификатором
** (и разобрана, либо программа уже завершилась с ошибкой).
** Возвращает 0, если строка вообще не подошла ни под один
** идентификатор — тогда вызывающий код считает её началом карты.
*/
int	try_parse_config(t_cub *cub, char *line)
{
	if (match_identifier(line, "NO"))
		set_texture(cub, &cub->no_path, line + 2, "north");
	else if (match_identifier(line, "SO"))
		set_texture(cub, &cub->so_path, line + 2, "south");
	else if (match_identifier(line, "WE"))
		set_texture(cub, &cub->we_path, line + 2, "west");
	else if (match_identifier(line, "EA"))
		set_texture(cub, &cub->ea_path, line + 2, "east");
	else if (match_identifier(line, "F"))
		parse_color(cub, &cub->floor, line + 1, "floor");
	else if (match_identifier(line, "C"))
		parse_color(cub, &cub->ceiling, line + 1, "ceiling");
	else
		return (0);
	return (1);
}

void	check_config_complete(t_cub *cub)
{
	if (!cub->no_path)
		parse_error(cub, "missing north texture (NO)");
	if (!cub->so_path)
		parse_error(cub, "missing south texture (SO)");
	if (!cub->we_path)
		parse_error(cub, "missing west texture (WE)");
	if (!cub->ea_path)
		parse_error(cub, "missing east texture (EA)");
	if (!cub->floor.is_set)
		parse_error(cub, "missing floor color (F)");
	if (!cub->ceiling.is_set)
		parse_error(cub, "missing ceiling color (C)");
}
