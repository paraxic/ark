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


void aur_print(aur_pkg_t pkg){
	printf("Name: %s %s\nDesc: %s\nMaintainer: %s\nDepends: %s\nConflicts: %s\nLicense: %s\nURL: %s\n",
			pkg.name, pkg.version,
			pkg.description, pkg.maintainer,
			pkg.pacinfo.depends, pkg.pacinfo.conflicts,
			pkg.pacinfo.license, pkg.url );
}

#endif // AURPKG_H
