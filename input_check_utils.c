/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbreik <malbreik@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:25:28 by mcombeau          #+#    #+#             */
/*   Updated: 2025/06/30 19:22:36 by malbreik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_digit(char c)
{
	return ((c >= '0' && c <= '9') || c == 32);
}

int	is_sign(char c)
{
	return (c == '+' || c == '-');
}

int	nbstr_cmp(const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = i;
	if (s1[i] == '+')
	{
		if (s2[j] != '+')
			i++;
	}
	else
	{
		if (s2[j] == '+')
			j++;
	}
	while (s1[i] != '\0' && s2[j] != '\0' && s1[i] == s2[j])
	{
		i++;
		j++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}

int	count_tokens_array(char **s)
{
	int	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

char	**parse_and_validate_input(char **av)
{
	char	*str;
	char	**s;
	int		i;

	str = NULL;
	i = 0;
	while (av[i])
	{
		str = ft_strjoin_mod(str, av[i]);
		str = ft_strjoin_mod(str, " ");
		i++;
	}
	s = ft_split(str, ' ');
	if (!s)
		exit_error(NULL, NULL, NULL);
	free(str);
	if (!is_correct_input(s))
		exit_error(NULL, NULL, s);
	return (s);
}
