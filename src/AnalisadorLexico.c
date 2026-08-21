#include <stdio.h>
#include <stdlib.h>

#include "AnalisadorLexico.h"

static FILE *arquivo;

void inicializarLexer(FILE *entrada) {
    arquivo = entrada;
}

Token getNextToken(){
    
}