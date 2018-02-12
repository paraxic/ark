#include "arkparse.h"

size_t aur_get(char * ptr, size_t size, size_t nmemb, void * user){
//we're gonna exfil the data so that we can put it into our own type instead of doing all the work
//here in this function;
if((size * nmemb) == 0){ fprintf(stderr,"aur_get: No Data"); return 0;}
 size_t data_size = (nmemb * size);
 strncpy((char*)user, ptr, data_size);
return data_size;
}

void aur_search_data(char * keyword, int type, char * data ){
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
 #ifdef ARK_DEBUG
  printf("CURL REQUEST: %s\n",request);
 #endif 
 if(cfetch){
 	curl_easy_setopt(cfetch, CURLOPT_URL, request);
	curl_easy_setopt(cfetch, CURLOPT_WRITEFUNCTION, aur_get);
	curl_easy_setopt(cfetch, CURLOPT_WRITEDATA, (void *) data);
	cerror = curl_easy_perform(cfetch);
	if(cerror != CURLE_OK){
		fprintf(stderr,"curl error: %s\n", curl_easy_strerror(cerror));
	}
	curl_easy_cleanup(cfetch);
 }
}


int aur_search_parse(char * data, aur_pkg_t * pkgs){
 #ifdef ARK_DEBUG
   printf("================================================================================\n"); 
   printf("DATA:\n%s\n",data);
   printf("================================================================================\n");
 #endif
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
 pkgs[0].pkg_count = pkg_count;
 json_t * results = json_object_get(root,"results");
 json_t * pkginfo;
 for(size_t i = 0; i < pkg_count; i++){
  cdata = json_array_get(results,i);
  pkginfo = json_object_get(cdata, "Name");
  pkgs[i].name = malloc(sizeof(char) * (int)strlen(json_string_value(pkginfo)));
  strncpy(pkgs[i].name, json_string_value(pkginfo),strlen(json_string_value(pkginfo)));
  pkginfo = json_object_get(cdata,"Version");
  pkgs[i].version = malloc(sizeof(char) * (int)strlen(json_string_value(pkginfo)));
  strncpy(pkgs[i].version, json_string_value(pkginfo), strlen(json_string_value(pkginfo)));
  pkginfo = json_object_get(cdata,"Description");
  pkgs[i].description = malloc(sizeof(char) * (int)strlen(json_string_value(pkginfo)));
  strncpy(pkgs[i].description, json_string_value(pkginfo), strlen(json_string_value(pkginfo)));
 }
 return 1; 
} 

int aur_info_parse(char * data, aur_pkg_t * pkgs){
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
	fprintf(stderr,"No package found\n");
	return 0;
 }
 json_t * results = json_object_get(root,"results");
  if(!json_is_array(results)){
	fprintf(stderr,"jansson: Not an Array line 98\n");
  }
 json_t * pkginfo;
  cdata = json_array_get(results,0);
  pkginfo = json_object_get(cdata, "Name");
  pkgs[0].name = malloc(sizeof(char) * (int)strlen(json_string_value(pkginfo)));
  strncpy(pkgs[0].name, json_string_value(pkginfo), json_string_length(pkginfo));
  pkginfo = json_object_get(cdata, "Version");
  pkgs[0].version = malloc(sizeof(char) * (int)strlen(json_string_value(pkginfo)));
  strncpy(pkgs[0].version, json_string_value(pkginfo), strlen(json_string_value(pkginfo)));
  pkginfo = json_object_get(cdata, "Description");
  pkgs[0].description = malloc(sizeof(char) * (int)strlen(json_string_value(pkginfo)));
  strncpy(pkgs[0].description, json_string_value(pkginfo), strlen(json_string_value(pkginfo)));
  pkginfo = json_object_get(cdata, "Maintainer");
  pkgs[0].maintainer = malloc(sizeof(char) * (int)strlen(json_string_value(pkginfo)));
  if(strcmp(json_string_value(pkginfo),"((null))") == 0){
      strncpy(pkgs[0].maintainer, "None", 4);
  }else {
      strncpy(pkgs[0].maintainer, json_string_value(pkginfo), strlen(json_string_value(pkginfo)));
  }
  pkginfo = json_object_get(cdata,"URL");
  pkgs[0].url = malloc(sizeof(char) * (int)strlen(json_string_value(pkginfo)));
  strncpy(pkgs[0].url, json_string_value(pkginfo), strlen(json_string_value(pkginfo)));
  return 1; 
} 

void search_print(aur_pkg_t pkg){
 printf("aur/%s %s\t (%s)\n%s\n",pkg.name,pkg.version,pkg.maintainer,pkg.description);
}

void info_print(aur_pkg_t pkg){
 printf("Name: %s\nVersion: %s\nDescription: %s\nMaintainer: %s\nURL: %s\n",pkg.name,pkg.version,pkg.description,pkg.maintainer,pkg.url);
}

