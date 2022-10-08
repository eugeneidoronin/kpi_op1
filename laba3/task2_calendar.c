#include <stdio.h> //just to printf and scanf
#include <string.h>//strcmp in flag()
#include <math.h>// all math

#define N_INPUT 3
#define QUIT "yes\0"

char days[7][10] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

int flag(); // asks to continue
int n_value(int, int);
int day_f(int, int, int);
int check(int, int, int);

int main() {
    do {
        int day, month, year;
        printf("enter the date DD/MM/YYYY: ");
        scanf("%d/%d/%d", &day, &month, &year);
        if (check(day, month, year))
            switch (day_f(day, month, year)) {
                case 0:
                    printf("Monday");
                    break;
                case 1:
                    printf("Tuesday");
                    break;
                case 2:
                    printf("Wednesday");
                    break;
                case 3:
                    printf("Thursday");
                    break;
                case 4:
                    printf("Friday");
                    break;
                case 5:
                    printf("Saturday");
                    break;
                case 6:
                    printf("Sunday");
                    break;
            }
        else printf("[ERROR] invalid input");

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

int check(day, month, year){
    int chck=1;
    if (month<0 || month>12 || day>31 || year<0) chck--;
    else if (month == 4 ||month == 6 || month == 1 || month == 9 ||month == 11 &&day>30 ) chck--;
    else if (year%100!=0 && year%4==0 && month ==2 &&day >29) chck--;
    else if (month ==2 &&day >28) chck--;
    return chck;
}

int n_value(int month, int year){
    int n=0;
    if (month <= 2 && year%100!=0 && year%4==0) n++;
    else
        if(month <= 2 ) n+=2;
    return n;
}
int day_f(int day, int month, int year){
    int weekday= (int)(floor(365.25*year)+floor(30.56*month)+day + n_value(month, year))%7;
    return weekday;
}