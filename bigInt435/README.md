John Fahringer
Project 1 - Part 2
=

How to run part1 code
=
Using the initial Makefile that was assigned with the initial project, use

	make all

to compile the rsa program. Then use

	./rsa435

to execute the program. It will generate prime numbers, public and private key files to be used in part2 program "sign". To clean object code, do

	make clean

How to run part2 code
=
Using the provided Makefile, Use the command:

	make all

to compile the code for part 2 in project 1. You must download and include the sha256 program files by Olivier Gay, which is located
at http://www.zedwood.com/article/cpp-sha256-function  
To clean object files use the command:

	make clean

Once you compile, run the sign program by doing ./sign. To sign an existing "file_a" do

    ./sign file_a

To verify the existing "file_a" do

    ./sign v file_a file_a.signature

Program Information
=
This project generates RSA keys that can be used for generating and verifying digital signatures using a SHA256 hash of any simple files you have. It uses the BigInt class by Matt McCutchen to help generate the large numbers required to implement, and Olivier's SHA256 program to hash the file content. 
