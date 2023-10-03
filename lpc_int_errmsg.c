#include <unistd.h>

void	leakproof_errmsg(void)
{
	write(2, "The function you have called is having no memory at the moment.",
		53);
	write(2, "Please hold the addresses\n", 26);
}
