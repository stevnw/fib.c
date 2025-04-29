// Calculate Fibonacci Numbers -This program was written by Softwave: https://s0ftwave.net/ - I made some modifications :D
// Added save to txt prompt (Y/n) -> F(900).txt saved -> exits program
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <gmp.h>
#include <time.h>
#include <string.h>

long limit, i = 0;

int main(int argc, char *argv[])
{
    // Get User Input
    if (argc != 2)
    {
        printf("Improper input, Exiting.\n");
        printf("Usage: %s <number>\n", argv[0]);
        return -1;
    }
    limit = strtol(argv[1], NULL, 10);
    
    // Setup GMP
    mpz_t a, b, c;
    mpz_init_set_ui(a, 1);
    mpz_init_set_ui(b, 0);
    mpz_init(c);
    
    // Start timing
    clock_t start_time = clock();
    for (i = 0; i < limit; i++)
    {
        // Perform the Fibonacci Calculation
        mpz_add(c, a, b);
        mpz_set(a, b);
        mpz_set(b, c);
    }
    // End timing
    clock_t end_time = clock();
    
    // Print the result to stdout
    printf("F(%ld) = ", i);
    mpz_out_str(stdout, 10, b);
    printf("\n");
    
    // Print time taken
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Calculation Time: %f seconds\n", time_taken);
    
    // Prompt user to save result to a text file
    char response;
    printf("Save to txt file? (Y/n): ");
    scanf(" %c", &response);
    
    if (response == 'Y' || response == 'y' || response == '\n')
    {
        // Create filename based on the Fibonacci number calculated
        char filename[20];
        sprintf(filename, "F(%ld).txt", i);
        
        // Open file for writing
        FILE *file = fopen(filename, "w");
        if (file == NULL)
        {
            printf("Error opening file for writing.\n");
            
            // Cleanup
            mpz_clear(a);
            mpz_clear(b);
            mpz_clear(c);
            return -1;
        }
        
        // Write result to file
        fprintf(file, "F(%ld) = ", i);
        mpz_out_str(file, 10, b);
        fprintf(file, "\n");
        fprintf(file, "Calculation Time: %f seconds\n", time_taken);
        
        // Close file
        fclose(file);
        printf("%s saved -> exiting program\n", filename);
    }
    else
    {
        printf("File not saved. Exiting program.\n");
    }
    
    // Cleanup
    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(c);
    
    return 0;
}
