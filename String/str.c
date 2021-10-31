#include "../Includes/str.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/*
 * Funções para uso da struct string_list_t
 */

#define INITIAL_STR_LIST_SIZE 32

/**
 * @brief Aloca espaço para uma nova lista de strings.
 *
 * @param initial_amt_strs quantidade inicial de strings para lista
 *
 * @return string_list_t struct para uma nova lista de strings
 */
string_list_t str_list_create(int initial_amt_strs) {
	string_list_t list = malloc(sizeof(struct string_list));
	if (initial_amt_strs > 0) {
		list->strs = malloc(initial_amt_strs * sizeof(string_t));
	} else {
		list->strs = NULL;
	}
	list->amt_strs = initial_amt_strs;

	return list;
}

/**
 * @brief Libera toda memória utilizada por uma lista de strings.
 *
 * @param list struct referente a uma lista de strings
 */
void str_list_delete(string_list_t list) {
	for (int i = 0; i < list->amt_strs; i++) free(list->strs[i]);
	free(list->strs);
	free(list);
}

/**
 * @brief Copia uma parte de uma string até um certo token para uma outra string.
 *
 * @param src_str  string de origem
 * @param src_pos  index referente a string de origem
 * @param dest_str string de destino
 * @param sep      token para referênciar o fim da parte
 *
 * @return bool boolo que alega se foi alcançado o fim da string de origem
 */
static bool _get_a_part_from_str(string_t src_str, int *src_pos, string_t *dest_str, char sep) {
	*dest_str = NULL;
	bool is_end_of_part = false, is_end_of_str = false;

	char c;
	int dest_pos = 0;
	do {
		c = src_str[*src_pos];

		if (c == sep) {
			is_end_of_part = true;
			c              = '\0';
		} else if (c == '\0') {
			is_end_of_part = true;
			is_end_of_str  = true;
		}

		*dest_str             = realloc(*dest_str, (dest_pos + 1) * sizeof(char));
		(*dest_str)[dest_pos] = c;

		(*src_pos)++;
		dest_pos++;
	} while (!is_end_of_part);

	return is_end_of_str;
}

/**
 * @brief Realoca o dobro da memória atual para uma lista de strings.
 *
 * @param list struct referente a uma lista de strings
 */
static void _realloc_str_list(string_list_t list) {
	list->amt_strs *= 2;
	list->strs      = realloc(list->strs, list->amt_strs * sizeof(string_t));
}

/**
 * @brief Divide uma string em uma lista de strings a partir de um token.
 *
 * @param str string a ser dividida
 * @param sep token de separação
 *
 * @return string_list_t struct com a lista de strings geradas
 */
string_list_t str_split(string_t str, char sep) {
	string_list_t split_list = str_list_create(0);

	split_list->amt_strs = INITIAL_STR_LIST_SIZE;
	split_list->strs     = malloc(split_list->amt_strs * sizeof(string_t));

	bool is_end = false;
	int  i = 0, str_pos = 0;
	do {

		if (i == split_list->amt_strs) _realloc_str_list(split_list);
		string_t *cur_part = &split_list->strs[i];

		is_end = _get_a_part_from_str(str, &str_pos, cur_part, sep);

		if ((*cur_part)[0] == '\0') {
			free(*cur_part);
			continue;
		}

		i++;
	} while (!is_end);
	split_list->amt_strs = i;
	split_list->strs     = realloc(split_list->strs, split_list->amt_strs * sizeof(string_t));

	return split_list;
}
/*******************************************************************************/

/*
 * Funções para leitura de strings e números
 */

#define INITIAL_STR_LEN 512

/**
 * @brief Realoca o dobro da memória atual para uma string.
 *
 * @param str string a ter o espaço realocado
 * @param len tamanho atual da string
 */
static void _realloc_string(string_t *str, int *len) {
	*len *= 2;
	*str  = realloc(*str, *len * sizeof(char));
}

/**
 * @brief Lê, de um arquivo ou entrada de um usuário, uma sequência de chars até
 *  um certo token ou fim da linha e escreve em uma string.
 *
 * @param ptr     ponteiro para o arquivo no qual ocorrerá a leitura
 * @param str     string na qual será guarada a sequência de chars
 * @param end_ref token de referência para o final
 * @param cur_len tamanho alocado atualmente para a string
 *
 * @return int tamanho final da string
 */
static int _read_loop(FILE *ptr, string_t str, void *end_ref, int cur_len) {
	bool is_finished = false;

	char c;
	int i = 0;
	do {
		if (i == cur_len) _realloc_string(&str, &cur_len);

		c = fgetc(ptr);
		if (c == '\r') c = fgetc(ptr);

		// Verifica se a leitura terminou
		if (end_ref) {
			is_finished = (c == '\n' || c == EOF || c == *(string_t)end_ref);
		} else {
			is_finished = (c == '\n' || c == EOF);
		}

		// Adiciona caracter na string, ou '\0' caso encontre o final
		str[i++] = is_finished ? '\0' : c;
	} while (!is_finished);

	return i;
}

