#include <cstring>
#include <string>
#include <bdd.h>
#include "bvec.h"

int adder(int nbits);

main(void){
  int nbits = 4;
  adder(nbits);
}

/* Function template for custom Boolean function
int function_name(int nbits)
{
    // Initialization for BuDDy
    bdd_init(100,1000);
    bdd_setvarnum(2*nbits);
    bdd output_variable_0, output_variable_1;

    // Declare inputs as bit vectors, change number of variables, offset and step as required
    bvec a = bvec_var(nbits,0, 2);
    bvec b = bvec_var(nbits,1, 2);

    // Recommeded to use variable re-ordering for custom functions, for which optimal variable order is not known
    bdd_reorder(BDD_REORDER_SIFT); // change argument to explore various re-ordering algorithms

    // Generate ROBDD for custom function
    // Define custom function here

    // Generate file name (.bdd file, output in BuDDy format)
    std::string fname_str = "function_name-"+std::to_string(nbits)+".bdd";
    char fname_char[fname_str.size()+1];
    std::strcpy(fname_char, fname_str.c_str());

    bdd_fnsave(fname_char, output_variable0); // Print ROBDD in BuDDy format

    bdd_done();

    return 0;
}
*/

// Binary addition for n-bit Boolean formula
// Outputs MSB of carry
int adder(int nbits)
{
   // Initialization for BuDDy
   bdd_init(100,1000);
   bdd_setvarnum(2*nbits);
   bdd sum, carry;

   // Declare inputs as bit vectors
   bvec a = bvec_var(nbits,0, 2);
   bvec b = bvec_var(nbits,1, 2);

   // Generate ROBDD for MSB of n-bit addition
   for (int n=0; n < nbits; n++){
     if (n==0){
       sum = bdd_xor(a[n], b[n]); // Compute sum for LSB
       carry = bdd_and(a[n], b[n]); // Compute carry for LSB
     }
     else{
       sum = bdd_xor(bdd_xor(a[n], b[n]), carry); // Compute sum for all other bits
       carry = bdd_or(bdd_and(a[n], b[n]), bdd_and(carry, bdd_xor(a[n], b[n]))); // Compute carry for all other bits
     }
   }

   // // Generate file name (.dot file)
   // std::string fname_str = "adder-"+std::to_string(nbits)+".dot";
   // char fname_char[fname_str.size()+1];
   // std::strcpy(fname_char, fname_str.c_str());
   //
   // bdd_fnprintdot(fname_char, sum); // Print ROBDD as .dot file

   // // Generate file name (.bdd file, output in BuDDy format)
   std::string fname_str = "adder-"+std::to_string(nbits)+".bdd";
   char fname_char[fname_str.size()+1];
   std::strcpy(fname_char, fname_str.c_str());

   bdd_fnsave(fname_char, carry); // Print ROBDD in BuDDy format

   bdd_done();

   return 0;
}
