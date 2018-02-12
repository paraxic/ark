#include "aurpkg.h"

void aur_print(aur_pkg_t pkg){
 printf("Name: %s %s\nDesc: %s\nMaintainer: %s\nDepends: %s\nConflicts: %s\nLicense: %s\nURL: %s\n",
	pkg.name, pkg.version,
	pkg.description, pkg.maintainer,
	pkg.pacinfo.depends, pkg.pacinfo.conflicts,
	pkg.pacinfo.license, pkg.url );
}
