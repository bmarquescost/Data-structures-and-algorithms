#ifndef _STR_H_
#define _STR_H_

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#define TAB "    "

typedef char * string_t;

/*
 * Definições para uso da estrutura string_list_t
 */

struct string_list {
	string_t *strs;
	int amt_strs;
};
typedef struct string_list * string_list_t;

string_list_t str_list_create(int initial_amt_strs);
void str_list_delete(string_list_t list);

string_list_t str_split(string_t src_str, char sep);
/*******************************************************************************/

/*
 * Definições para leitura de dados
 * > Modos:
 *   `-> NORMAL: leitura da linha toda
 *   |      read_<type>(ptr, READ_ALL)
 *   |
 *   `-> FROM_TO: leitura da linha entre dois sepadores
 *   |      read_<type>(ptr, READ_FROM_TO, "<init>", "<end>")
 *   |
 *   `-> FROM: leitura da linha a partir de um separador
 *   |      read_<type>(ptr, READ_FROM, "<init>")
 *   |
 *   `-> UNTIL: leitura da linha até um separador
 *          read_<type>(ptr, READ_UNTIL, "<end>")
 */
typedef enum {READ_ALL, READ_FROM_TO, READ_FROM, READ_UNTIL} read_mode;

string_t read_line(FILE *ptr, read_mode mode, ...);
int read_int(FILE *ptr, read_mode mode, ...);
double read_double(FILE *ptr, read_mode mode, ...);
/******************************************************************************/

/*
 * Definições para funções gerais relacionadas à strings
 */

int str_to_int(string_t num_str);
double str_to_double(string_t num_str);
string_t int_to_str(int num);

string_t str_copy(string_t source_str);
string_t str_join(string_t sep, string_t left_str, string_t right_str);
string_t str_trim(string_t original_str, char removed_char);

void str_to_lower(string_t original_str);
void str_converts_not_alpha_to_spaces(string_t original_str);
bool strs_are_equals(string_t, string_t);

/******************************************************************************/

#endif
