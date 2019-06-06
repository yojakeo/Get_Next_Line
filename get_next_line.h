/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: japarbs <japarbs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 23:43:33 by japarbs           #+#    #+#             */
/*   Updated: 2019/06/06 16:19:54 by japarbs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 32
# define MAX_BUFFS 32

# include "libft/libft.h"

char	**read_line(int fd, char **line, size_t line_index, int eof);
int		process_line(int fd, char **line, size_t line_index);
int		get_next_line(const int fd, char **line);

#endif
