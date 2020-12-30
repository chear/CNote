#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h>

typedef unsigned int	   u_int32_t; 
#define prom_printf printf

#define PARTS_SIZE 512
#define SIZE_REMAINING UINT_MAX
#define SIZE_TO_GET (UINT_MAX-1)
#define OFFSET_CONTINUOUS UINT_MAX
#define OFFSET_BACK_FORWARD (UINT_MAX-1)
#define OFFSET_NOT_FOUND UINT_MAX 

#define PAGE_SHIFT  12
#define PAGE_SIZE   (1UL << PAGE_SHIFT)
#define PAGE_MASK   (~(PAGE_SIZE-1))

struct mtd_partition {
        char *name;             /* identifier string */
        u_int32_t size;         /* partition size */
        u_int32_t offset;       /* offset within the master MTD space */
        u_int32_t mask_flags;   /* master MTD flags to mask out for this partition */
};
struct mtd_partition *ecnt_parts;
int num_parts;
static char parts_size[PARTS_SIZE];
static int has_remaining_part_flag = 0;
 
#define PARTITIONS_CMDLINE_STR "30m[Tclinux_main],30m[tclinux],256k[second_romfile],128k[romd],256k[hwconfig],4m[log],18m[app]"
 
 
#define TCLINUX "Tclinux_main"
#define TCLINUX_SLAVE "tclinux"
#define TCLINUX_REAL_SIZE "tclinux_real_size"
#define TCLINUX_SLAVE_REAL_SIZE "tclinux_slave_real_size"
#define RESERVEAREA "reservearea"
#define KERNEL_PART "kernel"
#define ROOTFS_PART "rootfs"
#define KERNEL_SLAVE_PART "kernel_slave"
#define ROOTFS_SLAVE_PART "rootfs_slave"
#if 1 
#define BOOTLOADER_PART "bootloader"
#endif
#define ROMFILE_PART "romfile"
#define BOOTLOADER_PART_STR "0[bootloader],"
#define ROMFILE_PART_STR "0[romfile],"


/*
 * Parse one partition definition for an MTD. Since there can be many
 * comma separated partition definitions, this function calls itself
 * recursively until no more partition definitions are found. Nice side
 * effect: the memory to keep the mtd_partition structs and the names
 * is allocated upon the last definition being found. At that point the
 * syntax has been verified ok.
 */
static struct mtd_partition * ecnt_newpart(char *s, char **retptr,int *num_parts,
                                      int this_part,unsigned char **extra_mem_ptr,
                                      int extra_mem_size, unsigned int blocksize)
{
	struct mtd_partition *parts;
	unsigned long size = SIZE_TO_GET;
	unsigned long offset = OFFSET_CONTINUOUS;
	char *name;
	int name_len;
	unsigned char *extra_mem;
	char delim;
	unsigned int mask_flags;

	/* fetch the partition size */
	if (*s == '-'){	
		if(has_remaining_part_flag == 0){
			/* assign all remaining space to this partition */
			size = SIZE_REMAINING;
			has_remaining_part_flag = 1;
			s++;
		}
		else{
			printf( "no fill-up partitions allowed after already having a fill-up partition\n");
			return NULL;
		}
	}
	
	else{
		size = ecnt_memparse(s, &s, blocksize);
		if(size == 0)
			size = SIZE_TO_GET;
		if (size < PAGE_SIZE){
			printf( "partition size too small (%lx)\n", size);
			return NULL;
		}
	}

	/* fetch partition name and flags */
	mask_flags = 0; /* this is going to be a regular partition */
	delim = 0;
	
        /* now look for name */
	if (*s == '['){
		delim = ']';
	}

	if (delim){
		char *p;

	    	name = ++s;
		p = strchr(name, delim);
		if (!p){
			printf( "no closing %c found in partition name\n", delim);
			return NULL;
		}
		name_len = p - name;
		s = p + 1;
	}
	else{
	    	name = NULL;
		name_len = 13; /* Partition_000 */
	}

	/* record name length for memory allocation later */
	extra_mem_size += name_len + 1;

	/* offset type is append */
        if (strncmp(s, "a", 1) == 0){
		offset = OFFSET_CONTINUOUS;
		s += 1;
        }

        /* offset type is back forward*/
        if (strncmp(s, "end", 3) == 0){
		offset = OFFSET_BACK_FORWARD;
		s += 3;
        }
	
	/* test if more partitions are following */
	if (*s == ','){
#if 1		
		if(!strncmp(name, TCLINUX, name_len)){
			this_part += 2;
			extra_mem_size +=strlen(KERNEL_PART)+strlen(ROOTFS_PART)+2;
		}
		else if(!strncmp(name, TCLINUX_SLAVE, name_len)){
			this_part += 2;
			extra_mem_size +=strlen(KERNEL_SLAVE_PART)+strlen(ROOTFS_SLAVE_PART)+2;
		}
#endif
		/* more partitions follow, parse them */
		parts = ecnt_newpart(s + 1, &s, num_parts, this_part + 1,
				&extra_mem, extra_mem_size, blocksize);
		if (!parts)
			return NULL;
	}
	else{	/* this is the last partition: allocate space for all */
		int alloc_size;
#if 1
		if(!strncmp(name, TCLINUX, name_len)){
			this_part += 2;
			extra_mem_size +=strlen(KERNEL_PART)+strlen(ROOTFS_PART)+2;
		}
		else if(!strncmp(name, TCLINUX_SLAVE, name_len)){
			this_part += 2;
			extra_mem_size +=strlen(KERNEL_SLAVE_PART)+strlen(ROOTFS_SLAVE_PART)+2;
		}
		
		*num_parts = this_part + 2; /*add reservearea partition*/
		extra_mem_size += strlen(RESERVEAREA)+1;
#endif
		alloc_size = *num_parts * sizeof(struct mtd_partition) +
			     extra_mem_size;
		parts = parts_size;
	
		if(alloc_size > PARTS_SIZE){
			prom_printf("out of memory\n");
			return NULL;
		}
		extra_mem = (unsigned char *)(parts + *num_parts);
	}
	/* enter this partition (offset will be calculated later if it is zero at this point) */
	parts[this_part].size = size;
	parts[this_part].offset = offset;
	parts[this_part].mask_flags = mask_flags;
	if (name){
		strncpy(extra_mem, name, name_len);
	}
	else{
		sprintf(extra_mem, "Partition_%03d", this_part);
	}
	parts[this_part].name = extra_mem;
	extra_mem += name_len + 1;
#if 1
	if(!strcmp(parts[this_part].name, TCLINUX)){
		ecnt_newpart_set_other_parts(&parts[this_part-2],TCLINUX, this_part-2, blocksize);
	}
	else if(!strcmp(parts[this_part].name, TCLINUX_SLAVE)){
		ecnt_newpart_set_other_parts(&parts[this_part-2],TCLINUX_SLAVE, this_part-2, blocksize);
	}
	if(this_part == (*num_parts -2)){
		ecnt_newpart_set_other_parts(&parts[*num_parts -1], RESERVEAREA, *num_parts -1, blocksize);
	}
#endif

	printf("partition %d: name <%s>, offset %x, size %x, mask flags %x\n",this_part, parts[this_part].name,
	     parts[this_part].offset, parts[this_part].size, parts[this_part].mask_flags);

	/* return (updated) pointer to extra_mem memory */
	if (extra_mem_ptr)
	  *extra_mem_ptr = extra_mem;

	/* return (updated) pointer command line string */
	*retptr = s;

	/* return partition table */
	return parts;
}

