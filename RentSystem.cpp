#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int MAX_APARTMENTS = 19991; // Total observations in dataset

// Struct to represent an apartment
struct Apartment {
    string ads_id;
    string prop_name;
    string completion_year;
    int monthly_rent;
    string location;
    string property_type;
    int rooms;
    int parking;
    int bathroom;
    int size;
    string furnished;
};

// Global array to store apartments and a counter for the number of apartments
Apartment apartments[MAX_APARTMENTS];
int apartment_count = 0;

// Function prototypes
void parseCSVLine(string line, string cells[], int max_cells);
void quicksortMonthlyRent(Apartment arr[], int low, int high);
void quicksortSize(Apartment arr[], int low, int high);
int partitionMonthlyRent(Apartment arr[], int low, int high);
int partitionSize(Apartment arr[], int low, int high);
void heapifyMonthlyRent(Apartment arr[], int n, int i);
void heapifySize(Apartment arr[], int n, int i);
void heapsortMonthlyRent(Apartment arr[], int n);
void heapsortSize(Apartment arr[], int n);
bool isInteger(const string &s);
void swap(Apartment &a, Apartment &b);

int main() {
    string filename = "mudah-apartment-kl-selangor.csv";
    ifstream file(filename);
    string line;

    // Check if the file is opened successfully
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return 1;
    }

    getline(file, line);  // Skip header row

    // Read the CSV file line by line
    while (getline(file, line) && apartment_count < MAX_APARTMENTS) {
        string cells[11];
        parseCSVLine(line, cells, 11); // Parse the line into individual cells
        Apartment& apartment = apartments[apartment_count];

        // Ensure the line has enough fields
        if (!cells[0].empty()) {
            // Populate the apartment struct with data from cells
            apartment.ads_id = cells[0];
            apartment.prop_name = !cells[1].empty() ? cells[1] : "N/A";
            apartment.completion_year = !cells[2].empty() ? cells[2] : "N/A";

            // Parse monthly rent
            if (!cells[3].empty()) {
                try {
                    string rent_str = cells[3];
                    size_t pos = rent_str.find("RM ");
                    if (pos != string::npos) {
                        rent_str.erase(0, pos + 3);  // Remove "RM "
                        pos = rent_str.find(" per month");
                        if (pos != string::npos) {
                            rent_str.erase(pos);  // Remove " per month"
                        }
                        // Remove spaces from rent_str
                        rent_str.erase(remove(rent_str.begin(), rent_str.end(), ' '), rent_str.end());
                        if (isInteger(rent_str)) {
                            apartment.monthly_rent = stoi(rent_str);
                        } else {
                            apartment.monthly_rent = 0;  // Default value if invalid
                        }
                    } else {
                        apartment.monthly_rent = 0;  // Default value
                    }
                } catch (const std::invalid_argument&) {
                    apartment.monthly_rent = 0;  // Default value
                }
            } else {
                apartment.monthly_rent = 0;  // Default value
            }

            // Parse other fields
            apartment.location = cells[4];
            apartment.property_type = cells[5];
            apartment.rooms = isInteger(cells[6]) ? stoi(cells[6]) : 0;  // Default value
            apartment.parking = isInteger(cells[7]) ? stoi(cells[7]) : 0;  // Default value
            apartment.bathroom = isInteger(cells[8]) ? stoi(cells[8]) : 0;  // Default value

            // Parse size
            if (!cells[9].empty()) {
                try {
                    string size_str = cells[9];
                    size_t pos = size_str.find(" sq.ft.");
                    if (pos != string::npos) {
                        size_str.erase(pos);  // Remove " sq.ft."
                    }
                    apartment.size = isInteger(size_str) ? stoi(size_str) : 0;  // Default value
                } catch (const std::invalid_argument&) {
                    apartment.size = 0;  // Default value
                }
            } else {
                apartment.size = 0;  // Default value
            }

            apartment.furnished = !cells[10].empty() ? cells[10] : "N/A";

            // Increment the count of apartments
            apartment_count++;
        } else {
            cerr << "Incomplete line: " << line << endl;
        }
    }

    file.close();

    //////////////////////////////////////////////////////////////////////////////
    /////////////////////////CLEANING & READING COMPLETED/////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    string header = "ads_id,prop_name,completion_year,monthly_rent (RM),location,property_type,rooms,parking,bathroom,size (sq.ft.),furnished";

    // Measure and sort for Heap Sort (monthly rent)
    // Create a copy of the apartments array to avoid modifying the original array
    Apartment* apartmentsCopy1 = new Apartment[apartment_count];
    copy(apartments, apartments + apartment_count, apartmentsCopy1);

    // Record the start time of the heap sort operation for performance measurement
    auto start1 = high_resolution_clock::now();

    // Perform heap sort on the apartmentsCopy1 array based on monthly rent
    heapsortMonthlyRent(apartmentsCopy1, apartment_count);

    // Record the stop time of the heap sort operation for performance measurement
    auto stop1 = high_resolution_clock::now();

    // Calculate the duration of the heap sort operation in milliseconds
    auto duration1 = duration_cast<milliseconds>(stop1 - start1);

    // Open a file to write the sorted apartment data
    ofstream outFile1("HeapSort(monthly_rent)-Mudah-Apartment-KL-Selangor.csv");
    outFile1 << header << endl;

    // Loop through the sorted apartment array and write each apartment's details to the file
    for (int i = 0; i < apartment_count; i++) {
        Apartment& apartment = apartmentsCopy1[i];
        outFile1 << apartment.ads_id << ","
                 << apartment.prop_name << ","
                 << apartment.completion_year << ","
                 << apartment.monthly_rent << ","
                 << apartment.location << ","
                 << apartment.property_type << ","
                 << apartment.rooms << ","
                 << apartment.parking << ","
                 << apartment.bathroom << ","
                 << apartment.size << ","
                 << apartment.furnished << endl;
    }

    // Close the file
    outFile1.close();

    // Deallocate the memory used for the apartmentsCopy1 array
    delete[] apartmentsCopy1;

    cout << "Heap Sort (Monthly Rent) took " << duration1.count() << " milliseconds" << endl;



    // Measure and sort for Heap Sort (Size)
    // Create a copy of the apartments array to avoid modifying the original array
    Apartment* apartmentsCopy2 = new Apartment[apartment_count];
    copy(apartments, apartments + apartment_count, apartmentsCopy2);

    // Record the start time of the heap sort operation for performance measurement
    auto start2 = high_resolution_clock::now();

    // Perform heap sort on the apartmentsCopy1 array based on size
    heapsortSize(apartmentsCopy2, apartment_count);

    // Record the stop time of the heap sort operation for performance measurement
    auto stop2 = high_resolution_clock::now();

    // Calculate the duration of the heap sort operation in milliseconds
    auto duration2 = duration_cast<milliseconds>(stop2 - start2);

    // Open a file to write the sorted apartment data
    ofstream outFile2("HeapSort(Size)-Mudah-Apartment-KL-Selangor.csv");

    // Write the header line to the file
    outFile2 << header << endl;

    // Loop through the sorted apartment array and write each apartment's details to the file
    for (int i = 0; i < apartment_count; i++) {
        Apartment& apartment = apartmentsCopy2[i];
        outFile2 << apartment.ads_id << ","
                 << apartment.prop_name << ","
                 << apartment.completion_year << ","
                 << apartment.monthly_rent << ","
                 << apartment.location << ","
                 << apartment.property_type << ","
                 << apartment.rooms << ","
                 << apartment.parking << ","
                 << apartment.bathroom << ","
                 << apartment.size << ","
                 << apartment.furnished << endl;
    }

    // Close the file
    outFile2.close();

    // Deallocate the memory used for the apartmentsCopy1 array
    delete[] apartmentsCopy2;

    cout << "Heap Sort (Size) took " << duration2.count() << " milliseconds" << endl;



    // Measure and sort for Quick Sort (Monthly Rent)
    // Create a copy of the apartments array to avoid modifying the original array
    Apartment* apartmentsCopy3 = new Apartment[apartment_count];
    copy(apartments, apartments + apartment_count, apartmentsCopy3);

    // Record the start time of the heap sort operation for performance measurement
    auto start3 = high_resolution_clock::now();

    // Perform quick sort on the apartmentsCopy1 array based on monthly rent
    quicksortMonthlyRent(apartmentsCopy3, 0, apartment_count - 1);

    // Record the stop time of the quick sort operation for performance measurement
    auto stop3 = high_resolution_clock::now();

    // Calculate the duration of the quick sort operation in milliseconds
    auto duration3 = duration_cast<milliseconds>(stop3 - start3);

    // Open a file to write the sorted apartment data
    ofstream outFile3("QuickSort(Monthly_Rent)-Mudah-Apartment-KL-Selangor.csv");

    // Write the header line to the file
    outFile3 << header << endl;

    // Loop through the sorted apartment array and write each apartment's details to the file
    for (int i = 0; i < apartment_count; i++) {
        Apartment& apartment = apartmentsCopy3[i];
        outFile3 << apartment.ads_id << ","
                 << apartment.prop_name << ","
                 << apartment.completion_year << ","
                 << apartment.monthly_rent << ","
                 << apartment.location << ","
                 << apartment.property_type << ","
                 << apartment.rooms << ","
                 << apartment.parking << ","
                 << apartment.bathroom << ","
                 << apartment.size << ","
                 << apartment.furnished << endl;
    }

    // Close the file
    outFile3.close();

    // Deallocate the memory used for the apartmentsCopy1 array
    delete[] apartmentsCopy3;

    cout << "Quick Sort (Monthly Rent) took " << duration3.count() << " milliseconds" << endl;



    // Measure and sort for Quick Sort (Size)
    // Create a copy of the apartments array to avoid modifying the original array
    Apartment* apartmentsCopy4 = new Apartment[apartment_count];
    copy(apartments, apartments + apartment_count, apartmentsCopy4);

    // Record the start time of the heap sort operation for performance measurement
    auto start4 = high_resolution_clock::now();

    // Perform quick sort on the apartmentsCopy1 array based on size
    quicksortSize(apartmentsCopy4, 0, apartment_count - 1);

    // Record the stop time of the quick sort operation for performance measurement
    auto stop4 = high_resolution_clock::now();

    // Calculate the duration of the quick sort operation in milliseconds
    auto duration4 = duration_cast<milliseconds>(stop4 - start4);

    // Open a file to write the sorted apartment data
    ofstream outFile4("QuickSort(Size)-Mudah-Apartment-KL-Selangor.csv");

    // Write the header line to the file
    outFile4 << header << endl;

    // Loop through the sorted apartment array and write each apartment's details to the file
    for (int i = 0; i < apartment_count; i++) {
        Apartment& apartment = apartmentsCopy4[i];
        outFile4 << apartment.ads_id << ","
                 << apartment.prop_name << ","
                 << apartment.completion_year << ","
                 << apartment.monthly_rent << ","
                 << apartment.location << ","
                 << apartment.property_type << ","
                 << apartment.rooms << ","
                 << apartment.parking << ","
                 << apartment.bathroom << ","
                 << apartment.size << ","
                 << apartment.furnished << endl;
    }

    // Close the file
    outFile4.close();

    // Deallocate the memory used for the apartmentsCopy1 array
    delete[] apartmentsCopy4;

    cout << "Quick Sort (Size) took " << duration4.count() << " milliseconds" << endl;

    return 0;
}


