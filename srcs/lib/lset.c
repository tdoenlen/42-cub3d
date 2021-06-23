#include "cub3d.h"

int	lset_add(t_lset **lset, int new_val)
{
	t_lset	**last;

	last = lset;
	while (*last)
	{
		if ((*last)->val == new_val)
			return (1);
		last = (t_lset **)&((*last)->next);
	}
	*last = malloc(sizeof(**last));
	if (*last == NULL)
		return (print_err("allocation failed -> abort new input addition"));
	(*last)->val = new_val;
	(*last)->next = NULL;
	printf("+%d\n", new_val);
	return (0);
}

int	lset_rm(t_lset **lset, int rm_val)
{
	t_lset	*ptr;
	t_lset	*prev;

	prev = *lset;
	ptr = *lset;
	while (ptr && ptr->val != rm_val)
	{
		prev = ptr;
		ptr = ptr->next;
	}
	if (ptr == NULL)
		return (1);
	prev->next = ptr->next;
	if (ptr == prev)
		*lset = ptr->next;
	free(ptr);
	printf("-%d\n", rm_val);
	return (0);
}

int	lset_has_val(t_lset *lset, int val)
{
	while (lset && lset->val != val)
		lset = lset->next;
	if (lset)
		return (1);
	return (0);
}

void	lset_clear(t_lset **lset)
{
	t_lset	*next;

	while (*lset)
	{
		next = (*lset)->next;
		free(*lset);
		*lset = next;
	}
}
