/**
 * @file array_to_heap.cpp
 * @author Zachary Chair (zacharychair@ieee.org)
 * @brief This program converts an inputted array into a min-heap and displays the swaps performed to convert to the array
 * @version 0.1
 * @date 2023-03-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class HeapBuilder {
private:
    vector<int> data_;
    vector< pair<int, int> > swaps_;

    void WriteResponse() const {
        cout << swaps_.size() << "\n";
        for (int i = 0; i < swaps_.size(); ++i) {
            cout << swaps_[i].first << " " << swaps_[i].second << "\n";
        }
    }

    void ReadData() {
        int n;
        
        cout << "Enter the size of the heap ";
        cin >> n;
        data_.resize(n);

        cout << "Enter the values of the heap " << endl;
        for (int i = 0; i < n; ++i) {
            cin >> data_[i];
        }
    }

    void GenerateSwaps() {
        /** ensures the swaps vector is empty*/
        swaps_.clear();
        int n = data_.size();

        /** loops through top half of the elements in the vector and checks their heap property*/
        for (int i = (n + 1) / 2; i >= 0; i--) {
            SiftDown(i);
        }
    }

    void SiftDown(int pos) {
        int size = data_.size();
        int minIndex = pos;
        int leftChildIndex = (2 * pos) + 1;
        int rightChildIndex = (2 * pos) + 2;

        /** checks if left child is less than the parent*/
        if ((leftChildIndex < size) && (data_[leftChildIndex] <= data_[minIndex])) {
            /** if the left child is less than the parent then set new position for the index of the minimum value*/
            minIndex = leftChildIndex;
        }

        /** checks if right child is less than the parent*/
        if ((rightChildIndex < size) && (data_[rightChildIndex] <= data_[minIndex])) {
            /** if the right child is less than the parent then set new position for the index of the minimum value*/
            minIndex = rightChildIndex;
        }

        /** if the minimum position was changed then swap the parent with the lowest valued child*/
        if (pos != minIndex) {
            int temp = data_[pos];
            data_[pos] = data_[minIndex];
            data_[minIndex] = temp;
            /** record what was swapped*/
            swaps_.push_back(pair(pos, minIndex));
            /** repeat the process for the new minimum value to check its heap property*/
            SiftDown(minIndex);
        }
    }

public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};


int main() {
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}