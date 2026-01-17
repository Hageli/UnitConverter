#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define BUFFSIZE 1024

// Return conditions: true IF input is an integer, ELSE false
// Notes: Negative integer values accepted, must check validity of input elsewhere
bool parse_input(char *input, int *choice, float *to_calculation) {
    int i = 0;
    int length = strlen(input);

    // Check that input is not empty
    if(length == 0) return false;

    // Loop through whitespace
    while(isspace(input[i])) i++;

    // Variables for final integer output
    char int_buf[BUFFSIZE];
    int int_chars = 0;

    // Add minus if required
    if(input[i] == '-') {
        int_buf[int_chars] = '-';
        int_chars++;
        i++;
    }

    // Validate input format
    while( i < length && !isspace(input[i])) {
        if(!isdigit(input[i]) && input[i] != '.') return false;

        int_buf[int_chars] = input[i];
        int_chars++;
        i++;
    }

    // Add terminator, change to int and float
    int_buf[int_chars] = '\0';
    *to_calculation = atof(int_buf);
    *choice = atoi(int_buf);
    return true;
}

// Checks the conversion type and calculates final result
void handleTempCalculation(int *from_int, int *to_int) {
    float finalValue;
    char amount[BUFFSIZE];
    int temp_int;
    float temp_float;

    // Check if same unit is given twice
    if(*from_int == *to_int) {
        printf("\nCannot convert to same unit!\r\n\n");
        return;
    }

    printf("Enter the starting temperature: ");
    fgets(amount, sizeof(amount), stdin);

    // Check if the amount is valid
    if(!parse_input(amount, &temp_int, &temp_float)) {
        printf("\nPlease give valid amount\r\n\n");
        return;
    // C to F
    } else if (*from_int == 1 && *to_int == 2) {
        finalValue = temp_float * 1.8 + 32;
    // C to K
    } else if (*from_int == 1 && *to_int == 3) {
        finalValue = temp_float + 273.15;
    // F to C
    } else if (*from_int == 2 && *to_int == 1) {
        finalValue = (temp_float - 32) / 1.8;
    // F to K
    } else if (*from_int == 2 && *to_int == 3) {
        finalValue = (temp_float + 459.67) / 1.8;
    // K to C
    } else if (*from_int == 3 && *to_int == 1) {
        finalValue = temp_float - 273.15;
    // K to F
    } else if (*from_int == 3 && *to_int == 2) {
        finalValue = (temp_float - 273.15) * 1.8 + 32;
    }

    printf("\n%.2f\r\n\n", finalValue);
    return;
}

void handleWeightCalculation (int *from_int, int *to_int) {
    char amount[BUFFSIZE];
    int amount_int;
    float amount_float;
    float finalValue;

    if(*from_int == *to_int) {
        printf("\nCannot convert to same unit!\r\n\n");
        return;
    }

    printf("Enter the starting weight: ");
    fgets(amount, sizeof(amount), stdin);

    if(!parse_input(amount, &amount_int, &amount_float)) {
        printf("\nPlease give valid amount\r\n\n");
        return;
    } else if (amount_int < 0) {
        printf("\nNo negative mass values allowed!\r\n\n");
        return;
    // G to KG
    } else if (*from_int == 1 && *to_int == 2) {
        finalValue = amount_float / 1000;
    // G to OZ
    } else if (*from_int == 1 && *to_int == 3) {
        finalValue = amount_float / 28.3495;
    // G to LB
    } else if (*from_int == 1 && *to_int == 4) {
        finalValue = amount_float / 453.592;
    // G to ST
    } else if (*from_int == 1 && *to_int== 5) {
        finalValue = amount_float / 6350.29;
    // KG to G
    } else if (*from_int == 2 && *to_int == 1) {
        finalValue = amount_float * 1000;
    // KG to OZ
    } else if (*from_int == 2 && *to_int == 3) {
        finalValue = amount_float * 35.274;
    // KG to LB
    } else if (*from_int == 2 && *to_int == 4) {
        finalValue = amount_float * 2.20462;
    // KG to ST
    } else if (*from_int == 2 && *to_int == 5) {
        finalValue = amount_float * 0.157473;
    // OZ to G
    } else if (*from_int == 3 && *to_int == 1) {
        finalValue = amount_float * 28.3495;
    // OZ to KG
    } else if (*from_int == 3 && *to_int == 2) {
        finalValue = amount_float / 35.274;
    // OZ to LB
    } else if (*from_int == 3 && *to_int == 4) {
        finalValue = amount_float / 16;
    // OZ to ST
    } else if (*from_int == 3 && *to_int == 5) {
        finalValue = amount_float / 224;
    // LB to G
    } else if (*from_int == 4 && *to_int == 1) {
        finalValue = amount_float * 453.592;
    // LB to KG
    } else if (*from_int == 4 && *to_int == 2) {
        finalValue = amount_float / 2.20462;
    // LB to OZ
    } else if (*from_int == 4 && *to_int == 3) {
        finalValue = amount_float * 16;
    // LB to ST
    } else if (*from_int == 4 && *to_int == 5) {
        finalValue = amount_float / 14;
    // ST to G
    } else if (*from_int == 5 && *to_int == 1) {
        finalValue = amount_float * 6350.29;
    // ST to KG
    } else if (*from_int == 5 && *to_int == 2) {
        finalValue = amount_float / 0.157473;
    // ST to OZ
    } else if (*from_int == 5 && *to_int == 3) {
        finalValue = amount_float * 224;
    // ST to LB
    } else if (*from_int == 5 && *to_int == 4) {
        finalValue = amount_float * 14;
    }
    printf("%.2f\r\n\n", finalValue);
    return;
}

