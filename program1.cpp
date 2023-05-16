#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;

/**
 * Neatly prints out an array.
 * 
 * @param  {int} arrayPtr
 * @param  {int} size 
 */
void printArr(int* arrayPtr, int& size){

    // prints all elements of array w/o spacing
    for(int i = 0; i < size; i++){
        cout << arrayPtr[i];
    }
    cout << endl;
};


/**
 * Converts a decimal number to its
 * binary representation.
 * 
 * @param  {int} array
 * @param  {int} decvalue
 * @param  {int} size 
 */
void DecToBin(int* array, int& decvalue, int& size){
    
    // iteration variable (professor said loop 
    // variables can be disregarded)
    int k = 0;

    // writes binary representation to array
    // in reverse order
    while(decvalue > 0){

        // decimal to binary logic
        array[k++] = decvalue % 2;
        decvalue /= 2;
        
    }

    // pads binary value w/ zeros to equal array size
    for(int i = k; i < size; i++){
        array[i] = 0;
    }

    // reverses order of binary representation
    int j = size - 1;
    for(int i = 0; i < j; i++){

        // stores current bit
        int temp = array[i];

        // swaps right bit to left bit
        array[i] = array[j];

        // sets left bit to current bit
        array[j] = temp;

        // decrements reverse iterative value
        j--;
    }

    // prints binary value
    cout << "Binary Representation: ";
    printArr(array, size);

};


/**
 * Converts a one's complement number to its
 * two's complement equivalent.
 * 
 * @param  {int} OnesArray
 * @param  {int} size 
 */
void TwosComp(int* OnesArray, int& size){

    // initializes carry value 
    int* carryVal = new int;
    *carryVal = 1;

    // adds 1 bit to one's complement value
    for(int i = size - 1; i >= 0; i--){
        
        // adds 1 to current bit and stores in 'sum' 
        int* sum = new int;
        *sum = OnesArray[i] + *carryVal;

        // sets current bit to either 0/1
        // depending if sum is even/odd
        OnesArray[i] = *sum % 2;

        // sets carry value to respective carry
        *carryVal = *sum / 2;
        
        // breaks loop if carry is 0
        if(*carryVal == 0){
            break;
        }
    }

    // prints two's complement value
    cout << "Two's Complement: ";
    printArr(OnesArray, size);
    
};


/**
 * Converts a binary number to its
 * one's complement equivalent.
 * 
 * @param  {int} array
 * @param  {int} size 
 */
void OnesComp(int* array, int& size){

    // flips all bits in binary value 
    for(int i = 0; i < size; i++){

        // flips to either 0/1 using
        // basic conditional logic
        if(array[i] == 1){
            array[i] = 0;
        } 
        else {
            array[i] = 1;
        }
    }

    // prints one's complement value
    cout << "One's Complement: ";
    printArr(array, size);
};


/**
 * Checks whether decimal number is valid integer.
 * 
 * @returns {int} decimal
 */
int getDecimal()
{
    // variable to store decimal #
    int* decimal = new int;

    // checks if decimal is an integer > 0
    while (!(cin >> *decimal) && (*decimal > 0))
    {
        cout << "Invalid input, enter decimals only: ";

        // clears cin
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return *decimal;
}


/**
 * Checks whether input for bit system type is valid integer.
 * 
 * @param  {int} sizeNeeded
 * @returns {int} bits
 */
int getBitSystem(int& sizeNeeded)
{
    // variable to store bit system 
    int* bits = new int;

    // checks if bit system is an integer >= sizeNeeded
    while (!(cin >> *bits) || (*bits < sizeNeeded))
    {
        cout << "Input must be an integer >= " << sizeNeeded << ". Please try again (i.g 4/8/16/32/64): ";
        
        // clears cin
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return *bits;
}


/**
 * Takes in user input for a decimal number and
 * bit system, then returns binary representation, 
 * one's complement, and two's complement.
 */
int main(){
    
    // initializes value to store user input
    int* num = new int;
    *num = 0;

    // initialize bit system variable
    int* bsys = new int;
    *bsys = 0;

    // initializes exit prompt variable
    char* exitFlag = new char;
    *exitFlag = ' ';

    // runs until user enters 'q' at end prompt
    do {

        // prompts user for decimal number
        cout << "Enter a Decimal Number: ";

        // checks if input is valid decimal number
        *num = getDecimal();

        // find minimum array size needed for its binary equiv.
        int* sizeNeeded = new int; 
        *sizeNeeded = ceil(log2(*num));

        // prompts user for bit system
        cout << "Enter a Bit System (e.g. 4/8/16/32/64): ";
        *bsys = getBitSystem(*sizeNeeded);

        // checks if bsys input is a valid number 
        if (*bsys >= pow(2, *bsys))
        {
            cout << "Size that you indicated is not enough to represent " << *num << endl;

            // prompts bit system again
            continue;
        }

        // initializes array to store decimal number
        int* array = new int[*bsys];

        // calls number-conversion functions
        DecToBin(array, *num, *bsys);
        OnesComp(array, *bsys);
        TwosComp(array, *bsys);

        // checks if user wants to continue
        cout << "Enter 'q' to exit program, else enter any other key: ";
        cin >> *exitFlag;

        // deletes array
        delete[] array;

    } while (*exitFlag != 'q');

    return 0;
 
};