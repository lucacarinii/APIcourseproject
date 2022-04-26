#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct entity_s{

    char *id_orig;
    struct entity_s *next;

}entity_t;

typedef struct frequenzaRel_s{

    char *id_dest;
    char *id_rel;
    int totFreq;
    entity_t *id_origs[95];
    struct frequenzaRel_s *next;

}frequenzaRel_t;

typedef struct rel_s{

    entity_t *id_origs;
    char *id_rel;
    int freq;
    struct rel_s *next;

}rel_t;

//Funzioni usate per 'prendere' l'input
char *getName(char c);
//Funzione per definire il tipo di azione
int getAction(char *act);
//Aggiunge entità, inserimento in testa
entity_t *addent(entity_t *head,char *id_orig);
//Funzione usata per controllare se già esistono entità con lo stesso id
int controlla(entity_t *head, char *id_orig);
//Aggiunge la frequenza di ogni relazione, usare dopo addrel
frequenzaRel_t *addFreq(frequenzaRel_t *head, entity_t *headEnt[], char *id_orig, char *id_dest, char *id_rel);
//controlla se già esiste una relazione con lo stesso id_dest ed id_rel
int checkFrequency(frequenzaRel_t *head, char *id_dest, char *id_rel);
//Aggiunge nuova entità alla lista finale o update nuovo record
rel_t *addElemLastList(frequenzaRel_t *head, rel_t *headRel);
//Stampa il massimo di ogni relazione
void report(rel_t *head);
//Aggiunge una relazione
rel_t *addFinalRel(rel_t *head, char *id_orig, int totFreq, char *id_rel);
//Controlla se già esiste un nodo con quella relazione
int checkRel(rel_t *head,char *id_rel);
//update della lista relazione
void updateList(rel_t *head, char *id_rel, int totFreq, char *id_dest);
//Riordina secondo le specifiche la lista di output
void riordina(rel_t *head);
//Riordina le entità
void riordinaEntity(entity_t *head);
//Cancella la lista report
rel_t  *deleteList(rel_t *head);
//Cancella entità
entity_t *delent(entity_t *head, char *id_orig);
//cancella entità dalla lista frequenza
frequenzaRel_t *delentFreq(frequenzaRel_t *head,char *id_orig);
//Cancella relazione
frequenzaRel_t *delrel(frequenzaRel_t *head, char *id_orig, char *id_dest, char *id_rel);
//Cancella lista entità
entity_t *deleteListEnt(entity_t *head);
//Cancella lista frequenza
entity_t *deleteListFreq(frequenzaRel_t *head);



