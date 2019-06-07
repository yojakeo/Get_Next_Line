/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: japarbs <japarbs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 01:32:33 by japarbs           #+#    #+#             */
/*   Updated: 2019/06/06 20:23:01 by japarbs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFCHECK	{*(buffer) = count; break;}

/*
**	Reads line from FD and joins the current buff and current index of **line,
**	allocating the chars as it reads, allowing for dynamic string len.
**	eof (Bollean) is a signal for End Of File. If the read buff is less
**	than BUFF_SIZE then eof is triggered and will return 1 (for complete read).
**	cbl = Current Buffer Length.
*/

int		read_line(int fd, char **line, size_t line_index)
{
	size_t			cbl;
	size_t			i;
	int				eof;
	char			buffer[BUFF_SIZE];

	i = 0;
	eof = 0;
	cbl = 0;
	while (read(fd, buffer, BUFF_SIZE))
	{
		if (!buffer[BUFF_SIZE - 1])
			eof = 1;
		cbl = ft_findsubstrlen(buffer, '\n');
		if (!(line[line_index] = ft_strjoin(line[line_index], buffer)))
			return (-1);
	}
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
	rval = read_line(fd, line, line_index);
	if (rval == -1)
		return (-1);
	if (rval == 0)
		return (0);
	line_index = 0;
	return (1);
}