/**
 * @brief Cria e lê uma string a partir de um arquivo ou entrada do usuário.
 *
 * @param ptr         ponteiro para o arquivo no qual ocorrerá a leitura
 * @param is_finished boolo que alega se a linha na foi lida por completo
 * @param end_ref     token de referência para o final
 *
 * @return string_t string lida até o token ou final
 */
static string_t _read(FILE *ptr, bool is_finished, void *end_ref) {
	if (is_finished) return NULL;

	int cur_len  = INITIAL_STR_LEN;
	string_t str = malloc(cur_len * sizeof(char));

	int final_len = _read_loop(ptr, str, end_ref, cur_len);
	str           = realloc(str, final_len * sizeof(char));

	return str;
}

/**
 * @brief Leva o ponteiro do arquivo até uma posição após o token de ínicio de
 *  leitura.
 *
 * @param ptr       ponteiro para o arquivo no qual ocorrerá a leitura
 * @param start_ref token de referência para o início
 *
 * @return bool boolo que alega se a linha foi lida por inteiro
 */
static bool _read_ignored_part(FILE *ptr, void *start_ref) {
	char ignored;
	do {
		ignored = fgetc(ptr);
		if (ignored == '\r') ignored = fgetc(ptr);
		if (ignored == '\n' || ignored == EOF) return true;
	} while (ignored != *(string_t)start_ref);

	return false;
}

/**
 * @brief Realiza o setup de acordo com os modos para a execução da read_line()
 *  usando stdarg.h
 *
 * @param ptr  ponteiro para o arquivo no qual ocorrerá a leitura
 * @param mode modo de leitura escolhido
 * @param refs lista de tokens recebidos de acordo com cada modo
 *
 * @return string_t string lida de acordo com o modo
 */
static string_t _v_read_line(FILE *ptr, read_mode mode, va_list refs) {
	if (mode == READ_ALL) return _read(ptr, false, NULL);

	void *start_ref = NULL;
	void *end_ref = NULL;
	if (mode == READ_FROM_TO) {
		start_ref = va_arg(refs, void *);
		end_ref   = va_arg(refs, void *);
	} else {
		if (mode == READ_FROM)       start_ref = va_arg(refs, void *);
		else if (mode == READ_UNTIL) end_ref   = va_arg(refs, void *);
	}

	bool is_finished = false;
	if (start_ref) is_finished = _read_ignored_part(ptr, start_ref);

	return _read(ptr, is_finished, end_ref);
}

/**
 * @brief Realiza a leitura de uma sequência de chars, tendo suporte para quatro
 *  modos: READ_ALL (leitura completa da linha, até '\n'), READ_FROM_TO (leitura
 * 	entre tokens), READ_FROM (leitura a partir de um token), e READ_UNTIL
 *  (leitura até um token).
 *
 * @param ptr  ponteiro para o arquivo no qual ocorrerá a leitura
 * @param mode modo de leitura escolhido
 * @param ...  lista de tokens caso necessários
 *
 * @return string_t string lida de acordo com o modo
 */
string_t read_line(FILE *ptr, read_mode mode, ...) {
	// Seta os parâmetros opcionais para função de leitura
	va_list refs;
	va_start(refs, mode);
	string_t str = _v_read_line(ptr, mode, refs);
	va_end(refs);

	return str;
}

/**
 * @brief Re
aliza a leitura de um inteiro, tendo suporte para quatro modos:
 *  READ_ALL (leitura completa da linha, até '\n'), READ_FROM_TO (leitura entre
 *  tokens), READ_FROM (leitura a partir de um token), e READ_UNTIL (leitura até
 *  um token).
 *
 * @param ptr  ponteiro para o arquivo no qual ocorrerá a leitura
 * @param mode modo de leitura escolhido
 * @param ...  lista de tokens caso necessários
 *
 * @return string_t string lida de acordo com o modo
 */
int read_int(FILE *ptr, read_mode mode, ...) {
	// Seta os parâmetros opcionais para função de leitura
	va_list refs;
	va_start(refs, mode);
	string_t num_str = _v_read_line(ptr, mode, refs);
	va_end(refs);

	int num = str_to_int(num_str);
	free(num_str);

	return num;
}

/**
 * @brief Realiza a leitura de um real, tendo suporte para quatro modos:
 *  READ_ALL (leitura completa da linha, até '\n'), READ_FROM_TO (leitura entre
 *  tokens), READ_FROM (leitura a partir de um token), e READ_UNTIL (leitura até
 *  um token).
 *
 * @param ptr  ponteiro para o arquivo no qual ocorrerá a leitura
 * @param mode modo de leitura escolhido
 * @param ...  lista de tokens caso necessários
 *
 * @return string_t string lida de acordo com o modo
 */