int main() {

    entity_t *listaUtenti[95];
    frequenzaRel_t *frequenzaRelazioni = NULL;
    rel_t *reportList = NULL;
    char *action, c, *id_orig = NULL, *id_dest = NULL, *id_rel = NULL;
    int i;

    //inizializzazione array utenti
    for(i = 0;i < 95;i++) {
        listaUtenti[i] = (entity_t *)malloc(sizeof(entity_t));
        listaUtenti[i] = NULL;
    }//122 - 'char'

    i = 0;

    action = (char *)malloc(7*sizeof(char));

    c = getchar();

    while(c != ' '){
        action[i] = c;
        c = getchar();
        i++;
    }
    action[i] = '\0';

    while(strcmp(action, "end") != 0){
        switch (getAction(action)) {
            case 1:
                id_orig = getName(c);
                id_orig = (char *) realloc(id_orig, strlen(id_orig) + 1);
                id_orig[strlen(id_orig)] = '\0';
                listaUtenti[126 - id_orig[0]] = addent(listaUtenti[126 - id_orig[0]], id_orig);
                id_orig[0] = '\0';
                free(id_orig);
                break;
            case 2:
                id_orig = getName(c);
                id_dest = getName(c);
                id_rel = getName(c);
                frequenzaRelazioni = addFreq(frequenzaRelazioni, listaUtenti,id_orig, id_dest, id_rel);
                if(reportList != NULL)
                    reportList = deleteList(reportList);
                free(id_orig);
                free(id_dest);
                free(id_rel);
                break;
            case 3:
                id_orig = getName(c);
                id_orig = (char *) realloc(id_orig, strlen(id_orig) + 1);
                id_orig[strlen(id_orig)] = '\0';
                listaUtenti[126 - id_orig[0]] = delent(listaUtenti[126 - id_orig[0]], id_orig);
                frequenzaRelazioni = delentFreq(frequenzaRelazioni,id_orig);
                if(reportList != NULL)
                    reportList = deleteList(reportList);
                id_orig[0] = '\0';
                free(id_orig);
                break;
            case 4:
                id_orig = getName(c);
                id_dest = getName(c);
                id_rel = getName(c);
                frequenzaRelazioni = delrel(frequenzaRelazioni, id_orig, id_dest, id_rel);
                if(reportList != NULL)
                    reportList = deleteList(reportList);
                free(id_orig);
                free(id_dest);
                free(id_rel);
                break;
            case 5:
                reportList = addElemLastList(frequenzaRelazioni,reportList);
                riordina(reportList);
                report(reportList);
                break;
            default:
                break;
        }
        free(action);
        action = (char *)malloc(7*sizeof(char));

        do{
            c = getchar();
        }while(c == ' ' || c == '"');

        i = 0;

        while(c != ' ' && c != '\n'){
            action[i] = c;
            c = getchar();
            i++;
        }
        action[i] = '\0';
    }
    return 0;
}

int getAction(char *act){

    if(strcmp(act, "addent") == 0){
        return 1;
    }
    else if(strcmp(act, "addrel") == 0){
        return 2;
    }
    else if(strcmp(act, "delent") == 0){
        return 3;
    }
    else if(strcmp(act, "delrel") == 0){
        return 4;
    }
    else if(strcmp(act, "report") == 0){
        return 5;
    }
    return 0;
}

char *getName(char c){

    int i = 0;
    char *id;

    do{
        c = getchar();
    }while(c == ' ' || c == '"');

    id = (char *)malloc(1*sizeof(char));

    while(c != '"'){

        id[i] = c;
        id = (char *)(realloc(id, (strlen(id) + 1) * sizeof(char)));
        c = getchar();
        i++;

    }
    id[i] = '\0';
    return id;
}

entity_t *addent(entity_t *head,char *id_orig) {

    entity_t *newx;

    if (head != NULL) {
        if(controlla(head,id_orig))
            return head;
        else {
            newx = (entity_t *) malloc(sizeof(entity_t));
            newx->id_orig = (char *) malloc((strlen(id_orig) + 1) * sizeof(char));
            strcpy(newx->id_orig, id_orig);
            newx->id_orig[strlen(id_orig) + 1] = '\0';
            newx->next = head;
            head = newx;
            return head;
        }
    }
    else{
        newx = (entity_t *) malloc(sizeof(entity_t));
        newx->id_orig = (char *) malloc((strlen(id_orig) + 1) * sizeof(char));
        strcpy(newx->id_orig, id_orig);
        newx->id_orig[strlen(id_orig) + 1] = '\0';
        newx->next = NULL;
        head = newx;
        return head;
    }
}

int controlla(entity_t *head, char *id_orig){

    entity_t *tmp;

    if(head == NULL){
        return 0;
    }
    else{
        tmp = head;
        while(tmp != NULL && tmp->id_orig != NULL){
            if(strcmp(tmp->id_orig, id_orig) == 0)
                return 1;
            tmp = tmp->next;
        }
        return 0;
    }
}

int checkFrequency(frequenzaRel_t *head, char *id_dest, char *id_rel){

    frequenzaRel_t *tmp;

    if(head != NULL){
        tmp = head;
        while(tmp != NULL){
            if(strcmp(tmp->id_dest, id_dest) == 0 &&
               strcmp(tmp->id_rel, id_rel) == 0)
                return 1;
            tmp = tmp->next;
        }
        return 0;
    }
    else
        return 0;
}

