#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
// #include <curl/curl.h>
// #include <json-c/json.h>

#define BUFFSIZE 1024

// Struct for storing conversion rate response data
struct Memory {
    char *response;
    size_t size;
};

typedef struct {
    char *valueArray[3];
} Temperatures;

typedef struct {
    char *valueArray[5];
} Weights;

typedef struct {
    char *valueArray[4];
} Distances;

typedef struct {
    char *valueArray[5];
} Volumes;

typedef struct {
    char *valueArray[5];
} Currency;

// Initializing the units
static Temperatures tempUnits = {"Celsius", "Fahrenheit", "Kelvin"};
static Weights weightUnits = {"Gram", "Kilogram", "Ounce (US)", "Pound (US)", "Stone (GBR)"};
static Distances distUnits = {"Inch", "Centimetre", "Metre", "Foot"};
static Volumes volUnits = {"Millilitre", "Litre", "Cup (US)", "Gallon (US)", "Barrel (Oil)"};
static Currency curUnits = {"USD", "JPY", "SEK", "GBP", "CNY"};

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

// Checks the conversion type and calculates final temperature result
void handleTempCalculation(int *from_int, int *to_int) {
    char amount[BUFFSIZE];
    int amount_int;
    float amount_float;
    float finalValue;

    // Check if same unit is given twice
    if(*from_int == *to_int) {
        printf("\nCannot convert to same unit!\r\n\n");
        return;
    } else if(*from_int < 1 || *from_int > 3 || *to_int < 1 || *to_int > 3) {
        printf("\nInvalid unit choice!\r\n\n");
        return;
    }

    printf("Enter the starting temperature: ");
    fgets(amount, sizeof(amount), stdin);

    // Check if the amount is valid
    if(!parse_input(amount, &amount_int, &amount_float)) {
        printf("\nPlease give valid amount\r\n\n");
        return;
    // C to F
    } else if (*from_int == 1 && *to_int == 2) {
        finalValue = amount_float * 1.8 + 32;
    // C to K
    } else if (*from_int == 1 && *to_int == 3) {
        finalValue = amount_float + 273.15;
    // F to C
    } else if (*from_int == 2 && *to_int == 1) {
        finalValue = (amount_float - 32) / 1.8;
    // F to K
    } else if (*from_int == 2 && *to_int == 3) {
        finalValue = (amount_float + 459.67) / 1.8;
    // K to C
    } else if (*from_int == 3 && *to_int == 1) {
        finalValue = amount_float - 273.15;
    // K to F
    } else if (*from_int == 3 && *to_int == 2) {
        finalValue = amount_float - 273.15 * 1.8 + 32;
    }

    printf("\nConverting %.2f %s to %s... \nResult: %.2f %s\r\n\n", amount_float, tempUnits.valueArray[*from_int - 1], tempUnits.valueArray[*to_int - 1], finalValue, tempUnits.valueArray[*to_int - 1]);
    return;
}

