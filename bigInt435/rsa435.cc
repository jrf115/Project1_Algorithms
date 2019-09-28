// You need to complete this program for a part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>


// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

// My function implementations for doing the Fermat Test
void makePrime(BigUnsigned &p);
bool fermatTest(BigUnsigned p);

int main(){
	/* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
	try {
	  std::cout << "Implementing Fermat Test\n";
	  BigUnsigned p, q, e(3);
	  makePrime(p);
	  std::cout << "P is equal to: " << p << std::endl;
	  makePrime(q);
	  std::cout << "Q is equal to: " << q << std::endl;
	  std::ofstream file;
	  file.open("p_q.txt");
	  file << p << '\n' << q;
	  file.close();

	  BigUnsigned n = p * q ;
	  BigUnsigned theta_N = (p - 1) * (q - 1);	// Will need to convert to BigInteger later

	  // Find odd number e that is relatively prime to n
	  while (gcd(e, theta_N) != 1)
	  	e += 2;
	  std::cout << "Found e: " << e << std::endl;

	  //  Compute d, which is the multiplicative inverse of e
	  BigInteger d, int_quot;
	  BigInteger myGCD = theta_N * e;

	  // I'm Doing this to help throw out confusion of conflicting information of documentation vs notes:
	  /***********	    m ,  n   ,  g  ,r,   s    corresponds to the eE equation: r*m + s*n == g		*********/
	  extendedEuclidean(e,theta_N,myGCD,d,int_quot);
	  //std::cout << "Using extended euclidean algorithm " << "e is: " << e << "\nand d is: " << d << "\nand int_quot is: " << int_quot << "\nand theta_N is: " << theta_N << "\nand myGCD is: " << myGCD << std::endl;
	  std::cout << "Found d: " << d << std::endl;

	  // Public Key
	  file.open("e_n.txt");
	  file << e << '\n' << n;
	  file.close();
	  // Private Key
	  file.open("d_n.txt");
	  file << d << '\n' << n;
	  file.close();

	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}


	return 0;
}

/* This Function checks whether a bigUnsigned number that isn't one is prime or not,
 * and will return a bool according to that value.
 */
bool fermatTest(BigUnsigned p)
{
	if (modexp(BigInteger(95), p-1, p) != 1) // single 1 being "1 mod p"
		return false;
	if (modexp(BigInteger(96), p-1, p) != 1) // single 1 being "1 mod p"
		return false;
	if (modexp(BigInteger(99), p-1, p) != 1) // single 1 being "1 mod p"
		return false;
	return true;
}

/* This function tries to generates a likely prime number */
void makePrime(BigUnsigned &p)
{
	bool prime = false;
	while (!prime) {
		p = 1;
		for (int i(0); i < 400; i++)
			p = p * 10 + rand();
		prime = fermatTest(p);
	}

}