frequenzaRel_t *addFreq(frequenzaRel_t *head, entity_t *headEnt[], char *id_orig, char *id_dest, char *id_rel) {

    frequenzaRel_t *tmp, *newx;
    int i;
    if(headEnt[126 - id_orig[0]] != NULL && headEnt[126 - id_dest[0]] != NULL){
        if(controlla(headEnt[126 - id_orig[0]],id_orig) && controlla(headEnt[126 - id_dest[0]],id_dest)){
            if (head != NULL) {
                tmp = head;
                if (checkFrequency(tmp, id_dest, id_rel)) {
                    while (tmp != NULL) {
                        if (strcmp(tmp->id_dest, id_dest) == 0 &&
                            strcmp(tmp->id_rel, id_rel) == 0)
                            break;
                        tmp = tmp->next;
                    }
                    if (controlla(tmp->id_origs[126 - id_orig[0]], id_orig) == 1)
                        return head;
                    else if (checkFrequency(tmp, id_dest, id_rel) && controlla(tmp->id_origs[126 - id_orig[0]], id_orig) == 0) {
                        while (tmp != NULL) {
                            if (strcmp(tmp->id_dest, id_dest) == 0 &&
                                strcmp(tmp->id_rel, id_rel) == 0) {
                                tmp->totFreq++;
                                tmp->id_origs[126 - id_orig[0]] = addent(tmp->id_origs[126 - id_orig[0]], id_orig);
                            }
                            tmp = tmp->next;
                        }
                        return head;
                    }
                } else {
                    newx = (frequenzaRel_t *) malloc(sizeof(frequenzaRel_t));
                    for(i = 0;i < 95;i++){
                        newx->id_origs[i] = (entity_t *)malloc(sizeof(entity_t));
                        newx->id_origs[i] = NULL;
                    }
                    newx->id_origs[126 - id_orig[0]] = addent(NULL, id_orig);
                    newx->id_dest = (char *) malloc((strlen(id_dest) + 1) * sizeof(char));
                    strcpy(newx->id_dest, id_dest);
                    newx->id_dest[strlen(id_dest) + 1] = '\0';
                    newx->id_rel = (char *) malloc(strlen(id_rel) * sizeof(char));
                    strcpy(newx->id_rel, id_rel);
                    newx->totFreq = 1;
                    newx->next = tmp;
                    return newx;
                }
            } else {
                tmp = (frequenzaRel_t *) malloc(sizeof(frequenzaRel_t));
                tmp->id_origs[126 - id_orig[0]] = NULL;
                tmp->id_origs[126 - id_orig[0]]  = addent(tmp->id_origs[126 - id_orig[0]], id_orig);
                tmp->id_dest = (char *) malloc(strlen(id_dest) * sizeof(char));
                strcpy(tmp->id_dest, id_dest);
                tmp->id_rel = (char *) malloc(strlen(id_rel) * sizeof(char));
                strcpy(tmp->id_rel, id_rel);
                tmp->totFreq = 1;
                tmp->next = head;
                return tmp;
            }
        }
        return head;
    }
    return head;
}

int checkRel(rel_t *head,char *id_rel){

    rel_t *tmp;

    if(head != NULL){
        tmp = head;
        while(tmp != NULL){
            if(strcmp(tmp->id_rel,id_rel) == 0)
                return 1;
            tmp = tmp->next;
        }
        return 0;

    }
    else
        return 0;
}

void updateList(rel_t *head, char *id_rel, int freq, char *id_dest){
    rel_t *tmp;

    if(head != NULL){
        tmp = head;
        while(tmp != NULL){
            if(strcmp(tmp->id_rel, id_rel) == 0){
                if(freq > tmp->freq) {
                    tmp->freq = freq;
                    free(tmp->id_origs);
                    tmp->id_origs = NULL;
                    tmp->id_origs = addent(tmp->id_origs, id_dest);
                }else if(freq == tmp->freq){
                    tmp->id_origs = addent(tmp->id_origs,id_dest);
                }
            }
            tmp = tmp->next;
        }
    }
}

