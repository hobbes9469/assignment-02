/* ----------------------------------------------------------------------------
* Copyright &copy; 2015 Ben Blazak <bblazak@fullerton.edu>
*                  2015 TODO(Matthew Kang) <TODO(matthesk@fullerton.edu)>
* Released under the [MIT License] (http://opensource.org/licenses/MIT)
* ------------------------------------------------------------------------- */

/**
* A program to read unsigned integers from a text file and separate them into
* two files, one for primes, another for composites.
*/


#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <fstream>
using std::ifstream;
using std::ofstream;

/**
* Find the maximum unsigned integer in `infilename`.
*
* Arguments:
* - `infilename`: A string representing the file path to open.
*     - Note: Since the string will not be changed, we declare it `const`.
*       Since strings are objects (and therefore larger than fundamental
*       types), we avoid copying it by passing it by reference.
*
* Returns:
* - The maximum integer, or `-1` on error.
*     - Note: It would be better style in C++ to throw an exception, but we
*       haven't learned about those yet.
*/
int find_max(const string& infilename);

/**
* Mark all prime indices in `primes` as `true` and all others as `false` using
* the Sieve of Eratosthenes algorithm.
*
* Arguments:
* - `size`: The size of (the number of elements in) the array.
* - `primes`: An array of boolean values.
*
* Notes:
* - The number `2` is the smallest prime.
* - When arrays are passed to functions, they decay into pointers (even though
*   arrays and pointers are not the same thing).  Thus what this function is
*   actually receiving is a pointer to the first element of the array `primes`
*   in `main()` (it doesn't make much difference for how we're using it in
*   this function, but the distinction is important).  This pointer is passed
*   by value, but the data inside the array is not passed at all: we access it
*   through the pointer.
* - It might be better to return the array from the function rather than pass
*   the array and modify it, but the syntax is relatively uncommon, and might
*   be confusing.
*/
void sieve(const int size, bool primes[]);

/**
* Read numbers from `infilename`, and if they are prime, output them to
* `outfilename`, separated by newlines.
*
* Arguments:
* - `size`: The size of (the number of elements in) the array.
* - `primes`: An array of boolean values, with each element set to `true` if
*   its index is prime, and `false` otherwise.
* - `infilename`: A string representing the file path to read from.
* - `outfilename`: A string representing the file path to write to.
*
* Returns:
* - 0 on success, or -1 on error.
*/
int write_primes(const int size,
	bool primes[],
	const string& infilename,
	const string& outfilename);

/**
* Read numbers from `infilename`, and if they are composite, output them to
* `outfilename`, separated by newlines.
*
* Arguments:
* - `size`: The size of (the number of elements in) the array.
* - `primes`: An array of boolean values, with each element set to `true` if
*   its index is prime, and `false` otherwise.
* - `infilename`: A string representing the file path to read from.
* - `outfilename`: A string representing the file path to write to.
*
* Returns:
* - 0 on success, or -1 on error.
*/
int write_composites(const int size,
	bool primes[],
	const string& infilename,
	const string& outfilename);

// ----------------------------------------------------------------------------

int main() {
	int max = find_max("input.txt");
	if (max == -1) {
		cout << "ERROR in `find_max()`" << endl;
		return 1;  // error
	}
	
	bool primes[max + 1];				// This particular part gives an error in Visual Studio, but if I hard code it, it works, no idea how to fix
	sieve(max + 1, primes);

	

	//for (int value = 0; value < 11; value++) {
	//	cout << primes[value] << endl;
	//}
	//cin.get();



	int ret;  // for storing return values, to check for error codes
	//
	ret = write_primes(max + 1, primes, "input.txt", "primes.txt");
	if (ret == -1) {
		cout << "ERROR in `write_primes()`" << endl;
		return 1;  // error
	}
	//
	ret = write_composites(max + 1, primes, "input.txt", "composites.txt");
	if (ret == -1) {
		cout << "ERROR in `write_composites()`" << endl;
		return 1;  // error
	}

	return 0;  // success
}

// ----------------------------------------------------------------------------

// TODO: write prototyped functions



int find_max(const string& infilename) {			//The find_max definition
	ifstream inputFile;
	inputFile.open(infilename);
	int inputnumber;
	int theMaximum = 0;
	while (inputFile >> inputnumber) {
		if (inputnumber > theMaximum) {
			theMaximum = inputnumber;
		}
	}
	inputFile.close();
	return theMaximum;
}

void sieve(const int size, bool primes[]) {			//The sieve definition
	int count = 0;
	int divisor;
	for (count; count < size; count++) {
		if (count == 1) {
			primes[count] = 0;
		}
		if (count == 2) {
			primes[count] = 1;
		}
		for (divisor = 2; divisor < count; divisor++) {
			if (count % divisor == 0) {
				primes[count] = 0;
				break;
			}
			else {
				primes[count] = 1;
			}
		}
	}
}




int write_primes(const int size,					//The write_primes definition
	bool primes[],
	const string& infilename,
	const string& outfilename) {
	ifstream inputFile;
	inputFile.open(infilename);

	ofstream outputFile;
	outputFile.open(outfilename);

	int inputnumber;
	while (inputFile >> inputnumber) {
		if (primes[inputnumber] == 1) {
			outputFile << inputnumber << endl;
		}
	}

	outputFile.close();
	return 0;
}

int write_composites(const int size,					//The write_composites definition
	bool primes[],
	const string& infilename,
	const string& outfilename) {
	ifstream inputFile;
	inputFile.open(infilename);

	ofstream outputFile;
	outputFile.open(outfilename);

	int inputnumber;
	while (inputFile >> inputnumber) {
		if (primes[inputnumber] == 0) {
			outputFile << inputnumber << endl;
		}
	}

	outputFile.close();
	return 0;
}
