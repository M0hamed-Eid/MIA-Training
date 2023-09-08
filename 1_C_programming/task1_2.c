#include <stdio.h>
#include <unistd.h> // this for sleep function

int main() {
    int startNumber;
	
	wrong_input:
    // take input from the user
    printf("Enter the number to start the countdown from: ");
    scanf("%d", &startNumber);

    // to make sure that he entered a +ve num
    if (startNumber <= 0) {
        printf("Please enter a positive integer greater than 0\n");
        goto wrong_input;
    }

    // countdown loop
    for (int i = startNumber; i >= 1; --i) {
        printf("%d\n", i);
        sleep(1); // 1-second delay
    }

    printf("Blast off to the moon!\n");

    return 0;
}
