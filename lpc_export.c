extern int	lpc_int_check_storage(void);
extern void	lpc_int_errmsg(void);
extern int	lpc_int_enlarge_storage(void);
extern int	lpc_int_load(unsigned int priority, void *addr,
				void (*destroyer)(void *));

void	**lpc_int_storage(void)
{
	static void	*data;

	return (&data);
}

void	lpc_export(int priority, void *addr, void (*destroyer)(void *))
{
	int	check;

	check = lpc_int_check_storage();
	if (check == -1)
		return (lpc_int_errmsg());
	else if (check == 1 && lpc_int_enlarge_storage())
		return (lpc_int_errmsg());
	else if (lpc_int_load(priority, addr, destroyer))
		return (lpc_int_errmsg());
}
