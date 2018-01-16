#include <stdio.h>
#include <stdlib.h>

typedef struct set {
    int start;
    int end;
    struct set *next;
} set;

typedef struct setList {
    set *setEntry;
    struct setList *next;
} setList;

//set functions
void createSet(set *s) {
    s = malloc(sizeof(set));
    s->start = -999;
    s->end = -999;
    s->next = NULL;
}

void push(set *s, int s, int e) {
    if(s->start == -999) { //set is empty
        s->start = s;
        s->end = e;
    }
    else {
        set *temp = malloc(sizeof(set));
        temp->start = s;
        temp->end = e;
        temp->next = NULL;
        set *search = s;
        while(search->next != NULL)
            search = search->next;
        search->next = temp;
    }
}

int order(set *s) {
    int count = 0;
    if(s->start == -999)
         return 0;
    else {
        ++count;
        set *search = s;
        while(search->next != NULL) {
            ++count;
            search = search->next;
        }
        return count;
    }
}

void createSetList(setList *sl) {
    sl = malloc(sizeof(setList);
    sl->next = NULL;
    set *s;
    createSet(s);
    sl->setEntry = s;
}

//creates power sets of a set s. return setList R;
setList* subsets(set *s, int n) {
    setList *curR, *rootR, *lastR; //intial setList to be returned
    setList *R;
    createSetList(R);
    rootR = R; 
    curR = R; 
    lastR = R;
    //iterate through initial set adding elements to set list
    for(int i = 0; i < n; i++) { 
        
    }
}

int main(void) {

}
