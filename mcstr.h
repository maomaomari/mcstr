/*
Copyright 2025 maria clara skibinski <maomaomarii@gmail.com>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
	*/
#ifndef _MCSTR
#define _MCSTR

#include <string.h>
#include <stdlib.h>

typedef struct str_arr_s {
	char** str;
	unsigned int size;
} str_arr_t;

#define MCSTRDEF static inline

/*
  separates a char* between separator's occurances, returns a str_arr_s struct with the resulting char* and it's size.
 */
MCSTRDEF str_arr_t mcstr_str_split(char* src, char separator);
MCSTRDEF void mcstr_str_arr_println(const str_arr_t* const arr);
MCSTRDEF int mcstr_str_arr_explode(str_arr_t *arr);
MCSTRDEF str_arr_t mcstr_str_arr_init(void);
MCSTRDEF int mcstr_str_arr_add(char* str, str_arr_t* arr);

#ifdef MCSTR_IMP

MCSTRDEF str_arr_t mcstr_str_split(char* src, char separator) {
	size_t len = strlen(src);
	if(!len)
		return (str_arr_t) {
			.size = 0,
			.str = NULL,
		};
	str_arr_t words = {
		.size = 0,
	};
	words.str = malloc(sizeof(words.str));
	size_t last_word = 0;
	size_t current_word_size = 0;

	for(int i = 0; i < len+1; i++) {
		
		if(src[i] == separator || src[i] == '\0') {

			words.size++;
			words.str = realloc(words.str, sizeof(*(words.str)) * words.size);
			words.str[words.size - 1] = malloc(sizeof(**(words.str)) * current_word_size +1);
			
			memcpy(words.str[words.size - 1], src + i - current_word_size, current_word_size);
			words.str[words.size - 1][current_word_size] = '\0';
			
			current_word_size = 0;
		} else
			current_word_size++;	
	}
	
	return words;
}

MCSTRDEF void mcstr_str_arr_println(const str_arr_t* const arr) {
	for(int i = 0; i < arr->size; i++) {
		printf("%s\n", arr->str[i]);
	}
}

MCSTRDEF int mcstr_str_arr_explode(str_arr_t* arr) {
	for(int i = 0; i < arr->size; i++) {
		free(arr->str[i]);
		arr->str[i] = NULL;
	}
	arr->size = 0;
}

MCSTRDEF str_arr_t mcstr_str_arr_init() {
	str_arr_t temp = {
		.size = 0,
	};
	temp.str = malloc(sizeof(temp.str));
}

MCSTRDEF int mcstr_str_arr_add(char* str, str_arr_t* arr) {
	size_t len = strlen(str);
	if(!len)
		return -1;
	arr->size++;
	arr->str = realloc(arr->str, sizeof(*(arr->str)) * arr->size);
	arr->str[arr->size - 1] = malloc(sizeof(**arr->str) * len +1);
	memcpy(arr->str[arr->size - 1], str, len);
	arr->str[arr->size - 1][len] = 0;
	return 0;
}
#endif

#endif