static void ecnt_check_mtdpart_str(char *dst, char *src){
	int have_bootloader_part = 0;
	int have_romfile_part = 0;
	char *bootloader_p = NULL;
	char *bootloader_end_p = NULL;
	
	if(bootloader_p = strstr(src, BOOTLOADER_PART)){
		have_bootloader_part = 1;
	}
	if(strstr(src, ROMFILE_PART)){
		have_romfile_part = 1;
	}

	if(have_romfile_part && have_bootloader_part){
		strcpy(dst, src);
	}
	else if(!have_romfile_part && !have_bootloader_part){
		strcpy(dst, BOOTLOADER_PART_STR);
		strcat(dst, ROMFILE_PART_STR);
		strcat(dst, src);
	}
	else if(have_romfile_part && !have_bootloader_part){
		strcpy(dst, BOOTLOADER_PART_STR);
		strcat(dst, src);
	}
	else if(!have_romfile_part && have_bootloader_part){
		bootloader_end_p = strchr(bootloader_p, ',');
		if(!bootloader_end_p)
			prom_printf("cmdline, bootloader partition error!\n");
		memcpy(dst, src, bootloader_end_p - src+1);
		strcat(dst, ROMFILE_PART_STR);
		strcat(dst, bootloader_end_p+1);
	}
	
}

int main (int argc, char **argv){

	char cmdline[256];
	unsigned char *extra_mem;
	char *p;
	char *s;
	
	
	sprintf(s,"%s", PARTITIONS_CMDLINE_STR);
	ecnt_check_mtdpart_str(cmdline, s);
	printf("cmdline = %s \n",cmdline);
	
	/*
	 * parse one mtd. have it reserve memory for the
	 * struct cmdline_mtd_partition and the mtd-id string.
	 */
	ecnt_parts = ecnt_newpart(p,		/* cmdline */
			&s,		/* out: updated cmdline ptr */
			&num_parts,	/* out: number of parts */
			0,		/* first partition */
			&extra_mem, /* out: extra mem */
			 0, blocksize);
	if(!ecnt_parts)
	{
		/*
		 * An error occurred. We're either:
		 * a) out of memory, or
		 * b) in the middle of the partition spec
		 * Either way, this mtd is hosed and we're
		 * unlikely to succeed in parsing any more
		 */
		 return 0;
	 }	
	 
	 
	 
	printf("======== Test Finish ========");
	return 0;
}


	
	
	