// Menu for temperature units
// Calls: handleTempCalculation()
void temperatureConversion() {
    char from_unit[BUFFSIZE];
    int from_int;
    float from_float;
    
    char to_unit[BUFFSIZE];
    int to_int;

    printf("Please give input unit\r\n");
    printf("1. Celsius\r\n");
    printf("2. Fahrenheit\r\n");
    printf("3. Kelvin\r\n\n");
    printf("Your input: ");
    fgets(from_unit, sizeof(from_unit), stdin);
    
    if(parse_input(from_unit, &from_int, &from_float)) {
        printf("\nPlease give output unit\r\n");
        printf("1. Celsius\r\n");
        printf("2. Fahrenheit\r\n");
        printf("3. Kelvin\r\n\n");
        printf("Your input: ");
        fgets(to_unit, sizeof(to_unit), stdin);

        if(parse_input(to_unit, &to_int, &from_float)) {
            handleTempCalculation(&from_int, &to_int);
        } else {
            printf("\nPlease give valid unit\r\n\n");
        }
    } else {
        printf("\nPlease give valid unit\r\n\n");
    }
    return;
}

// TODO: british stone, kilogram, gram, ounce, pound
void weightConversion () {
    char from_unit[BUFFSIZE];
    char to_unit[BUFFSIZE];
    int from_int;
    int to_int;
    float from_float;

    printf("\nPlease give input unit:\r\n");
    printf("1. Gram\r\n");
    printf("2. Kilogram\r\n");
    printf("3. Ounce\r\n");
    printf("4. Pound\r\n");
    printf("5. Stone\r\n\n");
    printf("Your input: ");
    fgets(from_unit, sizeof(from_unit), stdin);

    if(parse_input(from_unit, &from_int, &from_float)) {
        printf("\nPlease give output unit:\r\n");
        printf("1. Gram\r\n");
        printf("2. Kilogram\r\n");
        printf("3. Ounce\r\n");
        printf("4. Pound\r\n");
        printf("5. Stone\r\n\n");
        printf("Your input: ");
        fgets(to_unit, sizeof(to_unit), stdin);

        if(parse_input(to_unit, &to_int, &from_float)) {
            handleWeightCalculation(&from_int, &to_int);
        } else {
            printf("\nPlease give unit\r\n\n");
            return;    
        }
    } else {
        printf("\nPlease give valid unit\r\n\n");
        return;
    }
    return;
}


// TODO: dollar, euro, swedish krona, ruble
void moneyConversion () {

}

// TODO: metres, feet, inches, centrimetres
void distanceConversion () {

}

// TODO: cup, gallon, litre, ml, barrel
void volumeConversion () {

}

int main() {
    char input[BUFFSIZE];
    int choice = 999;
    float to_calculation;

    

    printf("This is the unit converter program! \r\n");
    printf("What type of unit would you like to convert?\r\n\n");
    while(choice != 0) {
        // Type choices
        printf("1. Temperature\r\n");
        printf("2. Weight\r\n");
        printf("3. Distance\r\n");        
        printf("4. Money\r\n");
        printf("0. Exit program\r\n\n");
        printf("Your input: ");

        fgets(input, sizeof(input), stdin);
        if(parse_input(input, &choice, &to_calculation)) {
            printf("\n");
            // Type conversion cases
            switch(choice) {
                case 1:
                    temperatureConversion();
                    break;
                case 2:
                    weightConversion();
                    break;
                case 3:
                    distanceConversion();
                    break;
                case 4:
                    moneyConversion();
                    break;
                case 0:
                    printf("Exiting system...\r\n\n");
                    exit(0);
                    break;
                default:
                    printf("Invalid choice, try again.\r\n\n");
                    break;
            }    
        } else {
            printf("\nInvalid choice, try again.\r\n\n");
        }
    }
    return 0;
}