#include <stdio.h>
#include "vernam.h"
#include "debug_helper.h"
#include "file_reader.h"
#include "vector.h"

enum {
    ENCRYPT,
    DECRYPT
};

int OPERATION;

char *input_file;
char *input_key;

SecureData* myData;

void encrypt(char*);
void decrypt(char*, char*);

char* program_name;

int main(int argc, char** argv) {
    int c;
    program_name = *argv;
    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch(c) {
                case 'e':
                    OPERATION = ENCRYPT;
                    break;
                case 'd':
                    OPERATION = DECRYPT;
                    break;
            }

    if ((OPERATION == ENCRYPT && argc < 1) || (OPERATION == DECRYPT && argc < 2)) {
        printf("USAGE : %s -e <file to encrypt> \n"
                "%s -d <file to decrypt> <file key>\n", program_name, program_name);
        return 0;
    }

    //di(OPERATION);
    //di(argc);
    //ds(*argv);

    /* Initialize my SecureData */
    myData = newSecureData(encrypt_vernam, decrypt_vernam);

    printf("\nVERNAM XOR ENCRYPTION - A Highly Secure One-Time Pad ----------------------------\n");

    switch (OPERATION) {
        case ENCRYPT:
            encrypt(*argv);
            printf("\n%s is now Encrypted in %s_encrypted, Key stored in %s_key\n\n", *argv, *argv, *argv);
            break;
        case DECRYPT: {
                char* fileName = *argv;
                char* fileKey = *++argv;
                decrypt(fileName, fileKey);
                printf("\n%s is now decrypted into file: message\n\n", fileName);
            }
            break;
    }


    /*
    myData -> message = new_string("SATYAJIT GHANA");
    char* key;
    myData -> encrypt(myData, &key);
    ds(myData -> message);
    ds(key);
    myData -> decrypt(myData, key);
    ds(myData -> message);*/

    return 0;
}

void encrypt(char* file_name) {
    char* to_encrypt = read_string_file(file_name);
    ds(to_encrypt);

    myData -> message = to_encrypt;
    myData -> isEncrypted = false;
    char* key;
    myData -> encrypt(myData, &key);

    char* output_file = strcat(new_string(file_name), "_encrypted");
    char* output_key = strcat(new_string(file_name), "_key");
    /* now write the key and the encrypted data */
    write_string_file(output_file, myData -> message);
    write_string_file(output_key, key);
}

void decrypt(char* file_name, char* key) {
    char* to_decrypt = read_string_file(file_name);
    char* decryption_key = read_string_file(key);

    //ds(to_decrypt);
    //ds(decryption_key);

    myData -> message = to_decrypt;
    myData -> isEncrypted = true;
    myData -> decrypt(myData, decryption_key);

    ds(myData -> message);

    char* output_file = "message_decrypted";
    write_string_file(output_file, myData -> message);
}
