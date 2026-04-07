# 🏢 Apartment Rent Sorting System

This project is a **C++ program** that reads apartment data from a CSV file and sorts it using different sorting algorithms.

It focuses on comparing the performance of:

* Quick Sort
* Heap Sort

---

## 📂 Project Description

The system processes a dataset containing apartment listings in **Kuala Lumpur & Selangor** and sorts them based on:

* Monthly Rent
* Apartment Size

The program also measures the **execution time** of each sorting algorithm for comparison.

---

## ⚙️ Features

* Read and clean CSV dataset
* Handle missing and inconsistent data
* Sort data using:

  * Quick Sort
  * Heap Sort
* Output sorted results into new CSV files
* Measure sorting performance (time taken)

---

## 🧱 Data Structure

Each apartment is stored using a struct:

```cpp
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
```

The program stores up to **19,991 records**.

---

## 📊 Sorting Algorithms Used

### 1. Quick Sort

* Average time complexity: O(n log n)
* Fast in practice
* Uses divide-and-conquer approach

### 2. Heap Sort

* Time complexity: O(n log n)
* Consistent performance
* Uses binary heap structure

---

## 📁 Output Files

After running the program, the following files will be generated:

* `HeapSort(monthly_rent)-Mudah-Apartment-KL-Selangor.csv`
* `HeapSort(Size)-Mudah-Apartment-KL-Selangor.csv`
* `QuickSort(Monthly_Rent)-Mudah-Apartment-KL-Selangor.csv`
* `QuickSort(Size)-Mudah-Apartment-KL-Selangor.csv`

---

## 🚀 How to Run

1. Make sure you have a C++ compiler (e.g. g++)
2. Place the dataset file in the same folder:

   ```
   mudah-apartment-kl-selangor.csv
   ```
3. Compile the program:

   ```bash
   g++ RentSystem.cpp -o RentSystem
   ```
4. Run the program:

   ```bash
   ./RentSystem
   ```

---

## 📝 Notes

* Missing values are handled by replacing with default values (e.g., 0 or "N/A")
* Strings like `"RM"` and `"per month"` are cleaned before processing
* Sorting is done on copies of the dataset to preserve original data

---

## 👥 Authors

* Ooi Chong Ming
* Yeoh Zi Qing Bryan
* Sim Sau Yang
