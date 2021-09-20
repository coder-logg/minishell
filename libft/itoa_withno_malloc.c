unsigned long long	get_unsigned(long long n)
{
	unsigned long	un;

	un = n;
	if (n < 0)
	{
		un = ~un;
		un++;
	}
	return (un);
}

int	digit_nbr(long n)
{
	int				i;
	unsigned long	unl;

	if (n == 0)
		return (1);
	i = 0;
	if (n < 0)
		i++;
	unl = get_unsigned(n);
	while (unl > 0)
	{
		i++;
		unl /= 10;
	}
	return (i);
}

char	*itoa_withno_malloc(char *dst, long long n)
{
	unsigned int	tmp_un;
	int				dnbr;

	if (dst == (void *)0)
		return ((void *)0);
	tmp_un = n;
	if (n < 0)
	{
		dst[0] = '-';
		tmp_un = get_unsigned(n);
	}
	else
		dst[0] = 0;
	dnbr = digit_nbr(n);
	dst[dnbr] = 0;
	while (dnbr > 0 + (dst[0] == '-'))
	{
		dnbr--;
		dst[dnbr] = tmp_un % 10 + '0';
		tmp_un /= 10;
	}
	return (dst);
}
