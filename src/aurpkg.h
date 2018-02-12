#ifndef AURPKG_H
#define AURPKG_H
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <time.h>

struct aur_pkg_t
{
	int pkg_count;
	char * name;
	char * description;
	char * version;
	char * maintainer;
	struct pacinfo {
		char * depends;
		char * conflicts;
		char * license;
	}pacinfo;
	char * url;
	char * urlpath;
	time_t submitted;
	time_t modified;
	time_t out_of_date;
};

typedef struct aur_pkg_t aur_pkg_t;

void aur_print(aur_pkg_t pkg); // pretty print for aur pkgs

#endif // AURPKG_H
