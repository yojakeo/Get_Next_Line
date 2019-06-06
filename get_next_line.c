/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: japarbs <japarbs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 01:32:33 by japarbs           #+#    #+#             */
/*   Updated: 2019/06/06 16:19:32 by japarbs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFCHECK	{*(buffer) = count; break;}
#define FREETMP	{free(*tmp); free(tmp);}

/*
**	Reads line from FD and places buffs to tmp, Allocating the total chars
**	needed to **line's current index. Returning tmp to be processed
**	(Coppied from **tmp to **line) by Process_line.
**	It is passed eof (Bollian) to signal if it is at End Of File.
**	cbl = Current Buffer Length.
*/

char	**read_line(int fd, char **line, size_t line_index, int eof)
{
	size_t			count;
	size_t			cbl;
	char			buffer[BUFF_SIZE];
	char			**tmp;

	count = 0;
	cbl = 0;
	if (!(tmp = (char **)malloc(sizeof(char *) * (MAX_BUFFS + 1))))
		return (NULL);
	while (read(fd, buffer, BUFF_SIZE))
	{
		if (!buffer[BUFF_SIZE - 1])
			eof = 1;
		cbl = ft_findsubstrlen(buffer, '\n');
		if (!(*(tmp) = (char *)ft_memalloc(cbl + 1)))
			return (NULL);
		count += cbl;
		ft_memcpy(*(tmp), buffer, cbl);
		(++tmp);
		if (cbl < BUFF_SIZE)
			BUFFCHECK;
	}
	line[line_index] = ft_strnew(count);
	return (tmp);
}

/*
**	Copies processed line from read_line to **line at the current index.
**	Converts the **tmp buffers to a single * for **line.
*/

int		process_line(int fd, char **line, size_t line_index)
{
	int				eof;
	size_t			i;
	char			**tmp;

	eof = 0;
	i = 0;
	tmp = read_line(fd, line, line_index, eof);
	while (tmp)
	{
		if (**(tmp) == '\n')
		{
			line[line_index][i] = '\0';
			return (0);
		}
		line[line_index][i++] = **(tmp++);
		if (!*(tmp))
			(++tmp);
	}
	FREETMP;
	if (!eof)
		return (0);
	return (1);
}

/*
**	Main function, runs checks and keeps track of line positon & file positon
*/

int		get_next_line(const int fd, char **line)
{
	static size_t	line_index;
	int				rval;

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
