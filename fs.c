#include <stdlib.h>
#include <stdio.h>
#include "fs.h"

t_fs	*open_fs(const char *filename)
{
	t_fs	*tmp;

	tmp = malloc(sizeof(*tmp));
	tmp->hdd = fopen(filename, "rb+");
	tmp->bs = malloc(sizeof(fat_BS));
	tmp->ext = malloc(sizeof(fat_extBS_16));
	fread(tmp->bs, sizeof(fat_BS), 1, tmp->hdd);
	fread(tmp->ext, sizeof(fat_extBS_16), 1, tmp->hdd);
	tmp->root_dir_sectors = ((tmp->bs->root_entry_count * 32) + (tmp->bs->bytes_per_sector - 1)) / tmp->bs->bytes_per_sector;
	tmp->first_data_sector = tmp->bs->reserved_sector_count + (tmp->bs->table_count * tmp->bs->table_size_16);
	tmp->first_fat_sector = tmp->bs->reserved_sector_count;
	tmp->data_sectors = tmp->bs->total_sectors_16 - (tmp->bs->reserved_sector_count + (tmp->bs->table_count * tmp->bs->table_size_16) + tmp->root_dir_sectors);
	tmp->total_clusters = tmp->data_sectors / tmp->bs->sectors_per_cluster;
	tmp->fat_type = 32;
	if (tmp->total_clusters < 4085)
		tmp->fat_type = 12;
	else
		if (tmp->total_clusters < 65525)
			tmp->fat_type = 16;
	printf("oem name : %s\n", tmp->bs->oem_name);
	return (tmp);
}

void	close_fs(t_fs	*fs)
{
	fclose(fs->hdd);
	free(fs->bs);
	free(fs->ext);
	free(fs);
}
