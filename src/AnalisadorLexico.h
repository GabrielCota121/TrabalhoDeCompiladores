#ifndef ANALISADOR_LEXICO_H
#define ANALISADOR_LEXICO_H

#include "Token.h"

void inicializarLexer(FILE *arquivo);
Token getNextToken();


#endif // ANALISADOR_LEXICO_H