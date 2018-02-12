#ifndef STRFUNC_H
#define STRFUNC_H
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

int sf_word_count(char * keywords); // counts number of words in keywords
char ** sf_word_split(char * wordlist); // splits wordlist into char[num_of_words];
char * sf_word_prefix (char * first, char * second); // prefix 'first' str by 'second' str

#endif //STRFUNC_H
