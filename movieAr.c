#include <stdio.h>
#include <stdlib.h>

typedef struct set {
    int *subset;
    int order;
    struct set *next;
} set;

//exponent function
int power(int x, int y) {
    int sum = x;
    for(int i = 0; i < y-1; i++)
        sum *= x;
    return sum;
}

//Copies the elements from a source set then adds in an additional element
void Union(set *dest, set *source, int start, int end) {
    int n = source->order + 1;
    int *sub = malloc(2*n*sizeof(int));
    
    for(int i = 0; i < (n-1); i++) {
        sub[i] = source->subset[i];
        sub[i+n] = source->subset[i+(n-1)];
    }
    sub[n-1] = start;
    sub[2*n-1] = end;
    
    dest->order = n;
    dest->subset = sub;
    return;
}

// Creates and returns all subsets of a given set. N is the order of the set  
set* subsets(int* masterSet, int n) {
    int totalSets = 2;
    //T <- Empty set 
    set *T = malloc(sizeof(set));
    int *init = malloc(2*sizeof(int));
    init[0] = masterSet[0];
    init[1] = masterSet[n];
    T->subset = init;
    T->order = 1;
    T->next = NULL;
    set *lastT = T;
    //for e in S
    for(int i = 1; i < n; i++) {
        //V = empty set
        set *V = malloc(sizeof(set));
        int *first = malloc(2*sizeof(int));
        first[0] = masterSet[i];
        first[1] = masterSet[i+n];
        V->order = 1;
        V->subset = first;
        V->next = NULL;
        set *rootV = V, *lastV = V;
        //for W in T
        set *W = T;
        for(int j = 0; j < totalSets-1; j++) {
            //insert (W union E) in V
            if(j != 0) W = W->next;
            set *E = malloc(sizeof(set));
            E->next = NULL;
            Union(E, W, masterSet[i], masterSet[i+n]);
            lastV->next = E;
            lastV = E;  
        }
        totalSets *= 2;
        //T <- union W
        lastT->next = rootV;
        lastT = lastV;
    }

    return T;    
}

// Checks to see if the subset has overlapping elements. Returns true if no overlapping elements exist
int hasOverlaps(int *S, int order) {
    for(int i = 0; i < order; i++) {
        for(int j = 0; j < order; j++) {
            if(i == j) 
                continue;
            else if( (S[i] >= S[j] && S[i] < S[j+order]) || (S[j] >= S[i] && S[j] < S[i+order])) 
                return 1; 
        }
    }
    return 0;
}

int main(void) {
    int n;
    printf("Number of entries: ");
    scanf("%d", &n);
    int* masterSet = malloc(2*n*sizeof(int));

    for(int i = 0; i < n; i++) {
        printf("Enter start end: ");
        scanf("%d %d", &masterSet[i], &masterSet[i+n]);
    }

    set *powerset = subsets(masterSet, n);
    set *Jmax = malloc(sizeof(set));
    Jmax->order = 0;
    set *search = powerset;
    for(int i = 0; i < (power(2, n)-1); i++) {
        if(i != 0) 
            search = search->next;
        if(search->order <= Jmax->order)
           continue;
        else if(hasOverlaps(search->subset, search->order))
            continue;
        Jmax->subset = search->subset;
        Jmax->order = search->order;
    }
    printf("\nAcceptable max subset is: {");
    for(int i = 0; i < Jmax->order; i++) {
        printf("(%d, %d)", Jmax->subset[i], Jmax->subset[i+Jmax->order]);
    }
    printf("}\n");
    
/************************test print of power sets****************
    set *root = powerset;
    int count = power(2, n);
    for(int i = 0; i < count-1; i++) {
        int* temp = root->subset;
        int or = root->order;
        printf("%d: {", i);
        for(int j = 0; j < or; j++) {
            printf("(%d,%d)", temp[j], temp[j+or]);
        }
        printf("}\n");
        root = root->next;
    }
****************************************************************/
    return 0;
}
