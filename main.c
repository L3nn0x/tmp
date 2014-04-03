#include <stdio.h>
#include <stdlib.h>
#include "fs.h"

int	main()
{
	t_fs	*hdd;

	hdd = open_fs("c.img");
	printf("hdd opened\n");

	close_fs(hdd);
	return (0);
}
