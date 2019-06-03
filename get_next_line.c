/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: japarbs <japarbs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 01:32:33 by japarbs           #+#    #+#             */
/*   Updated: 2019/06/02 21:05:26 by japarbs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	**read_line(int fd, char **line, size_t line_index, int EOF)
{
	size_t			count;
	size_t			i;
	char			buffer[BUFF_SIZE];
	char			tmp[MAX_BUFFS][BUFF_SIZE + 1];

	count = 0;
	i = 0;
	while (read(fd, buffer, BUFF_SIZE))
	{
		if (!buffer[BUFF_SIZE])
			EOF = 1;
		i = ft_findsubstrlen(buffer, '\n');
		count += i;
		ft_memcpy(*(tmp), buffer, i);
		**(++tmp);
		if (i < BUFF_SIZE)
		{
			*(buffer) = count;
			break;
		}
	}
	line[line_index] = ft_strnew(count);
	return (tmp);
}
/*
**	Copies processed line from read_line to **
*/
int		process_line(int fd, char **line, size_t line_index)
{
	int				EOF;
	size_t			i;
	char			**tmp;
	
	EOF = 0;
	i = 0;
	tmp = read_line(fd, line, line_index, EOF);
	while (**(tmp))
	{
		if (*(tmp) == '\n')
		{
			line[line_index][i] = '\0';
			return (0);
		}
		line[line_index][i++] = *(tmp++);
		if (!*(tmp))
			**(++tmp);
	}
	if (!EOF)
		return (0);
	return (1);
}
/*
**	Main function, runs checks and keeps track of line positon & file positon
*/
int		get_next_line(const int fd, char **line)
{
	static size_t	line_index;
	int rval;

	if (fd < 0 || !line)
		return (-1);
	rval = process_line(fd, line, line_index);
	if (rval == -1)
		return (-1);
	if (rval == 0)
		return (0);
	line_index = 0;
	return (1);
}

/*
**	Sudo Code
**	Start code defining indexes and strings. Read the file and run checks.
**	Returns are 1: Line read, 0: Finished Reading, -1: Error.
**	Reads one line then exits. Looping get_next_line will read multipule lines.
**	 
*/
