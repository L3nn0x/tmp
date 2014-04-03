
#ifndef FS_H
# define FS_H

# include <stdio.h>

typedef struct	s_fat_extBS_16 {
	unsigned char	bios_drive_num;
	unsigned char	reserved1;
	unsigned char	boot_signature;
	unsigned char	volume_id;
	unsigned char	volume_label[11];
	unsigned char	fat_type_label[8];
}__attribute__((packed)) fat_extBS_16;

typedef struct	s_fat_BS {
	unsigned char	bootjmp[3];
	unsigned char	oem_name[8];
	unsigned short	bytes_per_sector;
	unsigned char	sectors_per_cluster;
	unsigned short	reserved_sector_count;
	unsigned char	table_count;
	unsigned short	root_entry_count;
	unsigned short	total_sectors_16;
	unsigned char	media_type;
	unsigned short	table_size_16;
	unsigned short	sectors_per_track;
	unsigned short	head_side_count;
	unsigned int	hidden_sector_count;
	unsigned int	total_sectors_32;
	unsigned char	extended_section[54];
}__attribute__((packed)) fat_BS;

typedef struct	s_fs {
	FILE			*hdd;
	fat_BS			*bs;
	fat_extBS_16	*ext;
	unsigned int	root_dir_sectors;
	unsigned int	first_data_sector;
	unsigned int	first_fat_sector;
	unsigned int	data_sectors;
	unsigned int	total_clusters;
	unsigned int	fat_type;
}				t_fs;

t_fs	*open_fs(const char *filename);
void	close_fs(t_fs	*fs);

#endif /* !FS_H */