// Checks the conversion type and calculates final weight result
void handleWeightCalculation (int *from_int, int *to_int) {
    char amount[BUFFSIZE];
    int amount_int;
    float amount_float;
    float finalValue;

    if(*from_int == *to_int) {
        printf("\nCannot convert to same unit!\r\n\n");
        return;
    } else if(*from_int < 1 || *from_int > 5 || *to_int < 1 || *to_int > 5) {
        printf("\nInvalid unit choice!\r\n\n");
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

    printf("\nConverting %.2f %s to %s... \nResult: %.2f %s\r\n\n", amount_float, weightUnits.valueArray[*from_int - 1], weightUnits.valueArray[*to_int - 1], finalValue, weightUnits.valueArray[*to_int - 1]);
    return;
}

// Checks the conversion type and calculates final distance result
void handleDistanceCalculation (int *from_int, int *to_int) {
    char amount[BUFFSIZE];
    int amount_int;
    float amount_float;
    float finalValue;

    if(*from_int == *to_int) {
        printf("\nCannot convert to same unit!\r\n\n");
        return;
    } else if(*from_int < 1 || *from_int > 4 || *to_int < 1 || *to_int > 4) {
        printf("\nInvalid unit choice!\r\n\n");
        return;
    }

    printf("Enter the starting distance: ");
    fgets(amount, sizeof(amount), stdin);

    if(!parse_input(amount, &amount_int, &amount_float)) {
        printf("\nPlease give valid amount\r\n\n");
        return;
    } else if (amount_int < 0) {
        printf("\nNo negative distance values allowed!\r\n\n");
        return;
    // INCH to CM 
    } else if (*from_int == 1 && *to_int == 2) {
        finalValue = amount_float * 2.54;
    // INCH to M
    } else if (*from_int == 1 && *to_int == 3){
        finalValue = amount_float * 0.0254;
    // INCH to FOOT
    } else if (*from_int == 1 && *to_int == 4){
        finalValue = amount_float / 12;
    // CM to INCH
    } else if (*from_int == 2 && *to_int == 1) {
        finalValue = amount_float / 2.54;
    // CM to M
    } else if (*from_int == 2 && *to_int == 3) {
        finalValue = amount_float / 100;
    // CM to FOOT
    } else if (*from_int == 2 && *to_int == 4) {
        finalValue = amount_float / 30.48;
    // M to INCH
    } else if (*from_int == 3 && *to_int == 1) {
        finalValue = amount_float / 0.0254;
    // M to CM
    } else if (*from_int == 3 && *to_int == 2) {
        finalValue = amount_float * 100;
    // M to FOOT
    } else if (*from_int == 3 && *to_int == 4) {
        finalValue = amount_float * 3.28084;
    // FOOT to INCH
    } else if (*from_int == 4 && *to_int == 1) {
        finalValue = amount_float * 12;
    // FOOT TO CM
    } else if (*from_int == 4 && *to_int == 2) {
        finalValue = amount_float * 30.48;
    // FOOT TO M
    } else if (*from_int == 4 && *to_int == 3) {
        finalValue = amount_float / 3.28084;
    }

    printf("\nConverting %.2f %s to %s... \nResult: %.2f %s\r\n\n", amount_float, distUnits.valueArray[*from_int - 1], distUnits.valueArray[*to_int - 1], finalValue, distUnits.valueArray[*to_int - 1]);
    return;
}

// Checks the conversion type and calculates final weight result
void handleVolumeCalculation (int *from_int, int *to_int) {
    char amount[BUFFSIZE];
    int amount_int;
    float amount_float;
    float finalValue;

    if(*from_int == *to_int) {
        printf("\nCannot convert to same unit!\r\n\n");
        return;
    } else if(*from_int < 1 || *from_int > 5 || *to_int < 1 || *to_int > 5) {
        printf("\nInvalid unit choice!\r\n\n");
        return;
    }

    printf("Enter the starting volume: ");
    fgets(amount, sizeof(amount), stdin);

    if(!parse_input(amount, &amount_int, &amount_float)) {
        printf("\nPlease give valid amount\r\n\n");
        return;
    } else if (amount_int < 0) {
        printf("\nNo negative volume values allowed!\r\n\n");
        return;
    // ML to L
    } else if (*from_int == 1 && *to_int == 2) {
        finalValue = amount_float / 1000;
    // ML to CUP(US)
    } else if (*from_int == 1 && *to_int == 3) {
        finalValue = amount_float / 236.6;
    // ML to GL(US)
    } else if (*from_int == 1 && *to_int == 4) {
        finalValue = amount_float / 3785.41;
    // ML to BR(US)
    } else if (*from_int == 1 && *to_int== 5) {
        finalValue = amount_float / 158987.294;
    // L to ML
    } else if (*from_int == 2 && *to_int == 1) {
        finalValue = amount_float * 1000;
    // L to CUP(US)
    } else if (*from_int == 2 && *to_int == 3) {
        finalValue = amount_float * 4.22675;
    // L to GL(US)
    } else if (*from_int == 2 && *to_int == 4) {
        finalValue = amount_float / 3.785;
    // L to BR(US)
    } else if (*from_int == 2 && *to_int == 5) {
        finalValue = amount_float / 158.987;
    // CUP(US) to ML
    } else if (*from_int == 3 && *to_int == 1) {
        finalValue = amount_float * 236.6;
    // CUP(US) to L
    } else if (*from_int == 3 && *to_int == 2) {
        finalValue = amount_float * 0.236588;
    // CUP(US) to GL(US)
    } else if (*from_int == 3 && *to_int == 4) {
        finalValue = amount_float / 16;
    // CUP(US) to BR(US)
    } else if (*from_int == 3 && *to_int == 5) {
        finalValue = amount_float / 672;
    // GL(US) to ML
    } else if (*from_int == 4 && *to_int == 1) {
        finalValue = amount_float * 3785.41;
    // GL(US) to L
    } else if (*from_int == 4 && *to_int == 2) {
        finalValue = amount_float * 3.785;
    // GL(US) to CUP(US)
    } else if (*from_int == 4 && *to_int == 3) {
        finalValue = amount_float * 16;
    // GL(US) to BR(US)
    } else if (*from_int == 4 && *to_int == 5) {
        finalValue = amount_float / 42;
    // BR(US) to ML
    } else if (*from_int == 5 && *to_int == 1) {
        finalValue = amount_float * 158987.294;
    // BR(US) to L
    } else if (*from_int == 5 && *to_int == 2) {
        finalValue = amount_float * 158.987;
    // BR(US) to CUP(US)
    } else if (*from_int == 5 && *to_int == 3) {
        finalValue = amount_float * 672;
    // BR(US) to GL(US)
    } else if (*from_int == 5 && *to_int == 4) {
        finalValue = amount_float * 42;
    }

    printf("\nConverting %.2f %s to %s... \nResult: %.2f %s\r\n\n", amount_float, volUnits.valueArray[*from_int - 1], volUnits.valueArray[*to_int - 1], finalValue, volUnits.valueArray[*to_int - 1]);
    return;
}

// Checks the conversion type and calculates final currency result
void handleMoneyCalculation(int *from_int, int *to_int) {
    char amount[BUFFSIZE];
    int amount_int;
    float amount_float;
    float finalValue;

    if(*from_int == *to_int) {
        printf("\nCannot convert to same unit!\r\n\n");
        return;
    } else if(*from_int < 1 || *from_int > 5 || *to_int < 1 || *to_int > 5) {
        printf("\nInvalid currency choice!\r\n\n");
        return;
    }

    printf("Enter the starting amount: ");
    fgets(amount, sizeof(amount), stdin);

    if(!parse_input(amount, &amount_int, &amount_float)) {
        printf("\nPlease give valid amount\r\n\n");
        return;
    } else if (amount_int < 0) {
        printf("\nNo negative amount allowed!\r\n\n");
        return;
    }

    printf("\nConverting %.2f EUR to %s... \nResult: %.2f %s\r\n\n", amount_float, curUnits.valueArray[*from_int -1], finalValue, curUnits.valueArray[*to_int -1]);
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

// Menu for weight units
// Calls: handleWeightCalculation()
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
            printf("\nPlease give valid unit\r\n\n");
            return;    
        }
    } else {
        printf("\nPlease give valid unit\r\n\n");
        return;
    }
    return;
}

