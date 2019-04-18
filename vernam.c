#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include "vernam.h"
#include "debug_helper.h"

SecureData* newSecureData(int (*encryptAlgo)(SecureData*, char**),
        int (*decryptAlgo)(SecureData*, char*)) {

    SecureData* myData = (SecureData*) malloc(sizeof *myData);
    if (myData == NULL) return NULL;
    myData -> isEncrypted = false;
    myData -> message = NULL;
    myData -> encrypt = encryptAlgo;
    myData -> decrypt = decryptAlgo;

    return myData;
}

/* pass a &char* to this method, and it encrypts the data and stores the key in the
 * parameter passed */
int encrypt_vernam(SecureData* myData, char** key) {
    if (myData -> isEncrypted)
        return -1;

    if (myData -> message == NULL)
        return -1;

    /* Encrypt the Data and store the key */

    *key = malloc(strlen(myData -> message) * sizeof **key);
    char *encrypted = malloc(strlen(myData -> message) * sizeof *encrypted);

    int i; srand(time(0));
    for (i = 0 ; i < strlen(myData -> message); i++) {
        (*key)[i] = 65 + rand()%(CHAR_MAX-65);
        encrypted[i] = (myData -> message)[i] ^ (*key)[i];
    }
    encrypted[i] = (*key)[i] = '\0';
    free(myData -> message);
    myData -> message = encrypted;
    myData -> isEncrypted = true;

    return 0;
}

int decrypt_vernam(SecureData* myData, char* key) {
    if (!myData -> isEncrypted)
        return -1;

    if (myData -> message == NULL)
        return -1;

    /* Decrypt the data using the Key */
    char* decrypted = malloc(strlen(myData -> message) * sizeof *decrypted);

    int i;
    for (i = 0 ; i < strlen(key) ; i++) {
        decrypted[i] = (myData -> message)[i] ^ key[i];
    }
    decrypted[i] = '\0';
    free(myData -> message);
    myData -> message = decrypted;
    myData -> isEncrypted = false;

    return 0;
}
