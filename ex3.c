/******************
Name:
ID:
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};


void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}


void initCube(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int daysInYear, int numOfBrands, int numOfTypes){
    #define initVal -1
    for (int i = 0; i < daysInYear; i++){
        for (int j = 0; j < numOfBrands; j++){
            for (int k = 0; k < numOfTypes; k++)
                cube[i][j][k] = initVal;
        }
    }
}


int getBrand(){
    int brandSelected;
    scanf("%d", &brandSelected);
    while (brandSelected < 1 || brandSelected > NUM_OF_BRANDS){
        printf("This brand is not valid\n");
        scanf("%d", &brandSelected);
    }
    return brandSelected;
}


void enterDailyBrandData(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int daysInYear, int numOfBrands, int numOfTypes, int day, int brand){
    int suvSales, sedanSales, coupeSales, gtSales;
    for (int i = 0; i < numOfTypes; i++){
        scanf("%d", &cube[day][brand][i]);
    }
}


void printMissingBrands(int brandsEntered[NUM_OF_BRANDS])
{
    printf("No data for brands ");
    for (int i = 0; i < NUM_OF_BRANDS; i++){
        if (brandsEntered[i] == 0)
            printf("%s ", brands[i]);
    }
    printf("\nPlease complete the data.\n");
}


int getBrandForDailyData(int brandsEntered[], int numOfBrands){
    int brandSelected;
    scanf("%d", &brandSelected);
    while (brandSelected < 0 || brandSelected > numOfBrands - 1 || (brandsEntered[brandSelected] == 1)){
        printf("This brand is not valid\n");
        printMissingBrands(brandsEntered);
        scanf("%d", &brandSelected);
    }
    return brandSelected;
}


void enterDailyData(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int daysInYear, int numOfBrands, int numOfTypes, int day){
    int brandsEntered[NUM_OF_BRANDS] = {0};
    int brandSelected;
    for (int i = 0; i < NUM_OF_BRANDS; i++){
        printMissingBrands(brandsEntered);
        brandSelected = getBrandForDailyData(brandsEntered, NUM_OF_BRANDS);
        enterDailyBrandData(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES, day, brandSelected);
        brandsEntered[brandSelected] = 1;
    }
}


int getValidDay(int maxDay){
    int daySelected;
    printf("What day would you like to analyze?\n");
    scanf("%d", &daySelected);
    daySelected--; // Translate to array index
    while(daySelected <= 0 || daySelected >= maxDay){
        printf("Please enter a valid day.\n");
        printf("Which day would you like to analyze?\n");
        scanf("%d", &daySelected);
        daySelected--;
    }
    return daySelected;
}


void printArrayCell(char array[], int index){
    printf("%s", array[index]);
}


int printTotalSales(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int daysInYear, int numOfBrands, int numOfTypes, int day){
    int totalSales = 0;
    for(int i = 0; i < numOfBrands; i++){
        for(int j = 0; j < numOfTypes; j++){
            totalSales += cube[day][i][j];
        }
    }
    printf("The sales total was %d\n", totalSales);
}

int printBestSoldBrandForDay(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int daysInYear, int numOfBrands, int numOfTypes, int day){
    int brandSales[NUM_OF_BRANDS] = {0}, maxSales = 0;
    for(int i = 0; i < numOfBrands; i++){
        for(int j = 0; j < numOfTypes; j++){
            brandSales[i] += cube[day][i][j];
            if (maxSales < brandSales[i])
                maxSales = brandSales[i];
        }
    }
    for(int i = 0; i < numOfBrands; i++){
        if(brandSales[i] == maxSales){
            printf("The best sold brand with %d sales was %s\n", brandSales[i], brands[i]);
        }
    }
}

void printBestSoldTypeForDay(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int daysInYear, int numOfBrands, int numOfTypes, int day){
    int typeSales[NUM_OF_TYPES] = {0}, maxSales = 0;
    for(int i = 0; i < numOfTypes; i++){
        for(int j = 0; j < numOfBrands; j++){
            typeSales[i] += cube[day][j][i];
            if (maxSales < typeSales[i])
                maxSales = typeSales[i];
        }
    }
    for(int i = 0; i < numOfBrands; i++){
        if(typeSales[i] == maxSales){
            printf("The best sold type with %d sales was %s\n", typeSales[i], types[i]);
        }
    }
}


void printStatsForDay(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int daysInYear, int numOfBrands, int numOfTypes, int maxDay){
    int daySelected;
    daySelected = getValidDay(maxDay);
printf("daySelected: %d\n", daySelected);
    printf("In day number %d:\n", daySelected + 1);
    printTotalSales(cube, daysInYear, numOfBrands, numOfTypes, daySelected);
    printBestSoldBrandForDay(cube, daysInYear, numOfBrands, numOfTypes, daySelected);
    printBestSoldTypeForDay(cube, daysInYear, numOfBrands, numOfTypes, daySelected);
}


void printAllData(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int daysInYear, int numOfBrands, int numOfTypes, int maxDay){
    for (int brand = 0; brand < NUM_OF_BRANDS; brand++){
        printf("Sales for %s:\n", brands[brand]);
        for (int day = 0; day < maxDay; day++){
            printf("Day %d- ", day);
            for (int type = 0; type < NUM_OF_TYPES; type++)
                printf("%s: %d ", types[type], cube[day][brand][type]);
            printf("\n");
        }
    }
}
/*
Sales for Toyoga:
Day 1- SUV: 1 Sedan: 1 Coupe: 1 GT: 1
Day 2- SUV: 1 Sedan: 1 Coupe: 1 GT: 1
Day 3- SUV: 1 Sedan: 1 Coupe: 1 GT: 1
Day 4- SUV: 1 Sedan: 1 Coupe: 1 GT: 1
Sales for HyunNight:
Day 1- SUV: 2 Sedan: 1 Coupe: 1 GT: 1
Day 2- SUV: 2 Sedan: 1 Coupe: 1 GT: 4
Day 3- SUV: 2 Sedan: 1 Coupe: 3 GT: 1
Day 4- SUV: 2 Sedan: 2 Coupe: 3 GT: 3
Sales for Mazduh:
Day 1- SUV: 1 Sedan: 1 Coupe: 1 GT: 3
Day 2- SUV: 1 Sedan: 1 Coupe: 1 GT: 3
Day 3- SUV: 1 Sedan: 1 Coupe: 1 GT: 3
Day 4- SUV: 1 Sedan: 1 Coupe: 1 GT: 3
Sales for FolksVegan:
Day 1- SUV: 1 Sedan: 1 Coupe: 1 GT: 1
Day 2- SUV: 20 Sedan: 1 Coupe: 1 GT: 1
Day 3- SUV: 1 Sedan: 1 Coupe: 1 GT: 1
Day 4- SUV: 1 Sedan: 1 Coupe: 1 GT: 1
Sales for Key-Yuh:
Day 1- SUV: 1 Sedan: 1 Coupe: 1 GT: 1
Day 2- SUV: 1 Sedan: 1 Coupe: 1 GT: 1
Day 3- SUV: 1 Sedan: 1 Coupe: 1 GT: 1
Day 4- SUV: 1 Sedan: 1 Coupe: 1 GT: 1


2
0 1 1 1 1
1 2 1 1 1
2 1 1 1 3
3 1 1 1 1
4 1 1 1 1
2
0 1 1 1 1
1 2 1 1 4
2 1 1 1 3
3 20 1 1 1
4 1 1 1 1
2
0 1 1 1 1
1 2 1 3 1
2 1 1 1 3
3 1 1 1 1
4 1 1 1 1
2
0 1 1 1 1
1 2 2 3 3
2 1 1 1 3
3 1 1 1 1
4 1 1 1 1
3
5
4
4
5
6
7

*/


int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int days[NUM_OF_BRANDS] = {0};
    int choice;
    int dayCounter = 0;
    initCube(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES);
    printMenu();
    scanf("%d", &choice);
    while(choice != done){
        switch(choice){
            case addOne:
                enterDailyBrandData(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES, dayCounter, getBrand());
                break;
            case addAll:
                if (dayCounter < DAYS_IN_YEAR){
                    enterDailyData(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES, dayCounter);
                    dayCounter++;
                }
                break;
            case stats:
                printStatsForDay(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES, dayCounter);
                break;
            case print:
                printAllData(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES, dayCounter);
                break;
// #define insights  5
// #define deltas  6
            /*
             ......
             */
            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}


