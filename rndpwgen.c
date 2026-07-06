/*
 * rndpwgen
 *
 * Tiny offline Base58 password generator.
 *
 * Platform-specific entropy is abstracted by rnd().
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __APPLE__

static uint32_t rnd(uint32_t upper)
{
    return arc4random_uniform(upper);
}

#elif defined(__linux__)

#include <sys/random.h>

static uint32_t rnd(uint32_t upper)
{
    uint32_t value;
    uint32_t limit = UINT32_MAX - (UINT32_MAX % upper);

    do {
        if (getrandom(&value, sizeof(value), 0) != sizeof(value)) {
            perror("getrandom");
            exit(EXIT_FAILURE);
        }
    } while (value >= limit);

    return value % upper;
}

#else
#error "Unsupported platform"
#endif


#define LEN(x) (sizeof(x) - 1)

// Generate a random password of length N.
void randomPasswordGeneration(int N)
{
	// Initialize counter
	int i = 0;

	// Base58 character set.
	// Ambiguous characters ('0', 'O', 'I', 'l') intentionally omitted.
    
	const char digit[] = "123456789";
	const char lower[] = "abcdefghijkmnopqrstuvwxyz";
	const char upper[] = "ABCDEFGHJKLMNPQRSTUVWXYZ";
	// const char symbols[] = "_#!~^+=-&@";

	// Password buffer (+1 for terminating null byte).
	char password[N + 1];

	// Character class selected for the next character.
	enum CharType {
	    DIGIT,
	    UPPER,
	    LOWER
	};

	// Initialize our enum randomizer
	enum CharType randomizer = DIGIT;

	// Iterate over the range [0, N]
	for (i = 0; i < N; i++) {

		if (i == 0) {  // Begin our password with a digit. Legacy BTC wallet vibe.
			password[i] = digit[rnd(LEN(digit))];
			randomizer = (enum CharType)rnd(3);
		} 

		else if (randomizer == DIGIT) {
			password[i] = digit[rnd(LEN(digit))];
			randomizer = (enum CharType)rnd(3);
		}
		
		else if (randomizer == UPPER) {
			password[i] = upper[rnd(LEN(upper))];
			randomizer = (enum CharType)rnd(3);
		}
		else {
			password[i] = lower[rnd(LEN(lower))];
			randomizer = (enum CharType)rnd(3);
		}
	}

	password[N] = '\0';  // Null-terminate the password string.
	printf("%s\n", password);
}


int main(int argc, char *argv[])
{
	// If length parameter of password argument is missing
	if(argc<=1) {
        printf("Expecting length of password as an argument. Usage: rndpwgen <password length>\n");
        exit(1);
    } 
	
	int N = atoi(argv[1]);

	// Generate and display the password.
	randomPasswordGeneration(N);

	return 0;
}
