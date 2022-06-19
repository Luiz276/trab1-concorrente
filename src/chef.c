#include <stdlib.h>

#include "chef.h"
#include "config.h"
#include "globals.h"

extern int number_students_served;

void *chef_run()
{
    /* Insira sua lógica aqui */
    int total_students = globals_get_students();
    while (globals_get_buffets_criados() != 1);
    while (number_students_served != total_students)
    {
        //msleep(5000); /* Pode retirar este sleep quando implementar a solução! */
        chef_check_food();
    }
    
    pthread_exit(NULL);
}


void chef_put_food(int id_buffet, int meal)
{
    /* Insira sua lógica aqui */
    buffet_t *buffets = globals_get_buffets();
    // talvez colocar um mutex ou um semáforo para impedir interferência nessa operação
    buffets[id_buffet]._meal[meal] += 40;
}

void chef_check_food()
{
    /* Insira sua lógica aqui */
    // loop que checa os buffets por comida que falta enquanto todos os estudantes não se servirem
    // caso falte comida, chama put food
    buffet_t *buffets = globals_get_buffets();
    int number_of_buffets = globals_get_number_buffets();
    int total_students = globals_get_students();
    while (number_students_served < total_students) {
        for (int i = 0; i < number_of_buffets; i++) {
            for (int j = 0; j < 5; j++) {
                if (buffets[i]._meal[j] == 0) {
                    chef_put_food(i, j);
                }
            }
        }
    }
}

/* --------------------------------------------------------- */
/* ATENÇÃO: Não será necessário modificar as funções abaixo! */
/* --------------------------------------------------------- */

void chef_init(chef_t *self)
{
    pthread_create(&self->thread, NULL, chef_run, NULL);
}

void chef_finalize(chef_t *self)
{
    pthread_join(self->thread, NULL);
    free(self);
}