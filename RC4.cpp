#include <stdio.h>
#include <string.h>
#define N 256
void swap(unsigned char *a, unsigned char *b) {
    unsigned char temp = *a;
    *a = *b;
    *b = temp;
}
void KSA(unsigned char *key, int key_len, unsigned char *S) {
    int i, j = 0;
    for (i = 0; i < N; i++) {
        S[i] = i;
    }
    for (i = 0; i < N; i++) {
        j = (j + S[i] + key[i % key_len]) % N;
        swap(&S[i], &S[j]);
    }
}
void RC4(unsigned char *input, int len, unsigned char *key, int key_len, unsigned char *output) {
    unsigned char S[N];
    int i = 0, j = 0, k, t;
    KSA(key, key_len, S);
    for (k = 0; k < len; k++) {
        i = (i + 1) % N;
        j = (j + S[i]) % N;
        swap(&S[i], &S[j]);
        t = (S[i] + S[j]) % N;
        unsigned char K = S[t]; 

        output[k] = input[k] ^ K;
    }
}
int main() {
    unsigned char key[] = "secret";
    unsigned char plaintext[] = "Hello RC4";
    int len = strlen((char*)plaintext);
    unsigned char ciphertext[100];
    unsigned char decrypted[100];
    RC4(plaintext, len, key, strlen((char*)key), ciphertext);
    printf("Ciphertext: ");
    for (int i = 0; i < len; i++) {
        printf("%02X ", ciphertext[i]);
    }
    RC4(ciphertext, len, key, strlen((char*)key), decrypted);
    decrypted[len] = '\0';
    printf("\nDecrypted: %s\n", decrypted);
    return 0;
}