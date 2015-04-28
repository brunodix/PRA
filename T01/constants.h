//
// Created by bruno on 26/04/15.
//

#ifndef T01_CONSTANTS_H
#define T01_CONSTANTS_H

#include "student.h"

//Tamanho do arquivo em MEGAS
static int const SIZE = 10;
// 1 MiB
static int const MIB = 1024 * 1024;
// Número de vias
static int const PATHWAYS = 8;
// Tamanho do definição de estudante
static int const STUDENT_SIZE = sizeof(Student);
// Tamanho do arquivo final, que não tenha sobras
static int const FILE_SIZE = MIB * SIZE;
// Numero de regitros
static int const REG_NUM = FILE_SIZE / STUDENT_SIZE;
// Tamanho das páginas de registros
static int const REG_PAGE_SIZE = 100000;

#endif //T01_CONSTANTS_H
