/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: japarbs <japarbs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 01:32:33 by japarbs           #+#    #+#             */
/*   Updated: 2019/06/07 17:37:25 by japarbs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**	Reads line from FD and joins the current buff and current index of **line,
**	allocating the chars as it reads, allowing for dynamic string len.
**	eof (Bollean) is a signal for End Of File. If the read buff is less
**	than BUFF_SIZE then eof is triggered and will return 1 (complete read).
**	cbl = Current Buffer Length.
*/

int		read_line(int fd, char **line, char **fdarr)
{
	int				bres;
	int				eof;
	char			buffer[BUFF_SIZE + 1];
	char			*tmp;

	eof = 0;
	while ((bres = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[bres] = '\0'
		if (!bres)
			eof = 1;
		if (!(line[line_index] = ft_strjoin(line[line_index], buffer)))
			return (-1);
		if (ft_strdlen(buffer, '\n') < BUFF_SIZE)
			break;
	}
	if (!eof)
		return (0);
	return (1);
}

/*
**	'home' function, runs return checks and keeps track of current  & file positon
**	MAX_FD is the total ammount of FDs get_next_line can handle (defined in .h)
*/

int		get_next_line(const int fd, char **line)
{
	static char	*fdarr[MAX_FD];
	int				rval;

	if (fd == -1 || !line || (rval = read_line(fd, line, fdarr) == -1))
		return (-1);
	if (rval == 0)
		return (0);
	return (1);
}
