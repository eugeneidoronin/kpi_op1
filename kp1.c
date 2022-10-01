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
int check(double side1, double side2, double side3);//is used to stop or continue the code
double area(double len[N_SIDES], int p); // finds the area of tg
double height(double len[N_SIDES], int index, double root); //finds height
double medians(double side1, double side2, double side3);// finds median
double bisector(double , double , double, double p);//finds bisector

int main() {
    do //cycle to loop the whole program
    {
        int test = 0; //flag value
        double p = 0; //perimeter
        double lengths[N_SIDES]; //arr with all the lengths of the sides
        for (int i=0; i<N_SIDES; i++){
            printf("print the length of the side %c of the triangle in cm:", sides[i]);
            scanf("%lf", &lengths[i]);//%lf- specificator for double &-adrres of the object
        }
        for (int num = 0; num < N_SIDES; num++) {
            if (lengths[num] < 0) { //checks the side not to be negative
                printf("[ERROR] the length cant be negative :c");
                test++;
                break;
            }
            if (!check(lengths[indecies[N_SIDES*num]],lengths[indecies[N_SIDES*num+1]], \
            lengths[indecies[N_SIDES*num+2]])) { //checks the main equality of triangle
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
                printf("to %c: height = %.2f cm; bisector = %.2f cm; median = %.2f cm\n", sides[i],
                       height(lengths, i, root), \
                       bisector(lengths[indecies[N_SIDES*i]],lengths[indecies[N_SIDES*i+1]],\
                       lengths[indecies[N_SIDES*i+2]],p / 2),//e.g. i=0: indecies[3*0+1]
                       medians(lengths[indecies[N_SIDES*i]],lengths[indecies[N_SIDES*i+1]], \
                       lengths[indecies[N_SIDES*i+2]]));
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

int check(double side1, double side2, double side3){
    int ret = 0;
    if (side2 + side3 > side1) {
        return ret + 1;
    }
    else return ret;
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

double medians(double side1, double side2, double side3){
    return 0.5 * sqrt(2 * pow(side2, 2) + 2 * pow(side3, 2) -
                      pow(side1, 2));
}

double bisector(double side1, double side2, double side3, double p) {
    return (2 / (side2 + side3)) * sqrt(side2 * side3 * p * (p - side1));
}
