#include <libft.h>

#include <libft.h>

void	ft_free_char_arr(char ***arr)
{
	int	i;

	i = 0;
	if (arr && *arr)
	{
		while ((*arr)[i])
		{
			free((*arr)[i]);
			(*arr)[i] = NULL;
			i++;
		}
		free(*arr);
		*arr = NULL;
	}
}
