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


void initializeCube(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int daysInYear, int numOfBrands, int numOfTypes) {
#define initVal -1
    for (int i = 0; i < daysInYear; i++) {
        for (int j = 0; j < numOfBrands; j++) {
            for (int k = 0; k < numOfTypes; k++)
                cube[i][j][k] = initVal;
        }
    }
}


int getNextDayFromCounter(int nextBrandDays[], int nextBrandDaysSize) {
    int nextDay = nextBrandDays[0];
    for (int i = 1; i < nextBrandDaysSize; i++)
        if (nextBrandDays[i] < nextDay)
            nextDay = nextBrandDays[i];
    nextDay++;
    return nextDay;
}


int isMissingBrandDataInDay(int nextBrandDays[], int nextBrandDaysSize, int dayToSet) {
    int isMissing = 0;
    for (int i = 0; i < nextBrandDaysSize; i++)
        if (nextBrandDays[i] < dayToSet)
            isMissing = 1;
    return isMissing;
}


int getValidBrand() {
    int brandSelected;
    scanf("%d", &brandSelected);
    while (brandSelected < 0 || brandSelected >= NUM_OF_BRANDS) {
        printf("This brand is not valid\n");
        scanf("%d", &brandSelected);
    }
    return brandSelected;
}


void setDailyBrandSales(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int daysInYear, int numOfBrands, int numOfTypes,
                        int nextBrandDays[], int nextBrandDaysSize, int whichBrand) {
    printf("cube: %d", cube);
    for (int i = 0; i < numOfTypes; i++) {
        scanf("%d", &cube[nextBrandDays[whichBrand]][whichBrand][i]);
    }
    nextBrandDays[whichBrand]++;
}


void printMissingBrands(int nextBrandDays[], int nextBrandDaysSize, int currentDay) {
    printf("No data for brands ");
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        if (nextBrandDays[i] < currentDay)
            printf("%s ", brands[i]);
    }
    printf("\nPlease complete the data\n");
}


int getValidBrandForDailyData(int nextBrandDays[], int nextBrandDaysSize, int currentDay) {
    int brandSelected;
    scanf("%d", &brandSelected);
    while (brandSelected < 0 || brandSelected > nextBrandDaysSize - 1 || (nextBrandDays[brandSelected] == currentDay)) {
        printf("This brand is not valid\n");
        printMissingBrands(nextBrandDays, nextBrandDaysSize, currentDay);
        scanf("%d", &brandSelected);
    }
    return brandSelected;
}


void setDailyData(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int daysInYear, int numOfBrands, int numOfTypes,
                  int nextBrandDays[], int nextBrandDaysSize) {
    int dayToSet = getNextDayFromCounter(nextBrandDays, nextBrandDaysSize);
    while (isMissingBrandDataInDay(nextBrandDays, nextBrandDaysSize, dayToSet)) {
        printMissingBrands(nextBrandDays, nextBrandDaysSize, dayToSet);
        setDailyBrandSales(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES,
                           nextBrandDays, nextBrandDaysSize,
                           getValidBrandForDailyData(nextBrandDays, NUM_OF_BRANDS, dayToSet));
    }
}


int getValidDay(int maxDay) {
    int daySelected;
    printf("What day would you like to analyze?\n");
    scanf("%d", &daySelected);
    while (daySelected <= 0 || daySelected > maxDay) {
        printf("Please enter a valid day.\n");
        printf("What day would you like to analyze?\n");
        scanf("%d", &daySelected);
    }
    return daySelected;
}


int printTotalSales(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int daysInYear, int numOfBrands, int numOfTypes, int day) {
    int totalSales = 0;
    for (int i = 0; i < numOfBrands; i++)
        for (int j = 0; j < numOfTypes; j++)
            totalSales += cube[day][i][j];
    printf("The sales total was %d\n", totalSales);
}


int printBestSoldBrandForDay(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int daysInYear, int numOfBrands, int numOfTypes,
    int day) {
    int brandSales[NUM_OF_BRANDS] = {0}, maxSales = 0;
    for (int brand = 0; brand < numOfBrands; brand++) {
        for (int type = 0; type < numOfTypes; type++)
            brandSales[brand] += cube[day][brand][type];
        if (maxSales < brandSales[brand])
            maxSales = brandSales[brand];
    }
    for (int brand = 0; brand < numOfBrands; brand++)
        if (brandSales[brand] == maxSales)
            printf("The best sold brand with %d sales was %s\n", brandSales[brand], brands[brand]);
}


void printBestSoldTypeForDay(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int daysInYear, int numOfBrands, int numOfTypes,
    int day) {
    int typeSales[NUM_OF_TYPES] = {0}, maxSales = 0;
    for (int type = 0; type < numOfTypes; type++) {
        for (int brand = 0; brand < numOfBrands; brand++)
            typeSales[type] += cube[day][brand][type];
        if (maxSales < typeSales[type])
            maxSales = typeSales[type];
    }
    for (int type = 0; type < numOfTypes; type++)
        if (typeSales[type] == maxSales)
            printf("The best sold type with %d sales was %s\n", typeSales[type], types[type]);
}


