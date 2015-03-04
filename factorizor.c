/*
 * File: factorizor.c
 * Author: Ian S. Cohee
 *
 * Will print all the factors of N, [1, N]
 *
 * Must be compiled with "-lm" flag for math.h functions
 * */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h>

char const *usage = "[!] Usage: %s <N>\n[!] N should be >= 4.\n";

/*
 * sortFactors
 * @param: Reference to an array of factors that were generated sequenatially
 * @param: size of the array of factors
 * @return: malloc'd reference to array of sorted numbers
 * */
unsigned long long* sortFactors(unsigned long long** factors, unsigned long long size) {
    unsigned long long i, ii, *sortedFactors;
    unsigned long long midway = (size-1)/2;

    sortedFactors = (unsigned long long *) malloc(sizeof(unsigned long long) * size);
    if(sortedFactors == NULL) {
        fprintf(stderr, "[!] ERROR: Could not allocate space. Dieing at line: %u.\n", __LINE__);
        exit(1);
    }

    // Walk through the array
    for(i=0, ii=0; ii <= midway; i += 2, ++ii) {
        sortedFactors[ii] = (*factors)[i];
        sortedFactors[size-1-ii] = (*factors)[i+1];
    }

    // If the set represents a perfect square,
    // there will be an odd number of factors
    if((size & 0x1) == 1) {
        sortedFactors[midway] = (*factors)[size-1];
    }

    return sortedFactors;
}

/*
 * Main
 * @param: N
 * */
int main(int argc, char *argv[]) {
    unsigned long long i, N, arraySize, factorsIter, *factors, *sortedFactors;

    if(argc < 2) {
        printf(usage, argv[0]);
        exit(1);
    }

    N = atoll(argv[1]);
    if(N < 4) {
        printf(usage, argv[0]);
        exit(1);
    }

    arraySize = (size_t) sizeof(unsigned long long) * 2 * floor(sqrt(N));
    factors = (unsigned long long *) malloc(arraySize);
    if(factors == NULL) {
        fprintf(stderr, "[!] ERROR: Could not allocate space. Dieing at line: %u.\n", __LINE__);
        exit(1);
    }

    bzero(factors, arraySize);

    printf("[*] N: %llu\n", N);
    printf("[*] Pairs: \n");
    for(i=1, factorsIter=0; i <= floor(sqrt(N)); ++i) {
        if(N % i == 0) {
            printf("... {%llu, %llu}\n", i, N/i);

            if(i == (N/i)) {
                // Perfect Square factors
                factors[factorsIter++] = i;
            } else {
                // Factors, but not the same number
                factors[factorsIter++] = i;
                factors[factorsIter++] = N/i;
            }
        }
    }

    printf("[*] |factors(%llu)| = %llu\n", N, factorsIter);
    sortedFactors = sortFactors(&factors, factorsIter);

    printf("[*] Set:\n... {\n");
    for(i=0; i < factorsIter; ++i) {
        printf((i != factorsIter-1) ? "... ... %llu,\n" : "... ... %llu\n", sortedFactors[i]);
    }
    printf("... }\n");

    printf("[*] Complete.\n");

    free(factors);
    free(sortedFactors);

    printf("[*] Memory freed. Exiting.\n");
    return 0;
}
