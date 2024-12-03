#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void generate_histogram(const char *title, const char *data_file) {
    // File pointer for reading data
    FILE *file = fopen(data_file, "r");
    if (file == NULL) {
        printf("Error: Unable to open data file '%s'.\n", data_file);
        return;
    }

    // Arrays to hold the parsed data
    char days[7][20];   // Days of the week (string format)
    int data[7];         // Quantities for each day
    int size = 0;        // To track number of valid entries

    // Read data from the file
    while (fscanf(file, "%s %d", days[size], &data[size]) == 2) {
        size++;
        if (size >= 7) break;  // Limit to 7 days (Monday to Sunday)
    }
    fclose(file);

    // Check if we have valid data for all 7 days
    if (size != 7) {
        printf("Error: Data file should contain 7 lines for each day of the week.\n");
        return;
    }

    // Create and write data to a file for Gnuplot
    FILE *gnuplot_data_file = fopen("data.txt", "w");
    if (gnuplot_data_file == NULL) {
        printf("Error: Unable to create data file for Gnuplot.\n");
        return;
    }

    // Writing data to the file
    for (int i = 0; i < size; i++) {
        fprintf(gnuplot_data_file, "%s %d\n", days[i], data[i]); // Format: day quantity
    }
    fclose(gnuplot_data_file);

    // Create a Gnuplot script file
    FILE *gnuplot_script = fopen("plot_commands.gp", "w");
    if (gnuplot_script == NULL) {
        printf("Error: Unable to create Gnuplot script file.\n");
        return;
    }

    // Writing Gnuplot commands for histogram
    fprintf(gnuplot_script, "set terminal pngcairo size 1920,1080 enhanced\n");  // Full-screen resolution
    fprintf(gnuplot_script, "set output 'histogram.png'\n");
    fprintf(gnuplot_script, "set title '%s'\n", title); // Use provided title
    fprintf(gnuplot_script, "set xlabel 'Days of the Week'\n");
    fprintf(gnuplot_script, "set ylabel 'Quantities'\n");
    fprintf(gnuplot_script, "set grid\n");
    fprintf(gnuplot_script, "set style data histograms\n");
    fprintf(gnuplot_script, "set style fill solid border -1\n");
    fprintf(gnuplot_script, "set boxwidth 0.6\n");

    // Custom color for Saturday and Sunday (for example, blue)
    fprintf(gnuplot_script, "set style line 1 lc rgb 'blue' pt 7 ps 1.5 lw 2\n");  
    fprintf(gnuplot_script, "plot 'data.txt' using 2:xtic(1) title 'Quantities' ls 1\n");

    fclose(gnuplot_script);

    // Run Gnuplot
    int result = system("gnuplot plot_commands.gp");
    if (result != 0) {
        printf("Error: Gnuplot command failed.\n");
        return;
    }

    printf("Histogram generated successfully! Open 'histogram.png' to view the plot.\n");
}

int main() {
    const char *data_file = "data_file.txt"; 
    char title[100];  // Ensure this is large enough to hold the full title
    // Concatenate strings using strcat
    strcpy(title, "Weekly Sales Histogram of supplier ");  // Copy first part
    strcat(title, "t88");  // Append second part
    
    generate_histogram(title, data_file);
    ReadQuantitiesFromFile(1); // Example usage
    return 0;
}
