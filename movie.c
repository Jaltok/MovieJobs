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
    s->start = -999;
    s->end = -999;
    s->next = NULL;
}

void push(set *S, int s, int e) {
    if(S->start == -999) { //set is empty
        S->start = s;
        S->end = e;
    }
    else {
        set *temp = malloc(sizeof(set));
        temp->start = s;
        temp->end = e;
        temp->next = NULL;
        set *search = S;
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
    sl->next = NULL;
    set *s;
    s = malloc(sizeof(set));
    createSet(s);
    sl->setEntry = s;
}

void printSet(set *s) {
    set *temp = s;
    int n = order(s);
    printf("Got order\n");
    if(n == 0) {
        printf("{}\n");
        return;
    }
    printf("{(%d, %d)", s->start, s->end);
    for(int i = 0; i < n; i++) {
        temp = temp->next;
        printf("(%d,%d)", temp->start, temp->end);
    }
    printf("}\n");
}

//creates power sets of a set s. return setList R;
setList* subsets(set *s, int n) {
    set *origin = s; 
    setList *curR, *rootR, *lastR; //intial setList to be returned
    setList *R = malloc(sizeof(setList));
    createSetList(R);
    rootR = R; 
    lastR = R;
    int totalSets = 1; //empty set counts as 1
    //iterate through initial set adding permutations to set list
    for(int i = 0; i < n; i++) { 
        if(i != 0) origin = origin->next;
        setList *V, *curV, *lastV, *rootV;
        V = malloc(sizeof(setList));
        createSetList(V);
        rootV = V; curV = V; lastV = V;
        curR = rootR;
        for(int j = 0; j < totalSets; j++) {
            if(j != 0) curR = curR->next;

            set *temp = curR->setEntry;
       
            while(temp->next != NULL) { //creating new set
                push(curV->setEntry, temp->start, temp->end);
                temp = temp->next; 
            } 
            push(curV->setEntry, temp->start, temp->end); //pushing last element
            push(curV->setEntry, origin->start, origin->end); //adding new element to new set
            
            lastV->next = curV;
            lastV = curV;
            curV = malloc(sizeof(setList)); //create new empty set list
            createSetList(curV); 
        } 
        totalSets *= 2;
        lastR->next = rootV; //linking newly created sets to master list
        lastR = lastV;
    }
    return R;
}

int main(void) {
    set *I = malloc(sizeof(set));
    createSet(I);
    int or = order(I);
    printf("Set is %d, contents: %d|%d\n", or, I->start, I->end);
    printf("Pushing first element\n");
    push(I, 2, 4);
    printf("Pushing second element\n");
    push(I, 3, 5);
    printf("Pushing third element\n");
    push(I, 7, 10);
    printf("%d, %d\n", I->start, I->end);
    printf("___________________________");
    setList *PS = subsets(I, 3);
    setList *pr = PS;
    for(int i = 0; i < 8; i++) {
        printSet(pr->setEntry);
        pr = pr->next;
        printf("______________________________");
    }

    return 1;
}
