/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbreik <malbreik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:44:34 by malbreik          #+#    #+#             */
/*   Updated: 2025/07/01 09:29:26 by malbreik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	copy_and_free(char *dst, char *s1, char *s2, size_t *i)
{
	size_t	j;

	j = 0;
	while (s1 && s1[j])
	{
		dst[*i] = s1[j];
		(*i)++;
		j++;
	}
	free(s1);
	j = 0;
	while (s2 && s2[j])
	{
		dst[*i] = s2[j];
		(*i)++;
		j++;
	}
}

char	*ft_strjoin_mod(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = 0;
	len2 = 0;
	i = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	if (!s1 && !s2)
		return (NULL);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	copy_and_free(result, s1, s2, &i);
	result[i] = '\0';
	return (result);
}

static void	push_swap(t_stack **stack_a, t_stack **stack_b, int size)
{
	if (size == 2 && !is_sorted(*stack_a))
		do_sa(stack_a);
	else if (size == 3)
		tiny_sort(stack_a);
	else if (size > 3 && !is_sorted(*stack_a))
		sort(stack_a, stack_b);
}

static void	cleanup_and_exit(char **s, t_stack **a, t_stack **b)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	free_stack(a);
	free_stack(b);
}

int	main(int ac, char **av)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char	**s;
	int		size;

	if (ac < 2)
		return (0);
	s = parse_and_validate_input(av);
	stack_b = NULL;
	stack_a = fill_stack_values(count_tokens_array(s), s);
	size = get_stack_size(stack_a);
	assign_index(stack_a, size + 1);
	push_swap(&stack_a, &stack_b, size);
	cleanup_and_exit(s, &stack_a, &stack_b);
	return (0);
}
