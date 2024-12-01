#include <stdio.h>
#include <stdlib.h>

// void data_file (int supplier_num ){
//     sprintf(filename, "supplier%d.txt", supplier_num);
//     FILE *supplier_amount = fopen(filename, "rt");
//     if (supplier_amount == NULL) {
//         c_textcolor(4);
//         printf("Error: Unable to create file %s!\n", filename);
//         return;
//     }
//     FILE *data_file = fopen("data_file.txt","rt");
//     if(data_file == NULL){
//         printf("the file does not exist !!!");
//         exit(0);
//     }
//     int taill = 0 ;
//     int quantity;
//     while(fscanf(data_file ,"%d",))
//     int *Quantity ;
//     while()
// }


#include <stdio.h>
#include <stdlib.h>

void ReadQuantitiesFromFile(int supplier_num) {
    // Array of weekdays
    const char *weekdays[] = {
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
        "Sunday"
    };
    char filename[30];
    sprintf(filename, "supplier%d.txt", supplier_num);
    FILE *supplier_amount = fopen(filename, "rt");
    if (supplier_amount == NULL) {
        printf("Error: Unable to open file %s!\n", filename);
        return;
    }

    FILE *data_file = fopen("data_file.txt", "wt");
    if (data_file == NULL) {
        printf("Error: Unable to create or open data_file.txt!\n");
        fclose(supplier_amount);
        exit(0);
    }

    // Process the supplier file
    int i = 0; // To keep track of the current weekday
    char line[256];
    int quantity;
    while (fgets(line, sizeof(line), supplier_amount) != NULL) {
        // Look for the line containing "Quantity"
        if (sscanf(line, "Quantity: %d", &quantity) == 1) {
            // Write the weekday and quantity to the data_file
            if (i < 7) { // Ensure no out-of-bounds access for weekdays
                fprintf(data_file, "%s %d\n", weekdays[i], quantity);
                i++;
            } else {
                i = 0; // Reset to Monday if more than 7 quantities are found
                fprintf(data_file, "%s %d\n", weekdays[i], quantity);
                i++;
            }
        }
    }

    // Close the files
    fclose(supplier_amount);
    fclose(data_file);
    printf("Data has been written to data_file.txt successfully.\n");
}

int main() {
    ReadQuantitiesFromFile(1); // Example usage
    return 0;
}
