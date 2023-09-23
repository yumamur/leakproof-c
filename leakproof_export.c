extern int	leakproof_check_storage(void);
extern void	leakproof_errmsg(void);
extern int	leakproof_enlarge_storage(void);
extern int	leakproof_load(void *addr, void (*destroyer)(void *));

void	**leakproof_storage(void)
{
	static void	*data;

	return (&data);
}

void	leakproof_export(void *addr, void (*destroyer)(void *))
{
	int	check;

	check = leakproof_check_storage();
	if (check == -1)
		return (leakproof_errmsg());
	else if (check == 1 && leakproof_enlarge_storage())
		return (leakproof_errmsg());
	else if (leakproof_load(addr, destroyer))
		return (leakproof_errmsg());
}
