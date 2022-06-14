#include <stdlib.h>

#include "worker_gate.h"
#include "globals.h"
#include "config.h"

student_t *current_student;
extern int buffet_queue_insert(buffet_t *self, student_t *student);
extern int number_of_buffets;

extern pthread_mutex_t mutex_queue;

/*
TODO:
Ver aonde declarar a inicialização do mutex da queue e aonde declarar a variável dele
*/

void worker_gate_look_queue()
{
    /* Insira aqui sua lógica */
    // Pega o próximo estudante
    current_student = globals_get_queue()->_first->_student;
}

void worker_gate_remove_student(int number_students)
{
    // Retira o Student da queue
    queue_remove(globals_get_queue());
    number_students--;
}

void worker_gate_look_buffet(buffet_t *buffets)
{
    // Pega o id de um buffet para direcionar o estudante
    // talvez trocar por um while onde ele procura constantemente entre os buffets
    // vaté encontrar a posição ao invés de para após olhar uma vez em cada
    int buffet_entrou = 0;
    int i = 0;
    while (buffet_entrou == 0) {
        i = i % number_of_buffets;
        if (&buffets[i].queue_left[0] == 0) {  // checar se o buffet tem pelo menos uma fila disponivel
            current_student->_id_buffet = *(&buffets[i]._id);  // colocar o id do buffet vago
            current_student->left_or_right = 'L';           // colocar o lado do buffet
            break;
        } else if (&buffets[i].queue_right[0] == 0){  // checar se o buffet tem pelo menos uma fila disponivel
            current_student->_id_buffet = *(&buffets[i]._id);  // colocar o id do buffet vago
            current_student->left_or_right = 'R';           // colocar o lado do buffet
            break;
        }
        i++;
    }
}

void *worker_gate_run(void *arg)
{
    int all_students_entered;
    int number_students;

    number_students = *((int *)arg);
    all_students_entered = number_students > 0 ? FALSE : TRUE;
    buffet_t *buffets = globals_get_buffets();

    while (all_students_entered == FALSE)
    {
        pthread_mutex_lock(&mutex_queue);   // apenas uma thread pode acessar a queue por vez
        worker_gate_look_queue();
        worker_gate_look_buffet(buffets);
        worker_gate_remove_student(number_students);
        pthread_mutex_unlock(&mutex_queue);
        //msleep(5000); /* Pode retirar este sleep quando implementar a solução! */
        all_students_entered = number_students > 0 ? FALSE : TRUE; // caso não tenha mais estudantes, quebra o loop
    }

    pthread_exit(NULL);
}

void worker_gate_init(worker_gate_t *self)
{
    // dar init em todos os semaforos e mutex usados por worker_gate
    // Criar um mutex para acesso a queue
    int number_students = globals_get_students();
    pthread_mutex_init(&mutex_queue, NULL);
    pthread_create(&self->thread, NULL, worker_gate_run, &number_students);
}

void worker_gate_finalize(worker_gate_t *self)
{
    pthread_join(self->thread, NULL);
    free(self);
    pthread_mutex_destroy(&mutex_queue);
    // dar destroy em todos os semaforos e mutexes usados por worker_gate
}

void worker_gate_insert_queue_buffet(student_t *student)
{
    /* Insira aqui sua lógica */
    // Colocando no buffet
    // Fazer as checagens e usar os semáforos necessários para os buffets, caso preciso
    buffet_t *buffets = globals_get_buffets();
    buffet_queue_insert(buffets, student);
}