rel_t *addElemLastList(frequenzaRel_t *head, rel_t *headRel){

    frequenzaRel_t *tmp;
    rel_t *tmpRel;

    if(head != NULL){
        tmpRel = headRel;
        tmp = head;
        while(tmp != NULL){
            if(checkRel(tmpRel,tmp->id_rel)){
                updateList(tmpRel,tmp->id_rel,tmp->totFreq,tmp->id_dest);
            }
            else{
                tmpRel = addFinalRel(tmpRel,tmp->id_dest,tmp->totFreq,tmp->id_rel);
            }
            tmp = tmp->next;
        }
        return tmpRel;
    }
    else{
        return headRel;
    }
}

rel_t *addFinalRel(rel_t *head, char *id_orig,int totFreq, char *id_rel) {

    rel_t *newx;

    newx = (rel_t *) malloc(sizeof(rel_t));
    newx->id_origs = NULL;
    newx->id_origs = addent(newx->id_origs, id_orig);
    newx->id_rel = (char *) malloc(strlen(id_rel) * sizeof(char));
    strcpy(newx->id_rel, id_rel);
    newx->id_rel[strlen(newx->id_rel)] = '\0';
    newx->freq = totFreq;
    newx->next = head;
    head = newx;
    return head;
}

void riordinaEntity(entity_t *head){

    entity_t *tmp,*tmp2;

    char *id_origFlag;

    if(head != NULL){
        tmp = head;
        while(tmp != NULL){
            tmp2 = tmp->next;
            while(tmp2 != NULL){
                if(strcmp(tmp2->id_orig,tmp->id_orig) < 0){
                    id_origFlag = tmp2->id_orig;
                    tmp2->id_orig = tmp->id_orig;
                    tmp->id_orig = id_origFlag;
                }
                tmp2 = tmp2->next;
            }
            tmp = tmp->next;
        }
    }
}

void riordina(rel_t *head){

    rel_t *tmp,*tmp2;
    int flagFreq;
    entity_t *flagid_dest;
    char *flagid_rel;

    if(head != NULL){
        tmp = head;
        while(tmp != NULL ){
            riordinaEntity(tmp->id_origs);
            tmp = tmp->next;
        }
        tmp = head;
        while(tmp != NULL ){
            tmp2 = tmp->next;
            while(tmp2 != NULL){
                if(strcmp(tmp2->id_rel,tmp->id_rel) < 0){
                    flagFreq = tmp2->freq;
                    tmp2->freq = tmp->freq;
                    tmp->freq = flagFreq;
                    flagid_dest = tmp2->id_origs;
                    tmp2->id_origs = tmp->id_origs;
                    tmp->id_origs = flagid_dest;
                    flagid_rel = tmp2->id_rel;
                    tmp2->id_rel = tmp->id_rel;
                    tmp->id_rel = flagid_rel;
                }
                tmp2 = tmp2->next;
            }
            tmp = tmp->next;
        }
    }
}

void report(rel_t *head){

    rel_t *tmp;
    entity_t *tmpEnt;

    if(head != NULL){
        tmp = head;
        while(tmp != NULL){
            tmpEnt = tmp->id_origs;
            printf("\"%s\" ",tmp->id_rel);
            while(tmpEnt != NULL){
                printf("\"%s\" ",tmpEnt->id_orig);
                tmpEnt = tmpEnt->next;
            }
            printf("%d; ",tmp->freq);
            tmp = tmp->next;
        }
        printf("\n");
    }
    else
        printf("none\n");
}