// Menu for currencies
// TODO: dollar, euro, swedish krona, ruble
void moneyConversion () {
    char from_unit[BUFFSIZE];
    int from_int;
    float from_float;
    
    char to_unit[BUFFSIZE];
    int to_int;

    printf("Here you can convert EURO to other currencies with real-time exchange rates.\r\n");
    printf("Please give output currency\r\n");
    printf("1. Dollar\r\n");
    printf("2. Japanese Yen\r\n");
    printf("3. Swedish Krona\r\n");
    printf("4. British Pound\r\n");
    printf("5. Chinese Yuan\r\n\n");
    printf("Your input: ");
    fgets(from_unit, sizeof(from_unit), stdin);
    
    if(parse_input(from_unit, &from_int, &from_float)) {
        handleMoneyCalculation(&from_int, &to_int);
    } else {
        printf("\nPlease give valid currency\r\n\n");
    }
    return;
}

// Menu for distance units
// Calls: handleDistanceCalculation()
void distanceConversion () {
    char from_unit[BUFFSIZE];
    int from_int;
    float from_float;
    
    char to_unit[BUFFSIZE];
    int to_int;

    printf("Please give input unit\r\n");
    printf("1. Inch\r\n");
    printf("2. Centimetre\r\n");
    printf("3. Metre\r\n");
    printf("4. Foot\r\n\n");
    printf("Your input: ");
    fgets(from_unit, sizeof(from_unit), stdin);
    
    if(parse_input(from_unit, &from_int, &from_float)) {
        printf("\nPlease give output unit\r\n");
        printf("1. Inch\r\n");
        printf("2. Centimetre\r\n");
        printf("3. Metre\r\n");
        printf("4. Foot\r\n\n");
        printf("Your input: ");
        fgets(to_unit, sizeof(to_unit), stdin);

        if(parse_input(to_unit, &to_int, &from_float)) {
            handleDistanceCalculation(&from_int, &to_int);
        } else {
            printf("\nPlease give valid unit\r\n\n");
        }
    } else {
        printf("\nPlease give valid unit\r\n\n");
    }
    return;
}

