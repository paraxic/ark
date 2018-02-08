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
#define AUR_BASE_URL "https://aur.archlinux.org/rpc/?v=5"

size_t aur_get(char * ptr, size_t size, size_t nmemb, void * user){
//we're gonna exfil the data so that we can put it into our own type instead of doing all the work
//here in this function;
if((size * nmemb) == 0){ fprintf(stderr,"aur_get: No Data"); return 0;}
 size_t data_size = (nmemb * size) + 1;
 char curl_data[data_size];
 strncat(curl_data, ptr, data_size - 1);
 curl_data[data_size] = '\0';
 strncpy((char*) user, curl_data, data_size  + 1);
 printf("================================================================================\n");
 printf("%s\n",curl_data);
 printf("================================================================================\n");
return data_size - 1;
}

void aur_search_data(char * keyword, int type, char ** data ){
 CURL * cfetch;
 CURLcode cerror;
 curl_global_init(CURL_GLOBAL_DEFAULT | CURL_GLOBAL_SSL);
 cfetch = curl_easy_init();
 char * request = AUR_BASE_URL;
 if(type == AUR_SEARCH){
   request = sf_word_prefix(request,"&type=search");
 } else if(type == AUR_INFO){
   request = sf_word_prefix(request,"&type=info");
 }
 request = sf_word_prefix(request,sf_word_prefix("&arg=",keyword));
 printf("CURL REQUEST: %s\n",request);
 if(cfetch){
 	curl_easy_setopt(cfetch, CURLOPT_URL, request);
	curl_easy_setopt(cfetch, CURLOPT_WRITEFUNCTION, aur_get);
	curl_easy_setopt(cfetch, CURLOPT_WRITEDATA, (void *) *data);
	cerror = curl_easy_perform(cfetch);
	if(cerror != CURLE_OK){
		fprintf(stderr,"curl error: %s\n", curl_easy_strerror(cerror));
	}
	curl_easy_cleanup(cfetch);
 }
}


#define jstrcpy(x,y) strncpy(x,json_string_value(y),strlen(json_string_value(y)));
#define jog(x,y) pkginfo = json_object_get(y,x);
int aur_search_parse(char * data, aur_pkg_t ** pkgs){
 printf("\n\nDATA: %s\n\n",data);
 json_t * root;
 json_error_t error;
 root = json_loads(data,0,&error);
 if(!root){
	fprintf(stderr,"json: error on line %d: %s\n",error.line, error.text);
	return 0;
 }
 json_t * cdata = json_object_get(root,"resultcount");
 int pkg_count = (int)json_integer_value(cdata);
 if(pkg_count == 0){
	fprintf(stderr,"No packages found\n");
	return 0;
 }
 pkgs[0]->pkg_count = pkg_count;
 json_t * results = json_object_get(root,"results");
 json_t * pkginfo;
 for(size_t i = 0; i < pkg_count; i++){
  cdata = json_array_get(results,i);
  jog("Name",cdata);
  jstrcpy(pkgs[i]->name,pkginfo);
  jog("Version",cdata);
  jstrcpy(pkgs[i]->version,pkginfo);
  jog("Description",cdata);
  jstrcpy(pkgs[i]->description,pkginfo);
 }
 return 1; 
} 

int aur_info_parse(char * data, aur_pkg_t ** pkgs){
 json_t * root;
 json_error_t error;
 root = json_loads(data,0,&error);
 if(!root){
	fprintf(stderr,"json: error on line %d: %s\n",error.line, error.text);
	return 0;
 }
 json_t * cdata = json_object_get(root,"resultcount");
 int pkg_count = (int)json_integer_value(cdata);
 if(pkg_count == 0){
	fprintf(stderr,"No packages found\n");
	return 0;
 }
 json_t * results = json_object_get(root,results);
 json_t * pkginfo;
  cdata = json_array_get(results,0);
  jog("Name",cdata);
  jstrcpy(pkgs[0]->name,pkginfo);
  jog("Version",cdata);
  jstrcpy(pkgs[0]->version,pkginfo);
  jog("Maintainer",cdata);
  jstrcpy(pkgs[0]->maintainer,pkginfo);
  jog("Description",cdata);
  jstrcpy(pkgs[0]->description,pkginfo);
  jog("Conflicts",cdata);
  jstrcpy(pkgs[0]->pacinfo.conflicts,pkginfo);
  jog("Depends",cdata);
  jstrcpy(pkgs[0]->pacinfo.depends,pkginfo);
  jog("License",cdata);
  jstrcpy(pkgs[0]->pacinfo.license,pkginfo);
  jog("URL",cdata);
  jstrcpy(pkgs[0]->url,pkginfo);
 return 1; 
} 

void search_print(aur_pkg_t pkg){
 printf("aur/%s %s\t (%s)\n%s\n",pkg.name,pkg.version,pkg.maintainer,pkg.description);
}

void info_print(aur_pkg_t pkg){
 printf("Name: %s\nVersion: %s\nDescription: %s\nMaintainer: %s\nURL: %s\n",pkg.name,pkg.version,pkg.description,pkg.maintainer,pkg.url);
}

#endif //ARK_PARSE_H
