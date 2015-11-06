#include <sys/statfs.h>
#include <stdio.h>
#include <string.h>

static const char *human_fstype(unsigned int f_type)
{
	static const struct types {
		unsigned int type;
		const char *const fs;
	} humantypes[] = {
		{ 0xADFF,     "affs" },
		{ 0x1Cd1,     "devpts" },
		{ 0x137D,     "ext" },
		{ 0xEF51,     "ext2" },
		{ 0xEF53,     "ext2/ext3" },
		{ 0x3153464a, "jfs" },
		{ 0x58465342, "xfs" },
		{ 0xF995E849, "hpfs" },
		{ 0x9660,     "isofs" },
		{ 0x4000,     "isofs" },
		{ 0x4004,     "isofs" },
		{ 0x137F,     "minix" },
		{ 0x138F,     "minix (30 char.)" },
		{ 0x2468,     "minix v2" },
		{ 0x2478,     "minix v2 (30 char.)" },
		{ 0x4d44,     "msdos/vfat/fat32" },
		{ 0x4006,     "fat" },
		{ 0x564c,     "novell" },
		{ 0x6969,     "nfs" },
		{ 0x9fa0,     "proc" },
		{ 0x517B,     "smb" },
		{ 0x012FF7B4, "xenix" },
		{ 0x012FF7B5, "sysv4" },
		{ 0x012FF7B6, "sysv2" },
		{ 0x012FF7B7, "coh" },
		{ 0x00011954, "ufs" },
		{ 0x012FD16D, "xia" },
		{ 0x5346544e, "ntfs" },
		{ 0x65735446, "ntfs/fuseblk" },
		{ 0x1021994,  "tmpfs" },
		{ 0x52654973, "reiserfs" },
		{ 0x28cd3d45, "cramfs" },
		{ 0x7275,     "romfs" },
		{ 0x858458f6, "romfs" },
		{ 0x73717368, "squashfs" },
		{ 0x62656572, "sysfs" },
		{ 0x2011bab0, "exfat" },
		{ 0x794c764f, "overlayfs"},
		{ 0x64626720, "debugfs" },
		{ 0x726b,     "jffs2" },
		{ 0, "UNKNOWN" }
	};

	int i;

	for (i = 0; humantypes[i].type; ++i)
		if (humantypes[i].type == f_type)
			break;
	return humantypes[i].fs;
}

static void printf_usage()
{
	char* usage = "\nUsage: fmtsd <filepath>\n";
	printf("%s", usage);
}

int main(int argc, char** argv)
{
#define BUF_SIZE 30
	struct statfs fsbuf;
	char path[BUF_SIZE] = {0};
	char fstype[BUF_SIZE] = {0};

	if (argc < 2)
	{
		printf_usage();
		return 0;
	}

	strcpy(path, argv[1]);
	if (strlen(path) < 1)
		strcpy(path, "/tmp");

	if (statfs(path, &fsbuf) != 0)
	{
		perror("get statfs failed\n");
		return -1;
	}

	strcpy(fstype, human_fstype(fsbuf.f_type));
	printf("%s file system type is: 0x%x - %s\n", path, (unsigned int)fsbuf.f_type, fstype);
	return 0;
}
