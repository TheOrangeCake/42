#include "ft_printf.h"
#include <stdio.h>

int	main(void)
{
	char	c = 'c';
	char	*str;;
	int		i = 0;
	int		a;
	int		b;

	str = malloc(10);
	str = NULL;

	a = ft_printf("%c\n%s\n%p\n%dtest\n%i\n%u%u\n%x\n%X\n%%\n", c, str, str, i, i, i, i, i, i);
	printf("Total: %d\n", a);
	b = printf("%c\n%s\n%p\n%dtest\n%i\n%u%u\n%x\n%X\n%%\n", c, str, str, i, i, i, i, i, i);
	printf("Total: %d\n", b);
	return (0);
}

//use: gcc test.c -L. -lftprintf -o a.out