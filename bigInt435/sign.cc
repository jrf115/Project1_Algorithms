/* John Fahringer
 * Algorithms Fall 2019
 * sign.cc  - Part2 of Project1
 * This part will Generate and verify digigal signatures using a SHA-256 hash
 **/

 // Standard libraries
 #include <string>
 #include <iostream>
 #include <stdlib.h>
 #include <fstream>
 #include <sstream>


 // 'BigIntegerLibrary.hh' includes all of the library headers.
 #include "BigIntegerLibrary.hh"
 #include "BigIntegerUtils.hh"
 #include "sha256.h" /** Program by Olivier Gay */


using std::ifstream;
using std::ofstream;
using std::string;
using std::cout;
using std::endl;

string signHash(const string &hash, const BigUnsigned &d, const BigUnsigned &n);

// main function needs parameters since we need command line arguments
int main(int argc, char *argv[]) {
    try {
        std::cout << "sign.exe loaded\n";
        BigUnsigned d, e, n;
        string d_String, e_String, n_String, content, line;
        string filename = argv[2];
        ifstream file, secret;
        ofstream sign_File;
        /** Step 1: Sign a given file */
        if (*argv[1] == 's')
        {   // Execute if told to sign
            // Generate a SHA-256 hash of the content of the file to be signed
            cout << "Reading " << filename << endl;
            file.open(filename);
            content.assign( std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() ); // stores entire file content
            cout << "Content : " << content << endl;
            if (content.empty())
            {
                cout << "Error: File '" << filename << "' is empty or unavailible." << endl;
                return 0;
            }
            file.close();
            // cout << "file content reads: " << content << endl;
            string sign_this_Content = sha256(content);
            // cout << "sha256(content) reads: " << sign_this_Content << endl;
            file.open("d_n.txt");
            getline(file, d_String);
            getline(file, n_String);
            file.close();
            d = stringToBigUnsigned(d_String);
            n = stringToBigUnsigned(n_String);
            if (d_String.empty())
            {
                cout << "Error: d_n.txt is missing or doesn't have enough information";
                return 0;
            }
            cout << "d_String reads: " << d_String << endl << "n_String reads: " << n_String << endl;

            // Sign/"decrypt" this hash value using the private key stored in d_n.txt;
            string signed_Message = signHash(sign_this_Content, d, n);
            sign_File.open(filename + "signature");
            sign_File << signed_Message << endl << content;
            sign_File.close();
        }

    }  catch(char const* err) {
        std::cout << "The library threw an exception:\n"
            << err << std::endl;
    }


    return 0;
}

/** This function will sign the incoming hash with Private Key(d,n) **/
string signHash(const string &hash, const BigUnsigned &d, const BigUnsigned &n)
{
    // modinv();
}
