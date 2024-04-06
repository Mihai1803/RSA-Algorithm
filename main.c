#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 250

int public_key;
int private_key;
int n;

int prime_numbers[SIZE];
int no_primes;

long long int encoded[SIZE];
long long int decoded[SIZE];
int code = 0;
int decode = 0;


// Generate all the prime numbers in the 0..SIZE interval
void prime_generator() {
    int sieve[SIZE], i;

    sieve[0] = 0;
    sieve[1] = 0;
    for (i = 2; i < SIZE; i++) {
        sieve[i] = 1;
    }

    for (i = 2; i * i < SIZE; i++) {
        if (sieve[i] == 1) {
            int j;
            for (j = 2; j < SIZE / i; j++) {
                sieve[j * i] = 0;
            }
        }
    }

    no_primes = 0;
    for (i = 0; i < SIZE; i++) {
        if (sieve[i] == 1) {
            prime_numbers[no_primes] = i;
            no_primes++;
        }
    }
}

// returns the greatest common divisor
int greatest_common_divisor(int a, int b) {

    int r;
    while (b != 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

// pick random prime number
int pick_random_prime() {
    int number;
    int k = rand() % no_primes, i;

    for (i = 0; i < no_primes; i++) {
        if (i == k) {
            number = prime_numbers[i];
            break;
        }
    }

    return number;
}

// set public and private key
void set_keys() {
    int prime1 = pick_random_prime();
    int prime2 = pick_random_prime();
    n = prime1 * prime2;

    int fi = (prime1 - 1) * (prime2 - 1);

    int e = 2;
    while (1) {
        if (greatest_common_divisor(e, fi) == 1) {
            break;
        }
        e++;
    }
    public_key = e;

    int d = 2;
    while (1) {
        if ((d * e) % fi == 1) {
            break;
        }
        d++;
    }
    private_key = d;
}

// encrypt message
long long int encrypt(int message) {
    int e = public_key;
    long long int encrypted_message = 1;
    while (e) {
        encrypted_message = encrypted_message * message;
        encrypted_message = encrypted_message % n;
        e--;
    }
    return encrypted_message;
}

// decrypt message
long long int decrypt(int encrypted_message) {
    int d = private_key;
    long long int decrypted_message = 1;
    while (d) {
        decrypted_message = decrypted_message * encrypted_message;
        decrypted_message = decrypted_message % n;
        d--;
    }
    return decrypted_message;
}


// utility function to encode the message using the encrypt function
void encoder(char *message) {
    int i;
    code = 0;
    for (i = 0; i < strlen(message); i++) {
        encoded[code] = encrypt((int)message[i]);
        code++;
    }
}


// utility function to decode the message using the decrypt function
void decoder() {
    int i;
    for (i = 0; i < code; i++) {
        decoded[decode] = decrypt(encoded[i]);
        decode++;
    }
}


int main()
{
    int i;

    prime_generator();
    set_keys();

    char message[SIZE] = "message";
    printf("Initial message: %s\n", message);

    encoder(message);

    printf("Encoded message: ");
    for (i = 0; i < code; i++) {
        printf("%d", encoded[i]);
    }

    decoder();

    printf("\nDecoded message: ");
    for (i = 0; i < decode; i++) {
        printf("%c", (char)decoded[i]);
    }

    return 0;
}
