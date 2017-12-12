#include <stdio.h>

typedef struct	s_link {
	struct s_link	*prev;
	int				n;
	struct s_link	*next;
}				t_link;

void	push_a(t_link **stack_a, t_link **stack_b)
{
	t_link	*tmp;
	t_link	*lastb;

	if (*stack_b)
	{
		if (*stack_a)
			tmp = test_create_link((*stack_a)->prev, (*stack_b)->n, (*stack_a));
		else
			tmp = test_create_link(NULL, (*stack_b)->n, NULL);
		(*stack_a) = tmp;
		if ((*stack_a)->next)
			(*stack_a)->next->prev = (*stack_a);
		tmp = NULL;
		if ((*stack_b)->next)
			tmp = test_create_link((*stack_b)->prev, (*stack_b)->next->n, (*stack_b)->next->next);
		free(*stack_b);
		(*stack_b) = tmp;
	}
}

int
main(void)
{
	t_link
}