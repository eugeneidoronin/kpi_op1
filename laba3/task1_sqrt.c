#include <stdio.h> //just to printf and scanf
#include <string.h>//strcmp in flag()
#include <math.h>// all math

#define N_INPUT 3
#define QUIT "yes\0"

enum values {
    x, k, e
};
char value[N_INPUT] = {'x', 'k', 'e'};

int flag(); // asks to continue
int check(double []);
double y_search(double []);
int dig_count2(double);

int main() {
    do {
        double inputs[N_INPUT]; //arr with all the lengths of the sides
        for (int i = x; i <= e; i++) {
            printf("print the value of %c:  ", value[i]);
            scanf("%lf", &inputs[i]);
        }
        if (check(inputs)) {
            int precision = dig_count2(inputs[e]);
            if (inputs[k] > 0)
                printf("%.*f", precision, y_search(inputs));
            else
                printf("%.*f", precision, 1 / y_search(inputs));
            //The width specification can be an asterisk (*), in which case an argument from the argument list supplies the value.
            //The width argument must precede the value being formatted in the argument list.
        }
    } while (flag()); //returns 1 if 'no' - I do not want to quit the program
    return 0;
}

int flag() {//analyzes the input yes or no
    char resp[N_INPUT];
    printf("\nare you sure that you wanna quit? [yes/no]\n ");
    scanf("%s", &resp);
    if (strcmp(resp, QUIT) == 0) return 0;//checks if 'yes'- means I want to quit, function strcmp from <string.h>
    else return 1;
}

int check(double inputs[]) {
    int test = 1;
    if (!(int) inputs[k]) {
        printf("[ERROR] k cant be 0 :c");
        return test - 1;
    }

    if (inputs[k] > 0)
        if ((int) inputs[k] % 2 == 0 && inputs[x] < 0) {
            printf("[ERROR] x cant be negative if k is even");
            return test - 1;
        }

    if (inputs[k] < 0)
        if ((int) inputs[k] % 2 == 0 && inputs[x] <= 0) {
            printf("[ERROR] x cant be below zero if if k is even and negative");
            return test -1;
        } else if ((int) inputs[k] % 2 != 0 && inputs[x] == 0) {
            printf("[ERROR] x cant be 0 is k is odd and negative");
            return test -1;
        }
    return test;
}

int dig_count2(double e) {
    int count = 0;
    while ((int) e < 1) {
        e = e * 10;
        count++;
    }
    return count;
}

double y_search(double inputs[]) {
    double y = 1;
    double delta = 1;
    if (inputs[k] < 0) inputs[k] = -1 * inputs[k];
    while (fabs(delta) > fabs(inputs[e])) {
        delta = (1 / inputs[k]) * (inputs[x] / pow(y, inputs[k] - 1) - y);
        y += delta;
    }
    return y;
}
