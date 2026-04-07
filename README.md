**🏢 Apartment Sorting System (Data Structures Project)**

**📌 Overview**
This project implements and analyzes multiple sorting algorithms to determine the most efficient method for sorting large-scale property data.

The dataset used contains 10,000+ apartment listings from Kuala Lumpur and Selangor, including attributes such as monthly rent, size, location, and more.

The system is developed in C++ and focuses on:
  Data processing from CSV files
  Implementing sorting algorithms
  Performance comparison through experiments
  
**🎯 Objectives**
Implement multiple sorting algorithms:
  Merge Sort
  Quick Sort
  Heap Sort
  Selection Sort
  Insertion Sort
Compare their time and space complexity
Evaluate performance on a real-world dataset
Identify the most efficient algorithm for large datasets

**🧠 Key Features
📂 Data Processing**
Reads and parses CSV dataset (mudah-apartment-kl-selangor.csv)
Handles:
  Missing values
  Inconsistent formats (e.g. "RM 1200 per month")
  String-to-integer conversion
Stores data using a custom struct Apartment

**🏗️ Data Structure**
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

**⚙️ Algorithms Implemented**
**🔹 Quick Sort**
Average Time: O(n log n)
Worst Time: O(n²)
Space: O(log n)
Fastest in this project

**🔹 Heap Sort**
Time: O(n log n) (all cases)
Space: O(1)
More stable performance but slower in practice

**🔹 Merge Sort**
Time: O(n log n)
Space: O(n)
Stable but uses extra memory

**🔹 Selection Sort**
Time: O(n²)
Space: O(1)
Inefficient for large datasets

**🔹 Insertion Sort**
Best: O(n)
Average/Worst: O(n²)
Suitable for small or nearly sorted data

**📊 Performance Results**
| Algorithm   | Rent (ms) | Size (ms) |
|------------|----------:|----------:|
| Quick Sort | **196**   | 230.8     |
| Heap Sort  | 399.6     | 408.2     |

**🔍 Observations**
Quick Sort is significantly faster than Heap Sort
Best performance: Quick Sort (Monthly Rent)
Heap Sort is more consistent but slower

**🧪 How It Works**
Read dataset line-by-line
Parse and clean each field
Store data into array of Apartment
Duplicate dataset to preserve original data
Apply sorting algorithm:
Sort by monthly_rent or size
Measure execution time
Export sorted results to CSV files

**📁 Output**
The program generates sorted CSV files:
  QuickSort(Monthly_Rent).csv
  HeapSort(Monthly_Rent).csv
  QuickSort(Size).csv
  HeapSort(Size).csv
  
**🚀 How to Run**
Requirements
C++ compiler (e.g. g++)
Dataset file in the same directory
Compile
g++ main.cpp -o sorter
Run
./sorter

**📌 Conclusion**
Quick Sort is the best-performing algorithm for this dataset
Heap Sort provides consistent performance but with higher overhead
Simpler algorithms (Selection, Insertion) are not suitable for large datasets