void printStatsForDay(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int daysInYear, int numOfBrands, int numOfTypes,
    int maxDay) {
    int daySelected;
    daySelected = getValidDay(maxDay);
    printf("In day number %d:\n", daySelected);
    daySelected--; // Translate to array index
    printTotalSales(cube, daysInYear, numOfBrands, numOfTypes, daySelected);
    printBestSoldBrandForDay(cube, daysInYear, numOfBrands, numOfTypes, daySelected);
    printBestSoldTypeForDay(cube, daysInYear, numOfBrands, numOfTypes, daySelected);
    printf("\n");
}


void printAllData(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int daysInYear, int numOfBrands, int numOfTypes,
    int daysCounter[], int daysCounterSize) {
    printf("*****************************************\n\n");
    for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
        printf("Sales for %s:\n", brands[brand]);
        for (int day = 0; day < daysCounter[brand]; day++) {
            printf("Day %d- ", day + 1);
            for (int type = 0; type < NUM_OF_TYPES; type++)
                printf("%s: %d ", types[type], cube[day][brand][type]);
            printf("\n");
        }
    }
    printf("\n\n*****************************************\n");
}


int getMaxDayFromCounter(int nextBrandDays[], int nextBrandDaysSize) {
    int maxDay = 0;
    for (int i = 0; i < nextBrandDaysSize; i++)
        if (nextBrandDays[i] > maxDay)
            maxDay = nextBrandDays[i];
    return maxDay;
}


void getMaxValueAndIndexFromArray(int array[], int arraySize, int returnArray[2]) {
    returnArray[0] = 0;
    returnArray[1] = 0;
    for (int idx = 0; idx < arraySize; idx++) {
        if (returnArray[0] <= array[idx]) {
            returnArray[0] = array[idx];
            returnArray[1] = idx;
        }
    }
}


void printInsights(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int daysInYear, int numOfBrands, int numOfTypes,
    int maxDay) {
    int brandSales[NUM_OF_BRANDS] = {0}, typeSales[NUM_OF_TYPES] = {0}, daySales[DAYS_IN_YEAR] = {0}, maxArray[2] = {0};
    for (int day = 0; day < maxDay; day++) {
        for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
            for (int type = 0; type < NUM_OF_TYPES; type++) {
                brandSales[brand] += cube[day][brand][type];
                typeSales[type] += cube[day][brand][type];
                daySales[day] += cube[day][brand][type];
            }
        }
    }
    getMaxValueAndIndexFromArray(brandSales, NUM_OF_BRANDS, maxArray);
    printf("The best-selling brand overall is %s: %d$\n", brands[maxArray[1]], maxArray[0]);

    getMaxValueAndIndexFromArray(typeSales, NUM_OF_TYPES, maxArray);
    printf("The best-selling type of car is %s: %d$\n", types[maxArray[1]], maxArray[0]);

    getMaxValueAndIndexFromArray(daySales, maxDay, maxArray);
    printf("The most profitable day was day number %d: %d$\n", maxArray[1] + 1, maxArray[0]);
}


int getDailySumForBrand(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int daysInYear, int numOfBrands, int numOfTypes,
    int day, int brand) {
    int sum = 0;
    for (int type = 0; type < NUM_OF_TYPES; type++)
        sum += cube[day][brand][type];
    return sum;
}

float getAvgDeltaForBrand(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int daysInYear, int numOfBrands, int numOfTypes,
                          int maxDay, int brand) {
    int prevDaySum = getDailySumForBrand(cube, daysInYear, numOfBrands, numOfTypes, 0, brand), currDaySum;
    float deltaSum = 0.0;
    for (int day = 1; day < maxDay; day++) {
        currDaySum = getDailySumForBrand(cube, daysInYear, numOfBrands, numOfTypes, day, brand);
        deltaSum += currDaySum - prevDaySum;
        prevDaySum = currDaySum;
    }
    return deltaSum / (maxDay - 1);
}


void printAvgDelta(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int daysInYear, int numOfBrands, int numOfTypes,
    int maxDay) {
    for (int brand = 0; brand < NUM_OF_BRANDS; brand++)
        printf("Brand: %s, Average Delta: %f\n", brands[brand],
               getAvgDeltaForBrand(cube, daysInYear, numOfBrands, numOfTypes, maxDay, brand));
}


int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int days[NUM_OF_BRANDS] = {0};
    int choice;
    initializeCube(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES);
    printMenu();
    scanf("%d", &choice);
    while (choice != done) {
        switch (choice) {
            case addOne:
                setDailyBrandSales(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES, days, NUM_OF_BRANDS,
                                   getValidBrand());
                break;
            case addAll:
                setDailyData(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES, days, NUM_OF_BRANDS);
                break;
            case stats:
                printStatsForDay(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES,
                                 getMaxDayFromCounter(days, NUM_OF_BRANDS));
                break;
            case print:
                printAllData(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES,
                             days, NUM_OF_BRANDS);
                break;
            case insights:
                printInsights(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES,
                              getMaxDayFromCounter(days, NUM_OF_BRANDS));
                break;
            case deltas:
                printAvgDelta(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES,
                              getMaxDayFromCounter(days, NUM_OF_BRANDS));
                break;
            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}
