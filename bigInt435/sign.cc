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
        string filename, signed_filename;
        ifstream file, secret, signed_File;
        ofstream sign_File;

        /** Step 1: Sign a given file */
        if (*argv[1] == 's')
        {   // Execute if told to sign
            // Generate a SHA-256 hash of the content of the file to be signed
            filename = argv[2];
            cout << "Reading " << filename << endl;
            file.open(filename);
            content.assign( std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() ); // stores entire file content
            cout << "Content : " << content << endl;
            if (content.empty())
            {
                cout << "Error: File '" << filename << "' is empty or unavailible." << endl;
                exit(0);
            }
            file.close();
            string sign_this_Content = sha256(content);

            file.open("d_n.txt");
            file >> d_String;
            file >> n_String;
            file.close();
            d = stringToBigUnsigned(d_String);
            n = stringToBigUnsigned(n_String);
            if (d_String.empty() || n_String.empty())
            {
                cout << "Error: d_n.txt is missing or doesn't have enough information";
                exit(0);
            }

            // Sign/"decrypt" this hash value using the private key stored in d_n.txt;
            string signed_Message = signHash(sign_this_Content, d, n);

            // Save the signature to "file.txt.signature"
            sign_File.open(filename + ".signature");
            sign_File << signed_Message << endl << content;
            sign_File.close();
            cout << "Message signed. Exiting...\n";
        }
        /* Step 2: Verify the signed file */
        else if (*argv[1] == 'v')
        {
            filename = argv[2];
            signed_filename = argv[3];

            // Load necessary files
            // Obtain the signature from the signature file
            signed_File.open(signed_filename);
            string signature;
            signed_File >> signature;
            cout << "Signature is: " << signature << endl;
            signed_File.close();
            if (signature.empty())
            {
                cout << "error: " << signed_filename << " is either empty or missing.\n";
                exit(0);
            }

            file.open(filename);
            content.assign( std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() ); // stores entire file content
            file.close();
            if (content.empty())
            {
                cout << "error: " << filename << " is either empty or missing.\n";
                exit(0);
            }

            file.open("e_n.txt");
            file >> e_String;
            file >> n_String;
            cout << "n is " << n_String << endl;
            file.close();
            if (e_String.empty() || n_String.empty())
            {
                cout << "error: " << "e or n are empty\n";
                exit(0);
            }
            e = stringToBigUnsigned(e_String);
            n = stringToBigUnsigned(n_String);

            // SHA256 the content of the file and
            // Compare the SHA-256 hash value of the content and the “encrypted” signature
            string hashed_content = sha256(content);
            BigUnsignedInABase base16_content(hashed_content, 16);
            BigUnsigned bigUnsigned_content(base16_content);

            BigUnsignedInABase base16_signature(signature, 16);
            BigUnsigned bigUnsigned_signature(base16_signature);

            // Use the decryption formula: where m = bigUnsigned_signature, and (m^d % n) = signature  (the encrypted);
            /** ((m^d % n)^e) % n **/
            BigUnsigned decrypted = modexp(bigUnsigned_signature, e, n);
            cout << "The decrypted is :" << decrypted << endl << "The content is :" << bigUnsigned_content << endl;
            if (decrypted.compareTo(bigUnsigned_content) != 0)
                cout << "Your file has been modified!\n";
            else
                cout << "Your message has not been modified.\n";
        }

    }  catch(char const* err) {
        std::cout << "The library threw an exception:\n"
            << err << std::endl;
    }


    return 0;
}

/** This function will sign the incoming hash with Private Key(d,n) **/
/** Use hash = 'm', in the encyryption equation signature = m^d mod n  to get signature **/
string signHash(const string &hash, const BigUnsigned &d, const BigUnsigned &n)
{
    // Convert the hash's 16 bit number into its 10 bit number version.
    // modexp expects base10...
    BigUnsignedInABase base16_hash(hash, 16); // String to base16
    BigInteger bigInt_hash(base16_hash); // base16 to base10
    // The signature equation
    BigUnsigned bigUnsigned_signature = modexp(bigInt_hash,d,n);
    BigUnsignedInABase base16_signature(bigUnsigned_signature, 16);
    return base16_signature;
}
