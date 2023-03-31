/**
 * @file test.c
 * @author Théo TAILLEFUMIER 
 * @brief 
 * @necessities 
 * @date 2023-03-31
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include "headers/joueuses.h"
/**
 * @brief test si la joueuse est initialisée
 * 
 * @param j la joueuse à tester
 * 
 * @return int 1 si initialisée, 0 sinon
 * 
 */
//ce test est à chier
int test_init_joueuses(joueuse j)
{
    if(j == NULL)
    {
        return 0;
    }
    return 1;
}