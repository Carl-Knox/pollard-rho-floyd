# pollard-rho-floyd
Parallel Multicore Semiprime Factoring Pollard Rho Floyd, OpenMPI, GMP.

 Pollard rho algorithm using Floyd's implementation in C using the GMP library 
 to find a prime factor given a number with OpenMPI for parallel processing.
 Seems to work ok on shorter semiprimes.(< T40)
 
 Note: When compiling, specify the path to gmp.h using the -I flag if it is
 not automatically found by the compiler and make sure to compile with the
 -lgmp flag as well. E.g. gcc -I/usr/local/include/ main.cpp -lgmp
 
 Sample Semiprines                                      Factor
T15     502560280658509
T20     18567078082619935259
T30     350243405507562291174415825999                  75576435361433
T40     5705979550618670446308578858542675373983        72694838627523822433
T45     732197471686198597184965476425281169401188191   15877128246765026029153
T50     53468946676763197941455249471721044636943883361749

mpicc -o "sf" sfloyd.c floyd.c -lgmp           // input sfloyd.c & floyd.c
mpirun -np 64 sf                               // core count 64, name sf
 ============================================================================
