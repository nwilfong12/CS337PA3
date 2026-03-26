/*********************************************************************
* Author: Nicholas Wilfong
* Created: December 13, 2026
*
* The program contains a way to encrypt and decrypt strings
**********************************************************************/
#include <stdlib.h>
#include "utils.h"



/*
* It gets the length of the string
* input - the string we are counting
* output - the length of the string as an int
*/
int get_length(const char *s){
    int i = 0;
    while(s[i] != '\0'){
        i++;
    }

    return i;
}


/*
* Checks whether a particular character in the string is a Letter
* input - char
* output - 1 for true 0 for false
*/
int is_letter(char c){
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}


/*
* Checks whether a particular character in the string is a digit
* input - char
* output - 1 for true 0 for false
*/
int is_digit(char c){
    return (c >= '0' && c <= '9');
}


/*
* Implements the two above methods(is_digit and is_letter) to see if the entire string is valid
* input - string
* output - 1 for true 0 for false
*/
int is_valid(const char *s){
    int len = get_length(s);

    if(len < 2 || len > 20){
        return 0;
    }
        int valid = 0;

        for(int i = 0; i < len; i++){
            if(is_letter(s[i]) || is_digit(s[i])){
                valid = 1;
                break;
            }
        }
        return valid;

}


/*
* Encrypts the string
* input - a string
* output - the encrypted value of the original string
*/
char *encrypt(const char *input){
    if(!is_valid(input)){
        usage();
        return NULL;
    }

    int len = get_length(input);

    char *result = malloc(len + 1);
    int shift = len;


    for(int i = 0; i < len; i++){
        char c = input[i];

        if(c >= 'a' && c<= 'z'){
            result[i] = 'a' + ((c - 'a' + shift) % 26);
        }
        else if(c >= 'A' && c <= 'Z'){
            result[i] = 'A' + ((c - 'A' + shift) % 26);
        }
        else{
            result[i] = c;
        }
    }
    result[len] = '\0';
    return result;
}

/*
* The function decrypts the already encrypted string
* input - the encrypted string
* output - the original string
*/  
char *decrypt(const char *input){
    if(!is_valid(input)){
        usage();
        return NULL;
    }

    int len = get_length(input);
    int shift = len;

    char *result = malloc(len + 1);

    for(int i = 0; i < len; i++){
        char c = input[i];

        if(c >= 'a' && c <= 'z'){
            result[i] = 'a' + ((c-'a' - shift + 26) % 26);
        }
        else if(c >= 'A' && c <= 'Z'){
            result [i] = 'A' + ((c -'A' - shift + 26) % 26);     
        }
        else{
            result[i] = c;
        }
    }
    result[len] = '\0';
    return result;
}
