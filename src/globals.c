#include <stdlib.h>
#include "globals.h"
#include <semaphore.h>
queue_t *students_queue = NULL;
table_t *table = NULL;
buffet_t *buffets_ref = NULL;

int students_number = 0;
int number_of_tables_global = 0;
int seats_per_table_global = 0;
int number_buffets = 0;

int number_students_served = 0;

int buffets_criados = 0;

pthread_mutex_t mutex_queue;
pthread_mutex_t n_student_served;

void globals_set_queue(queue_t *queue)
{
    students_queue = queue;
}

queue_t *globals_get_queue()
{
    return students_queue;
}

void globals_set_table(table_t *t)
{
    table = t;
}

table_t *globals_get_table()
{
    return table;
}


void globals_set_students(int number)
{
    students_number = number;
}

int globals_get_students()
{
    return students_number;
}

void globals_set_buffets(buffet_t *buffets)
{
    buffets_ref = buffets;
}

buffet_t *globals_get_buffets()
{
    return buffets_ref;
}

void globals_set_number_buffets(int buffets)
{
    number_buffets = buffets;
}

int globals_get_number_buffets()
{
    return number_buffets;
}

void globals_set_students_served(int number)
{
    number_students_served = number;
}

int globals_get_students_served()
{
    return number_students_served;
}

void globals_set_number_tables(int number)
{
    number_of_tables_global = number;
}

int globals_get_number_tables()
{
    return number_of_tables_global;
}

void globals_set_buffets_criados(int criados)
{
    buffets_criados = criados;
}

int globals_get_buffets_criados()
{
    return buffets_criados;
}

/**
 * @brief Finaliza todas as variáveis globais que ainda não foram liberadas.
 *  Se criar alguma variável global que faça uso de mallocs, lembre-se sempre de usar o free dentro
 * dessa função.
 */
void globals_finalize()
{
    free(table);
}