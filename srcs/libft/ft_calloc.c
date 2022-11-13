#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*calloc;
	size_t	total;
	int		i;

	i = 0;
	total = count * size;
	calloc = malloc(total);
	if (!calloc)
		return (0);
	while (total--)
		calloc[i++] = '\0';
	return ((void *) calloc);
}