rel_t  *deleteList(rel_t *head)
{
    rel_t* tmp = head;
    rel_t* next;

    while (tmp != NULL)
    {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    head = NULL;

    return head;
}

entity_t *delent(entity_t *head, char *id_orig)
{
    entity_t *tmp = head, *prev;

    if(head != NULL){
        if(controlla(tmp,id_orig)){
            if (tmp != NULL && strcmp(tmp->id_orig,id_orig) == 0)
            {
                head = tmp->next;
                free(tmp);
                return head;
            }
            while (tmp != NULL && strcmp(tmp->id_orig,id_orig) != 0)
            {
                prev = tmp;
                tmp = tmp->next;
            }

            if (tmp == NULL) return head;

            prev->next = tmp->next;

            free(tmp);

            return head;
        }
        return head;
    }
    return NULL;
}

frequenzaRel_t *delentFreq(frequenzaRel_t *head,char *id_orig){

    frequenzaRel_t *tmp = head,*prev;
    int i = 0;
    if(head != NULL){
        if(tmp != NULL && strcmp(tmp->id_dest,id_orig) == 0){
            head = tmp->next;
            free(tmp);
            tmp = head;
            i = 1;
        }else if(controlla(tmp->id_origs[126 - id_orig[0]],id_orig)){
            tmp->id_origs[126 - id_orig[0]] = delent(tmp->id_origs[126 - id_orig[0]],id_orig);
            tmp->totFreq = tmp->totFreq - 1;
            if(tmp->totFreq == 0){
                head = tmp->next;
                free(tmp);
                tmp = head;
                i = 1;
            }
        }

        while(tmp != NULL){
            if(strcmp(tmp->id_dest,id_orig) == 0){
                if(i == 1){
                    head = tmp->next;
                    free(tmp);
                    tmp = head;
                    i = 1;
                    continue;
                }
                else{
                    prev->next = tmp->next;
                    free(tmp);
                    tmp = prev->next;
                    continue;
                }
            }
            else if(controlla(tmp->id_origs[126 - id_orig[0]],id_orig)){
                tmp->id_origs[126 - id_orig[0]] = delent(tmp->id_origs[126 - id_orig[0]],id_orig);
                tmp->totFreq = tmp->totFreq - 1;
                if(tmp->totFreq == 0){
                    if(i == 1){
                        head = tmp->next;
                        free(tmp);
                        tmp = head;
                        i = 1;
                        continue;
                    }
                    prev->next = tmp->next;
                    free(tmp);
                    tmp = prev->next;
                    continue;
                }
            }
            prev = tmp;
            tmp = tmp->next;
            i = 0;
        }
        return head;
    }
    return NULL;
}

frequenzaRel_t *delrel(frequenzaRel_t *head, char *id_orig, char *id_dest, char *id_rel){

    frequenzaRel_t *tmp = head, *prev;

    if(tmp != NULL && strcmp(tmp->id_dest,id_dest) == 0 && controlla(tmp->id_origs[126 - id_orig[0]],id_orig) && strcmp(tmp->id_rel,id_rel) == 0){
        if(tmp->totFreq == 1){
            head = tmp->next;
            free(tmp);
            return head;
        }else{
            tmp->id_origs[126 - id_orig[0]] = delent(tmp->id_origs[126 - id_orig[0]],id_orig);
            tmp->totFreq = tmp->totFreq - 1;
            return head;
        }
    }

    while(tmp != NULL){

        if(strcmp(tmp->id_dest,id_dest) == 0 && controlla(tmp->id_origs[126 - id_orig[0]],id_orig) && strcmp(tmp->id_rel,id_rel) == 0){
            if(tmp->totFreq == 1){
                prev->next = tmp->next;
                free(tmp);
                return head;
            }
            else{
                tmp->id_origs[126 - id_orig[0]] = delent(tmp->id_origs[126 - id_orig[0]],id_orig);
                tmp->totFreq = tmp->totFreq - 1;
                return head;
            }
        }

        prev = tmp;
        tmp = tmp->next;
    }
    return head;
}

entity_t *deleteListEnt(entity_t *head){

    entity_t* tmp = head;
    entity_t* next;

    while (tmp != NULL)
    {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    head = NULL;

    return head;
}

entity_t *deleteListFreq(frequenzaRel_t *head){

    frequenzaRel_t* tmp = head;
    frequenzaRel_t* next;

    while (tmp != NULL)
    {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    head = NULL;

    return head;
}