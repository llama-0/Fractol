#include <libft.h>

void	ft_putstr_base(char const *s, int out)
{
	size_t i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i])
	{
		ft_putchar_base(s[i], out);
		i++;
	}
}
