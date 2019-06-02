/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: japarbs <japarbs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 01:32:33 by japarbs           #+#    #+#             */
/*   Updated: 2019/06/02 04:18:51 by japarbs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	**read_line(int fd, char **line, size_t line_index)
{
	int				EOF;
	size_t			count;
	size_t			i;
	char			buffer[BUF_SIZE];
	char			tmp[MAX_BUFFS][BUF_SIZE + 1];

	count = 0;
	i = 0;
	EOF = 0;
	while (read(fd, buffer, BUF_SIZE))
	{
		if (!buffer[BUF_SIZE])
			EOF = 1;
		i = ft_findsubstrlen(buffer, '\n');
		count += i;
		ft_memcpy(**(tmp), buffer, i);
		tmp++;
		if (i < BUF_SIZE)
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
	size_t			i;
	int				EOF;
	i = 0;
	while (count)
	{
		if (buffer[i] == '\n')
		{
			line[line_index][i] = '\0';
			return (0);
		}
		line[line_index][i] = buffer[i++];
		--count;
	}
	if (!count && !EOF)
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