// Function to parse a line of CSV into cells
// `line`: the CSV line to be parsed
// `cells`: an array to store the parsed cells
// `max_cells`: the maximum number of cells to store in the `cells` array

void parseCSVLine(string line, string cells[], int max_cells) {
    string cell;                // Temporary string to store individual cells
    bool insideQuote = false;   // Flag to indicate if the parser is inside a quoted string
    int cell_index = 0;         // Index to track the position in the `cells` array


    // Replace commas inside quotes with a placeholder
    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] == '"') {
            // Toggle the insideQuote flag when a quote is encountered
            insideQuote = !insideQuote;
        } else if (line[i] == ',' && insideQuote) {
            // If a comma is found inside a quoted string, replace it with a placeholder
            line[i] = '=';  // Replace comma with placeholder
        }
    }

    // Use a stringstream to split the line by commas
    stringstream ss(line);
    while (getline(ss, cell, ',') && cell_index < max_cells) {
        // Replace placeholder back to comma
        replace(cell.begin(), cell.end(), '=', ',');
        // Store the cell in the cells array
        cells[cell_index++] = cell;
    }
}

// Function to check if a string is an integer
bool isInteger(const string &s) {
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

// Function to swap two Apartment structs
void swap(Apartment &a, Apartment &b) {
    Apartment temp = a;
    a = b;
    b = temp;
}

// Quicksort functions for sorting by monthly rent
// `arr`: the array of Apartment objects to be sorted
// `low`: the starting index of the array (or sub-array) to be sorted
// `high`: the ending index of the array (or sub-array) to be sorted
void quicksortMonthlyRent(Apartment arr[], int low, int high) {
    // Check if the low index is less than the high index
    if (low < high) {

        // Partition the array and get the pivot index
        int pi = partitionMonthlyRent(arr, low, high);

        // Recursively sort the elements before the pivot
        quicksortMonthlyRent(arr, low, pi - 1);

        // Recursively sort the elements after the pivot
        quicksortMonthlyRent(arr, pi + 1, high);
    }
}

// Function to partition the array for QuickSort
// `arr`: the array of Apartment objects to be partitioned
// `low`: the starting index of the array (or sub-array) to be partitioned
// `high`: the ending index of the array (or sub-array) to be partitioned
// Returns the index of the pivot element after partitioning
int partitionMonthlyRent(Apartment arr[], int low, int high) {
    // Choose the last element as the pivot
    int pivot = arr[high].monthly_rent;
    int i = low - 1;    // Index of the smaller element

    // Loop through the array from `low` to `high - 1`
    for (int j = low; j <= high - 1; j++) {

        // If the current element is smaller than the pivot
        if (arr[j].monthly_rent < pivot) {
            i++;
            swap(arr[i], arr[j]); // Swap the current element with the element at index `i`
        }
    }

    // Swap the pivot element with the element at index `i + 1`
    swap(arr[i + 1], arr[high]);
    return i + 1;   // Return the index of the pivot element
}

// Heapsort functions for sorting by monthly rent
// `arr`: the array of Apartment objects
// `n`: the size of the heap
// `i`: the index of the root of the subtree
void heapifyMonthlyRent(Apartment arr[], int n, int i) {
    int largest = i;        // Initialize largest as root
    int left = 2 * i + 1;   // Left child index
    int right = 2 * i + 2;  // Right child index

    // If the left child exists and is greater than the root
    if (left < n && arr[left].monthly_rent > arr[largest].monthly_rent)
        largest = left;
    
    // If the right child exists and is greater than the largest so far
    if (right < n && arr[right].monthly_rent > arr[largest].monthly_rent)
        largest = right;

    // If the largest is not root
    if (largest != i) {
        // Swap the root with the largest
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected subtree
        heapifyMonthlyRent(arr, n, largest);
    }
}

// `arr`: the array of Apartment objects to be sorted
// `n`: the size of the array
void heapsortMonthlyRent(Apartment arr[], int n) {
    // Build a max heap from the array
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyMonthlyRent(arr, n, i);

    // One by one extract elements from the heap
    for (int i = n - 1; i > 0; i--) {
        // Move the current root to the end
        swap(arr[0], arr[i]);

        // Call heapify on the reduced heap
        heapifyMonthlyRent(arr, i, 0);
    }
}


// Quicksort functions for sorting by size
void quicksortSize(Apartment arr[], int low, int high) {
    if (low < high) {
        int pi = partitionSize(arr, low, high);
        quicksortSize(arr, low, pi - 1);
        quicksortSize(arr, pi + 1, high);
    }
}

int partitionSize(Apartment arr[], int low, int high) {
    int pivot = arr[high].size;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].size < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Heapsort functions for sorting by size
void heapifySize(Apartment arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].size > arr[largest].size)
        largest = left;

    if (right < n && arr[right].size > arr[largest].size)
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapifySize(arr, n, largest);
    }
}

void heapsortSize(Apartment arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifySize(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapifySize(arr, i, 0);
    }
}
