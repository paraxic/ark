#ifndef ARK_PARSE_H
#define ARK_PARSE_H
#include "strfunc.h"
#include "aurpkg.h"
#include <jansson.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <malloc.h>

#define AUR_SEARCH 1
#define AUR_INFO 2
#define AUR_GET 3
#define AUR_BASE_URL "https://aur.archlinux.org/rpc/?v=5"

size_t aur_get(char * ptr, size_t size, size_t nmemb, void * user); // curl callback
void aur_search_data(char * keyword, int type, cdata * data); // grabs data using curl from AUR_BASE_URL
int aur_search_parse(char * data, aur_pkg_t * pkgs); // parse search info query into aur_pkg_t structs
int aur_info_parse(char * data, aur_pkg_t * pkgs); // parse info query into aur_pkg_t struct
void search_print(aur_pkg_t pkg); // pretty print for search queries
void info_print(aur_pkg_t pkg); // pretty print for info queries

#endif //ARK_PARSE_H
