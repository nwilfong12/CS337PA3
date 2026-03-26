/*******************************************************************
* Description: This program tests the functionality of text encryption and decryption.
*
* How to Run:
* Run make to compile the program. 
* After compiling, run the executable with ./cipher
*******************************************************************/

#include "utils.h"

int failed_tests = 0; 
int testcase = 1;

void usage() {
    printf("Error: Invalid input. Length must be 2–20 characters inclusive and contain at least one letter or digit.\n");
}

void custom_assert(int testcase, int condition, char *msg, char* expected, char* actual) {
    if (condition) {
        printf("Testcase %d succeeded: %s (Expected: %s, Actual: %s)\n\n", testcase, msg, expected, actual ? actual : "NULL");
    } else {
        printf("\033[31mTestcase %d failed: %s (Expected: %s, Actual: %s)\033[0m\n\n", testcase, msg, expected, actual ? actual : "NULL");
        failed_tests++;
    }
}

int main() {
       // Blank string should be rejected by encrypt
    char *enc1 = encrypt("");
    custom_assert(testcase++, enc1 == NULL, "Blank input rejected by encrypt", "NULL", enc1);

    // Blank string should be rejected by decrypt
    char *dec1 = decrypt("");
    custom_assert(testcase++, dec1 == NULL, "Blank input rejected by decrypt", "NULL", dec1);


    // Length 1 string should be rejected by encrypt
    char *enc2 = encrypt("m");
    custom_assert(testcase++, enc2 == NULL, "Length < 2 rejected by encrypt", "NULL", enc2);

    // Length 1 string should be rejected by decrypt
    char *dec2 = decrypt("b");
    custom_assert(testcase++, dec2 == NULL, "Length < 2 rejected by decrypt", "NULL", dec2);

    /// String with only whitespace should be rejected
    char *enc4 = encrypt("   \t   ");
    custom_assert(testcase++, enc4 == NULL,"Whitespace-only input rejected by encrypt", "NULL", enc4);

    // Whitespace-only string should also be rejected by decrypt
    char *dec4 = decrypt("   \t   ");
    custom_assert(testcase++, dec4 == NULL,"Whitespace-only input rejected by decrypt", "NULL", dec4);


     // Encrypt wraparound case
    char *enc12 = encrypt("xyz");
    custom_assert(testcase++, enc12 && strcmp(enc12,"abc")==0, "Alphabet wraparound during encrypt", "abc", enc12);

    // Decrypt wraparound case
    char *dec12 = decrypt(enc12);
    custom_assert(testcase++, dec12 && strcmp(dec12,"xyz")==0, "Alphabet wraparound during decrypt", "xyz", dec12);

    free(enc12);
    free(dec12);

    // Encrypt a multi-word string
    char *enc7 = encrypt("attack at dawn");
    custom_assert(testcase++, enc7 && strcmp(enc7,"ohhoqy oh rokb")==0, "Encrypt a multi-word string", "ohhoqy oh rokb", enc7);

    // Decrypt a multi-word string
    char *dec7 = decrypt(enc7);
    custom_assert(testcase++, dec7 && strcmp(dec7,"attack at dawn")==0, "Decrypt a multi-word string", "attack at dawn", dec7);

    free(enc7);
    free(dec7);


    // Encrypt a multi-word string
    char *enc8 = encrypt("temp password sent");
    custom_assert(testcase++, enc8 && strcmp(enc8,"lweh hskkogjv kwfl")==0, "Encrypt a multi-word string", "lweh hskkogjv kwfl", enc8);

    // Decrypt a multi-word string
    char *dec8 = decrypt(enc8);
    custom_assert(testcase++, dec8 && strcmp(dec8,"temp password sent")==0, "Decrypt a multi-word string", "temp password sent", dec8);

    free(enc8);
    free(dec8);

    // Encrypt a string containing special characters
    char *enc5 = encrypt("send #backup");
    custom_assert(testcase++, enc5 && strcmp(enc5,"eqzp #nmowgb")==0, "Encrypt string containing special characters", "eqzp #nmowgb", enc5);

    // Decrypt a string containing special characters
    char *dec5 = decrypt(enc5);
    custom_assert(testcase++, dec5 && strcmp(dec5,"send #backup")==0, "Decrypt string containing special characters", "send #backup", dec5);

    free(enc5);
    free(dec5);


    // Encrypt a short string including digits and symbols
    char *enc6 = encrypt("transfer $900");
    custom_assert(testcase++, enc6 && strcmp(enc6,"genafsre $900")==0, "Encrypt a short string including digits and symbols", "genafsre $900", enc6);

    // Decrypt a short string including digits and symbols
    char *dec6 = decrypt(enc6);
    custom_assert(testcase++, dec6 && strcmp(dec6,"transfer $900")==0, "Decrypt a short string including digits and symbols", "transfer $900", dec6);

    free(enc6);
    free(dec6);

    // Encrypt string containing only non-alphabetic characters
    char *enc11 = encrypt("5#16755(>)");
    custom_assert(testcase++, enc11 && strcmp(enc11,"5#16755(>)")==0, "Non alphabetic characters unchanged during encrypt", "5#16755(>)", enc11);

    // Decrypt string containing only non-alphabetic characters
    char *dec11 = decrypt(enc11);
    custom_assert(testcase++, dec11 && strcmp(dec11,"5#16755(>)")==0, "Non alphabetic characters unchanged during decrypt", "5#16755(>)", dec11);

    free(enc11);
    free(dec11);

    // Reject overly long string in encrypt 
    char *enc10 = encrypt("backup keys in locker");
    custom_assert(testcase++, enc10 == NULL, "Overlength input rejected by encrypt", "NULL", enc10);


    // Reject overly long string in decrypt
    char *dec10 = decrypt("Gvs gqcfsr wg bnm hhhhhhhhhhhhh qcz.");
    custom_assert(testcase++, dec10 == NULL, "Overlength input rejected by decrypt", "NULL", dec10);


    printf("\n============== SUMMARY =======================\n");
    printf("TESTCASES PASSED: %d out of %d\n", (testcase - 1 - failed_tests), (testcase-1));
    printf("==============================================\n");

    return (failed_tests == 0) ? 0 : 1;

}