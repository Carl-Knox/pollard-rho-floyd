/*
 ============================================================================
 Name        : sfloyd.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Swarm cluster factoring using Pollard Rho Floyd
 ============================================================================
    Some Semiprimes for testing                         Factors
T15     502560280658509
T20     18567078082619935259
T30     350243405507562291174415825999                  75576435361433
T40     5705979550618670446308578858542675373983        72694838627523822433
T45     732197471686198597184965476425281169401188191   15877128246765026029153
T50     53468946676763197941455249471721044636943883361749

mpicc -o "sf" sfloyd.c prfloyd.c -lgmp
mpirun -np 64 sf
 ============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"
#include "gmp.h"

#define BASE 10

void prfloyd(mpz_t factor, const mpz_t n, mpz_t start);

int
main()
{   /* Start MPI **************************************************************/
    MPI_Init(NULL, NULL);                                 // start up MPI
    int cores;                                            // number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &cores);                // get # of processes
    int rank;                                             // rank this process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);                 // get process rank

    /* Assign Data ************************************************************/
    mpz_t RANK;    mpz_init_set_ui(RANK, rank);           // set to a Biginteger
    mpz_t CORES;   mpz_init_set_ui(CORES, cores - 1);     // set to a Biginteger
    mpz_t factor;  mpz_init_set_ui(factor, 1);            // set to a Biginteger
    mpz_t seed;    mpz_init_set_ui(seed, 8);              // set to a Biginteger
    mpz_t n;       mpz_init_set_ui(n, 0);                 // set to a Biginteger
    int limit = 230;
    char buff[limit];
    int tag = 0;                                          // tag for messages
    int source = 0;                                       // rank of sender
    MPI_Status status;                                    // status for received
    char* rtn;                                            // fgets return status

    /* Input data & distribute it *********************************************/
    if(rank == 0)                                         // the control node
    {   printf("\n rank %d input\n", rank);               // prompt input
        rtn = fgets(buff, limit, stdin);                  // alternate input
        for(int dest = 1; dest < cores; dest++)           // send to each node
        {   MPI_Send(buff, limit, MPI_CHAR,
                dest, tag, MPI_COMM_WORLD);
        } // end for
        printf("\n[Swarm floyd] Processing with %d cores\n", cores);
    } else                                                // a compute node
    {   MPI_Recv(buff, limit, MPI_CHAR,
            source, tag, MPI_COMM_WORLD, &status);        // receive buff
    } // end if/else

    /* Algorithm **************************************************************/
    mpz_set_str(n, buff, 10);                             // move buff to 'n'
    mpz_add(seed, seed, RANK);                            // seed += rank
    prfloyd(factor, n, seed);                             // factor

    /* Output *****************************************************************/
    printf("rank %d factor = ", rank);                    // each core reports
    mpz_out_str(stdout, BASE, factor);    printf("\n");

    /* Clean up ***************************************************************/
    MPI_Finalize();                                       // shut down MPI
    return 0;
} // end main
