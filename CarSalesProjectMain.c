#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

    // Car prices
    float carPrices[] = {15000, 30000, 35000, 40000, 8000}; // Array 1 for car prices

    // Car quantity
    short carStock[] = {2, 4, 6, 7, 3}; // Array 2 for car quantity
    #define totalCarQuantity 22 // Total quantity of cars.
    float totalPrice;
    float discountCal;

    // User input
    char carBrand[201]; // car brand input
    char discount;// discount answer
    char menuChoice; // user menu select
    char customerName[totalCarQuantity][201]; // stores customer names
    short userAge[totalCarQuantity];

    // Sales Data
    float totalSales = 0.0f;
    int totalCarSold = 0;
    int carSold[5] = {0}; // Array 3 - tracks cars sold

    char *carNames[] = {"Volkswagen", "Bmw", "Mercedes", "Audi", "Toyota"}; // Array 4 for brand names
    int carYear[] = {2022,2023,2021,2020,2014}; // Array to store year of car manufacture

    // Customer sales
    float customerSales[totalCarQuantity]; // Stores purchase of each customer
    float discountAmount[totalCarQuantity]; // Stores discount of each customer
    char customerFeedback[totalCarQuantity][501]; // stores feedback of each customer



    void menu_Options(){
        printf("Welcome to ARU car dealership!\n\n");
        printf("Menu:\n");
        printf("a. Buy Cars\n");
        printf("b. View Sales Stats\n");
        printf("x. Exit\n\n");
        printf("Please choose one: ");
    }
    
    int isValidMenuOption(char choice) { // specified menu choices
        return (choice == 'a' || choice == 'b' || choice == 'x');
    }

    char user_Menu_Choice(char menuChoice) {
        scanf(" %c", &menuChoice);
        printf("\n\n");

            if (!isValidMenuOption(menuChoice)) {
                printf("Incorrect option. Please choose 'a', 'b', or 'x'.\n");
                menu_Options();
                //exit(EXIT_FAILURE); // Exit program if incorrect choice
            }

        return menuChoice;
    }

    void vehicle_stock(short carStock[], char *carNames[], float carPrices[], int carYear[]) {
        printf("We have the following vehicles in stock:\n\n");
            for (int i = 0; i < 5; i++) {
                if (carStock[i] <= 0) {
                    printf("%s - sorry, no more cars available from this brand.\n\n", carNames[i]);
            } else {
                printf("%s (%d) quantity in stock: %hd, each car costs %.0f£.\n\n", carNames[i], carYear[i], carStock[i], carPrices[i]);
            }
        }
    }

    void user_name(char customerName[][201]) {// takes user name/checks if name is string and not a symbol/numeric value
        printf("What is your name? Name: ");

            if (fgets(customerName[totalCarSold], sizeof(customerName[totalCarSold]), stdin) == NULL) {
                printf("Error reading user input.\n");
                exit(EXIT_FAILURE);
            }

    // Check if the input contains only alphabetic characters and spaces
            for (int i = 0; customerName[totalCarSold][i] != '\0'; i++) {
                if (!isalpha(customerName[totalCarSold][i]) && !isspace(customerName[totalCarSold][i])) {
                    printf("Invalid input. Please enter a name using only alphabetic characters and spaces.\n");
                    exit(EXIT_FAILURE);
                }
            }

    // Remove the newline character if present
            if (customerName[totalCarSold][strlen(customerName[totalCarSold]) - 1] == '\n') {
                customerName[totalCarSold][strlen(customerName[totalCarSold]) - 1] = '\0';
            }
    }

    void user_age(short userAge[], int index) { // Takes user input, checks if input is numerical/ checks if user is old enought to buy a car
        printf("Please enter how old you are: \n");

        if (scanf("%hd", &userAge[index]) != 1) {
            printf("Invalid input. Please enter a valid decimal number.\n");
            exit(EXIT_FAILURE);// Stops program
        }

    getchar(); // Consume the newline character in the input buffer

        if (userAge[index] < 18) {
            printf("Sorry, you must be over 18 years old to buy a car.\n");
            printf("Too young to buy a car. Exiting program.\n");
            exit(EXIT_FAILURE); // Stops program
        }
    }

    void car_brand_choice(char carBrand[201]){
        printf("Which car brand would you like to buy?\n");
        scanf(" %s", carBrand);
    }
    

    char user_discount_choice(char *discount){
        printf("Would you like to buy a second car from the same brand with a 30 percent discount (Y/N)?: ");
        scanf(" %c", discount);
    }

    

    void get_customer_feedback(char feedback[][501]) {
        printf("Please provide your feedback (max 500 characters):\n");
        scanf(" %[^\n]", feedback[totalCarSold]);
    }

    void carSort(int carYear[], char *carNames[], float carPrices[], short carStock[]) {
        int n = 5; // Number of elements in the arrays

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (carYear[j] < carYear[j + 1]) {
                    // Swap years
                    int tempYear = carYear[j];
                    carYear[j] = carYear[j + 1];
                    carYear[j + 1] = tempYear;

                    // Swap carNames
                    char *tempName = carNames[j];
                    carNames[j] = carNames[j + 1];
                    carNames[j + 1] = tempName;

                    // Swap carPrices
                    float tempPrice = carPrices[j];
                    carPrices[j] = carPrices[j + 1];
                    carPrices[j + 1] = tempPrice;

                    // Swap carStock
                    int tempStock = carStock[j];
                    carStock[j] = carStock[j + 1];
                    carStock[j + 1] = tempStock;
                }
            }
        }
    }

    void buy_Cars() {
        user_age(userAge,totalCarSold);// Checks if user is old enought to buy a car
        user_name(customerName); // Takes and stores user name
        car_brand_choice(carBrand); // Accepts and checks user car brand selected
        user_discount_choice(&discount); // Asks user for discount
        get_customer_feedback(customerFeedback); // Asks user for feedback

        int carIndex = -1;
        for (int i = 0; i < 5; i++) {//Case-insensitive string comparison
            if (strcasecmp(carBrand, carNames[i]) == 0) {
                carIndex = i;
                break;
            }
        }

        float discountCal = 0.0;
            if (carIndex >= 0 && carStock[carIndex] > 0) {
                if (discount == 'Y' || discount == 'y') { // IF THERE IS DISCOUNT
                    discountCal = 0.3 * carPrices[carIndex];
                    totalPrice = carPrices[carIndex] - discountCal;
                    printf("Thank you\n");
                        if (carIndex == 0) {
                            printf("You have bought 2 %s's!\n", carNames[carIndex]);
                            carStock[carIndex] -= 2;
                            carSold[carIndex] += 2;
                        } else {
                            printf("You have bought %s!\n", carNames[carIndex]);
                            carSold[carIndex] += 1;
                            carStock[carIndex] -= 1;
                        }
                        printf("Discount Given: %.1f£\n", discountCal);
                        printf("Total price is %.1f£\n", totalPrice);
                        printf("Feedback: %s\n", customerFeedback[totalCarSold]);
                        printf("Have a good day!\n");
                } else if (discount == 'N' || discount == 'n') { // IF THERE IS NO DISCOUNT
                    totalPrice = carPrices[carIndex];
                    printf("Thank you\n");
                    printf("You have bought %s!\n", carNames[carIndex]);
                    carSold[carIndex] += 1;
                    carStock[carIndex] -= 1;
                    printf("Discount Given: 0.0£\n");
                    printf("Total price is %.0f£\n", totalPrice);
                    printf("Feedback: %s\n", customerFeedback[totalCarSold]);
                    printf("Have a good day!\n");
                } else {
                    printf("Invalid discount selection.\n");
                }
            } else {
                printf("Invalid car brand or out of stock.\n");
            }
        customerSales[totalCarSold] = totalPrice;
        discountAmount[totalCarSold] = discountCal;
        totalCarSold++;
    }

    void view_sale_stats() {
        FILE *carSale = fopen("carTabs.txt", "a");// open and append the entire Sales tab into carTabs file
            if (carSale == NULL) {
                printf("Error opening file for writing.\n");
                return;
            }

        printf("Car sales stats:\n\n");

        for (int i = 0; i < totalCarSold; i++) {// PRINTS OUT CUSTOMER NAME / CUSTOMER SALE / DISCOUNT / FEEDBACK / TOTAL SALES
            printf("Customer Name: %s\n", customerName[i]); // Prints out customer name
            fprintf(carSale, "Customer Name: %s\n", customerName[i]); // saves name on file
            printf("Customer age: %hd\n", userAge[i]);
            printf("Car Sales: %.2f £\n", customerSales[i]); // prints out customer purchase
            fprintf(carSale, "Car Sales: %.2f £\n", customerSales[i]); // stores purchase on file
            printf("Discount Given: %.1f £\n", discountAmount[i]); // prints out discount amount
            fprintf(carSale, "Discount Given: %.1f £\n", discountAmount[i]); // stores discount on file
            printf("Feedback: %s\n", customerFeedback[i]); // prints out customer feedback
            fprintf(carSale, "Feedback: %s\n", customerFeedback[i]); // stores feedback on file
            printf("-----------------------\n");
            fprintf(carSale, "-----------------------\n"); //fancy separation lines
            printf("\n");
            fprintf(carSale, "\n");
        }

        totalSales = 0.0f;
            for (int i = 0; i < totalCarSold; i++) {
                totalSales += customerSales[i];
            }

        printf("Total sales: %.1f £\n\n", totalSales);
        fprintf(carSale, "Total sales: %.1f £\n\n", totalSales);

        fclose(carSale);
    }

    void menu_exit() {
        printf("\nThank you for using this Car Sales program. Bye-bye!\n");
    }

    void back_to_mainmenu() {
        if (menuChoice != 'x') {
            printf("\nPress Enter to return to the Menu...");
            while (getchar() != '\n'); // Clear the input buffer
        } else {
            printf("\nPress Enter to Exit...");
        }
    }

    void readPreviousSalesData() {
        FILE *carSale = fopen("carTabs.txt", "r");
            if (carSale == NULL) {// check if file can be open
            return;
            }
        // Read data from the file and initialize program state
        while (fscanf(carSale, "Customer Name: %[^\n]\n", customerName[totalCarSold]) == 1) {
            fscanf(carSale, "Customer age: %hd\n", &userAge[totalCarSold]);
            fscanf(carSale, "Car Sales: %f £\n", &customerSales[totalCarSold]);
            fscanf(carSale, "Discount Given: %f £\n", &discountAmount[totalCarSold]);
            fscanf(carSale, "Feedback: %[^\n]\n", customerFeedback[totalCarSold]);
        }

        fclose(carSale);
    }

    // MAIN
    int main(){

        readPreviousSalesData(); // reads previous sales from file and uses info if exsists

        do {
            menu_Options(); //Prints main menu
            menuChoice = user_Menu_Choice(menuChoice); //Accepts user input from main menu
            carSort(carYear, carNames, carPrices, carStock);// sorts car by year in desc order
            vehicle_stock(carStock, carNames, carPrices, carYear); //Shows car stock,brand,price,year
        
        switch (menuChoice) {
            case 'a':

                buy_Cars(); //Calculates sales,discount,applies if there is discount, accepts user input

                break;

            case 'b':

                view_sale_stats();// Prints out stored data

                break;

            case 'x':

                menu_exit();// Prints out exit message

                break;
        }

        back_to_mainmenu();// Sends user back to main menu

        getchar(); // Wait for Enter key

        }while (menuChoice != 'x');

            printf("\nHave a good day!\n");

    return 0;
}