// Menu for volume units
// Calls: handleVolumeCalculation()
void volumeConversion () {
    char from_unit[BUFFSIZE];
    char to_unit[BUFFSIZE];
    int from_int;
    int to_int;
    float from_float;

    printf("\nPlease give input unit:\r\n");
    printf("1. Millilitre\r\n");
    printf("2. Litre\r\n");
    printf("3. Cup (US)\r\n");
    printf("4. Gallon (US)\r\n");
    printf("5. Barrel (Oil)\r\n\n");
    printf("Your input: ");
    fgets(from_unit, sizeof(from_unit), stdin);

    if(parse_input(from_unit, &from_int, &from_float)) {
        printf("\nPlease give output unit:\r\n");
        printf("1. Millilitre\r\n");
        printf("2. Litre\r\n");
        printf("3. Cup (US)\r\n");
        printf("4. Gallon (US)\r\n");
        printf("5. Barrel (Oil)\r\n\n");
        printf("Your input: ");
        fgets(to_unit, sizeof(to_unit), stdin);

        if(parse_input(to_unit, &to_int, &from_float)) {
            handleVolumeCalculation(&from_int, &to_int);
        } else {
            printf("\nPlease valid give unit\r\n\n");
            return;    
        }
    } else {
        printf("\nPlease give valid unit\r\n\n");
        return;
    }
    return;
}

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct Memory *mem = (struct Memory *)userp;

    char *ptr = realloc(mem->response, mem->size + realsize + 1);
    if(ptr == NULL) {
        // out of memory
        printf("Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;

    return realsize;
}

int main() {
    char input[BUFFSIZE];
    int choice = 999;
    float to_calculation;

    // Values for exchange rates
    CURL *curl;
    CURLcode res;
    struct Memory chunk;

    chunk.response = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if(curl) {
        char url[256];
        snprintf(url, sizeof(url), "https://api.boffsaopendata.fi/referencerates/v2/api/V2?currencies=USD,JPY,SEK,GBP,CNY");
        curl_easy_setopt(curl, CURLOPT_URL, url );
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);

        struct json_object *json = json_tokener_parse(chunk.response);
    }
    

    printf("This is the unit converter program! \r\n");
    printf("What type of unit would you like to convert?\r\n\n");
    while(choice != 0) {
        // Type choices
        printf("1. Temperature\r\n");
        printf("2. Weight\r\n");
        printf("3. Distance\r\n");        
        printf("4. Money\r\n");
        printf("5. Volume\r\n");
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
                case 5:
                    volumeConversion();
                    break;
                case 0:
                    printf("Exiting system...\r\n\n");
                    free(chunk.response);
                    curl_global_cleanup();
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