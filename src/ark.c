#include "ark.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>


int main(int argc, char * argv[]){
int opt = 0;
if(argc < 3){
 fprintf(stderr,"usage: ark [-s/-i] keywords\n");
 exit(0);
}
if( strcmp(argv[1],"-s") == 0 || strcmp(argv[1], "--search") == 0){
 opt = AUR_SEARCH;
} else if ( strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--info") == 0) {
 opt = AUR_INFO;
}
aur_pkg_t pkgs[500];
char data[1024 * 4];
for(size_t i = 0; i < (1024 * 4); i++){
data[i] = 0;
}
if (opt == AUR_SEARCH) {
 aur_search_data(argv[2], opt, data);
 aur_search_parse(data, pkgs);
 int pkg_count = pkgs[0].pkg_count;
 for(size_t i = 0; i < pkg_count; i++){
   search_print(pkgs[i]);
 }
} else if ( opt == AUR_INFO ){
 aur_search_data(argv[2], opt, &data);
 aur_info_parse(data, pkgs);
 info_print(pkgs[0]);
}

return 0;
}
