#include "strfunc.h"

int sf_word_count(char * keywords){
	size_t len = strlen(keywords);
	len++;
	int count = 0; 
	for(size_t i = 0; i < len; i++){
		if(keywords[i] == ' ' || keywords[i] == '\0'){
			count++;
		}
	}
	return count;
}

char ** sf_word_split(char * wordlist){
	char ** words;
	char buffer[strlen(wordlist)+1];
	size_t c = 0, z = 0, reset = 0;
	int count = sf_word_count(wordlist);
	words = malloc(sizeof(char*) * (int)count);
	for(size_t i = 0; i < (size_t)count; i++){
		words[i] = malloc(sizeof(char*) * strlen(wordlist));
	}
	// test = "A B C D E F"
	//         0123456789A
	for(size_t i = 0; i < strlen(wordlist)+1; i++, z++){
		if(wordlist[i] == ' ' || wordlist[i] == '\0'){
			strncpy(words[c],buffer,z);
			c++;
			reset = 1;
			continue;
		}
		if(reset == 1){z = 0; reset = 0;}
		buffer[z] = wordlist[i];
	}
	return words;
}

char * sf_word_prefix(char * first, char * second){
	size_t size = strlen(first) + strlen(second);
	char * nstr = malloc(sizeof(char) * size);
	memset((void*) nstr, 0, size);
	strncpy(nstr, first, strlen(first) + 1);
	size_t c = 0;
	for(size_t i = strlen(first); i < size; i++,c++){
		nstr[i] = second[c];
	}
	nstr[size] = 0;
	return nstr;
}

