/* Copyright (c) 2018 Jeffrey Lund
** Full search of a series of overlapping intervals 
** Number of jobs defined by argv 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct set {
    int *subset;
    int order;
    struct set *next;
} set;

//Copies the elements from a source set then adds in an additional element
void Union(set *dest, set *source, int start, int end) {
    dest->order = source->order + 1;
    int *sub = malloc(2*dest->order*sizeof(int));
    
	if(source->order == 0) { //if the source is the empty set
		sub[0] = start;
		sub[1] = end;
	}
	else {
    	for(int i = 0; i < source->order; i++) {
        	sub[i] = source->subset[i];
        	sub[i+dest->order] = source->subset[i+(source->order)];
    	}
    	sub[source->order] = start;
    	sub[2*source->order+1] = end;
    }

    dest->subset = sub;
}

// Creates and returns all subsets of a given set. N is the order of the set  
set* createSubsets(int* masterSet, int n) {
    int totalSets = 1; //empty set
    //T <- Empty set 
    set *T = malloc(sizeof(set));
    T->subset = NULL;
    T->order = 0;
    T->next = NULL;
    set *last = T, *root = T, *current;
    //for e in S
    for(int i = 0; i < n; i++) {
		current = root;
        for(int j = 0; j < totalSets; j++) {
			if(j != 0)
				 current = current->next;
			set *temp = malloc(sizeof(set));
			Union(temp, current, masterSet[i], masterSet[i+n]);
			last->next = temp;
			last = temp;
		}
		totalSets *= 2;
    }
	last->next = NULL;

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

//finds a set containing the maximum numbers of non overlapping jobs
set* movieJobs(set *powerset, int n) {
    set *jobsMax = malloc(sizeof(set));
    jobsMax->order = 0;
    set *search = powerset;
    for(int i = 0; i < pow(2, n); i++) {
        if(i != 0)
            search = search->next;
        if(search->order <= jobsMax->order)
           continue;
        else if(hasOverlaps(search->subset, search->order))
            continue;
        jobsMax->subset = search->subset;
        jobsMax->order = search->order;
    }
    
	return jobsMax;
}

int main(int argc, char *argv[]) {
	srand(time(NULL));
    char *_n = argv[1];
	int n = atoi(_n); //number of intervals from 
    int* masterSet = malloc(2*n*sizeof(int)); //base set of intervals to build subsets from

    for(int i = 0; i < n; i++) { //random set generation
		masterSet[i] = rand()%(4*n);
		int delta = (4*n) - masterSet[i];
		masterSet[i+n] = (rand()%delta + masterSet[i]);
    }

    set *jobsMax = movieJobs(createSubsets(masterSet, n), n);

    printf("\nAcceptable max subset is: {");
    for(int i = 0; i < jobsMax->order; i++) {
        printf("(%d, %d)", jobsMax->subset[i], jobsMax->subset[i+jobsMax->order]);
    }
    printf("}\n");
    
    return 0;
}
