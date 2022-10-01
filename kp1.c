#include <stdio.h> //just to printf and scanf
#include <string.h>//strcmp in flag()
#include <math.h>// all math

#define N_SIDES 3 // const variable for n sides
#define QUIT "yes\0"//global variable

char sides[N_SIDES] = {'A', 'B', 'C'}; //names of the sides
int indecies[N_SIDES * N_SIDES] = { 0, 1, 2, 1, 2, 0, 2, 0, 1} ; // indecies of indecies
/*
i:0   0 1 2
i:1   1 2 0
i:2   2 0 1
-> 0 1 2 2 0 1 1 2 0
<- 0 1 2 1 2 0 2 0 1
*/
int flag(); // asks to continue
int check(double len[N_SIDES], int index); //is used to stop or continue the code
double area(double len[N_SIDES], int p); // finds the area of tg
double height(double len[N_SIDES], int index, double root); //finds height
double medians(double len[N_SIDES], int index); // finds median
double bisector(double len[N_SIDES], int index, double p);//finds bisector
double bisector2(double , double , double, double p);//finds bisector

int main() {
    do //cycle to loop the whole program
    {
        int test = 0; //flag value
        double p = 0; //perimeter
        double lengths[N_SIDES]; //arr with all the lengths of the sides
        printf("print the length of the side A of the triangle in cm:");
        scanf("%lf", &lengths[0]);//%lf- specificator for double &-adrres of the object
        printf("print the length of the side B of the triangle in cm:");
        scanf("%lf", &lengths[1]);
        printf("print the length of the side C of the triangle in cm:");
        scanf("%lf", &lengths[2]);
        for (int num = 0; num < N_SIDES; num++) {
            if (lengths[num] < 0) { //checks the side not to be negative
                printf("[ERROR] the length cant be negative :c");
                test++;
                break;
            }
            if (!check(lengths, num)) { //checks the main equality of triangle
                printf("[ERROR] sorry this triangle does not exist :c");
                test++;
                break;
            }
            p += lengths[num]; //sum for perimeter
        }
        if (!test) //if all the input was correct - no negative sides and t-le does exist
        {
            double root = area(lengths, p / 2); //root == area^2
            printf("area equals %.2f cm\n", sqrt(root));
            printf("perimeter = %.2f cm\n", p);
            for (int i = 0; i < N_SIDES; i++) {
                printf("to %c: height = %.2f cm; bisector = %.2f / %.2f cm; median = %.2f cm\n", sides[i],
                       height(lengths, i, root), \
                       bisector(lengths, i, p / 2),
                       bisector2(lengths[indecies[N_SIDES*i]],lengths[indecies[N_SIDES*i+1]], lengths[indecies[N_SIDES*i+2]],p / 2),
                       medians(lengths, i));
            }
        }
    } while (flag()); //returns 1 if 'no' - I do not want to quit the program
    return 0;
}

int flag() {//analyzes the input yes or no
    char resp[N_SIDES];
    printf("\nare you sure that you wanna quit? [yes/no]\n ");
    scanf("%s", &resp);
    if (strcmp(resp, QUIT) == 0) return 0;//checks if 'yes'- means I want to quit, function strcmp from <string.h>
    else return 1;
}

int check(double len[N_SIDES], int index) {
    int ret = 0;
    switch (index) {//different cases depending on which side are we examining now
        case 0:
            if (len[1] + len[2] > len[0]) {
                ret += 1;
                break;
            }
            else break; //main equation:one side is smaller than the sum of other two
        case 1:
            if (len[0] + len[2] > len[1]) {
                ret += 1;
                break;
            }
            else break;
        case 2:
            if (len[0] + len[1] > len[2]) {
                ret += 1;
                break;
            }
            else break;
    }
    return ret;
}

double area(double len[N_SIDES], int p) {
    double root = p;
    for (int num = 0; num < N_SIDES; num++) { //cycle to (p-num) where num is a or b or c
        root *= (p - len[num]); //using the formula area = sqrt(p(p-a)(p-b)(p-c)
    }
    return root;
}

double height(double len[N_SIDES], int index, double root) {
    return (2 * sqrt(root)) / len[index]; //the formula: (2*sqrt(p(p-a)(p-b)(p-c))/side which is being examined
}

double medians(double len[N_SIDES], int index) {
    switch (index) {//depending on wat side is being examined
        case 0:
            return 0.5 * sqrt(2 * pow(len[1], 2) + 2 * pow(len[2], 2) -
                              pow(len[0], 2));//the formula: 0.5*sqrt(2b^2+2c^2-a^2) (median to a)
        case 1:
            return 0.5 * sqrt(2 * pow(len[0], 2) + 2 * pow(len[2], 2) - pow(len[1], 2));
        case 2:
            return 0.5 * sqrt(2 * pow(len[0], 2) + 2 * pow(len[1], 2) - pow(len[2], 2));
    }
}

double bisector(double len[N_SIDES], int index, double p) {
    switch (index) {//depending on wat side is being examined
        case 0:
            return (2 / (len[1] + len[2])) * sqrt(len[1] * len[2] * p * (p -
                                                                         len[0]));//the formula: (2/b+c)*sqrt(bcp(p-a)) where p is half perimeter
        case 1:
            return (2 / (len[0] + len[2])) * sqrt(len[0] * len[2] * p * (p - len[1]));
        case 2:
            return (2 / (len[1] + len[0])) * sqrt(len[1] * len[0] * p * (p - len[2]));
    }
}
double bisector2(double side1, double side2, double side3, double p) {
    return (2 / (side2 + side3)) * sqrt(side2 * side3 * p * (p - side1));
}
