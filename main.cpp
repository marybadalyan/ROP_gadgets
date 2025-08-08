#include <stdio.h>
#include <string.h>


void vulnerable() {
    char buffer[64];
    printf("Input something: ");
    scanf("%s", buffer); // 🚨 vulnerable function (never use in real life!)
}

int main() {
    vulnerable();
    return 0;
}
