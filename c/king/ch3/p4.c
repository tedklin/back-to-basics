// phone

#include <stdio.h>

int main() {
    while (1) {
        int p1, p2, p3;
        printf("Enter phone number [(xxx) xxx-xxxx]: ");

        // https://stackoverflow.com/a/18478817
        // note that a malformed input will trigger an infinite loop
        scanf(" (%3d) %3d-%4d", &p1, &p2, &p3);

        printf("You entered: %d.%d.%d\n\n", p1, p2, p3);
    }
}