double read_double(FILE *ptr, read_mode mode, ...) {
	// Seta os parâmetros opcionais para função de leitura
	va_list refs;
	va_start(refs, mode);
	string_t num_str = _v_read_line(ptr, mode, refs);
	va_end(refs);

	return str_to_double(num_str);
}
/*******************************************************************************/

/*
 * Funções gerais relacionadas à strings
 */

/**
 * @brief Converte uma string para o seu referente inteiro.
 *
 * @param num_str string que representa um número inteiro
 *
 * @return int número pós conversão de tipo
 */
int str_to_int(string_t num_str) {
	int num = strtol(num_str, NULL, 10);

	return num;
}

/**
 * @brief Converte uma string para o seu referente double.
 *
 * @param num_str string que representa um número real
 *
 * @return int número pós conversão de tipo
 */
double str_to_double(string_t num_str) {
	double num = strtod(num_str, NULL);
	free(num_str);

	return num;
}

/**
 * @brief Calcula a parte inteira do log na base 10 de um dado n.
 *
 * @param n inteiro que terá seu log calculado
 *
 * @return int parte inteira do resultado
 */
static int _log_10(int n) {
	int log = 0;
	while (n / 10 > 0) { log++; n /= 10; }

	return log;
}

/**
 * @brief Converte um número inteiro para uma string que o representa.
 *
 * @param num valor inteiro para ser convertido em string
 *
 * @return string_t string representante do número pós conversão
 */
string_t int_to_str(int num) {
	int str_len = _log_10(num) + 1;

	string_t str_num = malloc(sizeof(char) * (str_len + 1));
	for (int i = 0; i < str_len; i++) {
		char digit = '0' + num % 10;
		str_num[str_len - i - 1] = digit;
		num /= 10;
	}
	str_num[str_len] = '\0';

	return str_num;
}

/**
 * @brief Retorna uma cópia, alocada em outra região de memória, de uma string.
 *
 * @param source_str string a ser copiada

 * @return string_t cópia da string alocada em outra região
 */
string_t str_copy(string_t source_str) {
	int      str_size = strlen(source_str) + 1;
	string_t new_str  = malloc(str_size * sizeof(char));

	for (int i = 0; i < str_size; i++) new_str[i] = source_str[i];

	return new_str;
}

/**

 * @brief Concatena duas strings em uma outra string, usando o separador
 *  especificado.
 *
 * @param sep       separador utilizado na concatenação
 * @param left_str  string que ficará à esquerda do separador
 * @param right_str string que ficará à direita do separador
 *
 * @return string_t string resultante da concatenação
 */
string_t str_join(string_t sep, string_t left_str, string_t right_str) {
	int l_str_len   = strlen(left_str);
	int r_str_len   = strlen(right_str);
	int sep_str_len = strlen(sep);

	int      joined_str_len = l_str_len + sep_str_len + r_str_len + 1;
	string_t joined_str     = malloc(sizeof(char) * joined_str_len);

	int i = 0, j = 0;
	while (j < l_str_len) joined_str[i++] = left_str[j++];

	j = 0;
	while (j < sep_str_len) joined_str[i++] = sep[j++];

	j = 0;
	while (j <= r_str_len) joined_str[i++] = right_str[j++];

	return joined_str;
}

/**
 * @brief Remove um caracter especificado das bordas de uma string.
 *
 * @param original_str string da qual serão removidos os caracteres
 * @param removed_char carater a ser limpo
 *
 * @return string_t string resultante da limpeza
 */
string_t str_trim(string_t original_str, char removed_char) {
	int ori_len = strlen(original_str);

	int ori_idx = 0;
	while (original_str[ori_idx] == removed_char) ori_idx++;

	int allocated_size = ori_len - ori_idx + 1, new_len = 0;
	string_t new_str = malloc(allocated_size);
	do {
		char cur_c = original_str[ori_idx];
		new_str[new_len++] = cur_c == removed_char ? '\0' : cur_c;
	} while (ori_idx < ori_len && original_str[ori_idx++] != removed_char);

	if (new_len < allocated_size) new_str = realloc(new_str, sizeof(char) * new_len);

	return new_str;
}

/**
 * @brief Converte todos caracteres de uma string para minúsculo.
 *
 * @param original_str string a ser alterada
 */
void str_to_lower(string_t original_str) {
	int str_len = strlen(original_str);

	for (int i = 0; i < str_len; i++) original_str[i] = tolower(original_str[i]);
}

/**
 * @brief Converte todos caracteres não alfabêticos de uma string para espaços.
 *
 * @param original_str string a ser alterada
 */
void str_converts_not_alpha_to_spaces(string_t original_str) {
	int str_len = strlen(original_str);

	for (int i = 0; i < str_len; i++) {
		if (!isalpha(original_str[i])) original_str[i] = ' ';
	}
}

bool strs_are_equals(string_t a, string_t b) {
	return (strcmp(a,b) == 0);
}

/*******************************************************************************/
