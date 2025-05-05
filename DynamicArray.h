#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdexcept>

//Dynamic array class template
template <typename T>
class DynamicArray {
public:
	DynamicArray(int capacity); //Constructor with initial capacity
	DynamicArray(); //Default constructor
	~DynamicArray(); //Destructor
	DynamicArray(const DynamicArray& other); //Copy constructor
	DynamicArray& operator=(const DynamicArray& other); //Copy assignment operator
	void pushBack(const T& element); //Add element to the end
	void popBack(); //Remove last element
	void popFront(); //Remove first element
	void insert(int index, const T& element); //Insert element at index
	void remove(int index); //Remove element at index
	void clear(); //Clear the array
	T& at(int index); //Get element at index
	T& operator[](int index); //Overload [] operator for non-const access
	const T& operator[](int index) const; //Overload [] operator for const access
	const T& get(int index) const; //Get element at index (const version)
	const T& back() const; //Get last element (const version)
	const T& front() const; //Get first element (const version)
	int size() const; //Get size of the array
	int capacity() const; //Get capacity of the array
	bool empty() const; //Check if the array is empty
	int find(const T& element) const; //Find element in the array
	bool contains(const T& element) const; //Check if the array contains element
	void resize(); //Resize the array if needed
private:
	T* array_; //Pointer to the array
	int size_; //Current size of the array
	int capacity_; //Current capacity of the array
	constexpr static int DEFAULT_CAPACITY = 10; //Default capacity
};

//Constructor with initial capacity
template <typename T>
DynamicArray<T>::DynamicArray(int capacity) {
	if (capacity < 0)
		throw std::out_of_range("Array capacity cannot be negative"); //Check for negative capacity
	array_ = new T[capacity]; //Allocate memory for the array
	capacity_ = capacity; //Set capacity
	size_ = 0; //Set size to 0
}

//Default constructor
template <typename T>
DynamicArray<T>::DynamicArray() {
	array_ = new T[DEFAULT_CAPACITY]; //Allocate memory for the array
	capacity_ = DEFAULT_CAPACITY; //Set default capacity
	size_ = 0; //Set size to 0
}

//Destructor
template <typename T>
DynamicArray<T>::~DynamicArray() {
	delete[] array_; //Deallocate memory for the array
	array_ = nullptr; //Set pointer to null
	size_ = 0; //Set size to 0
	capacity_ = 0; //Set capacity to 0
}

//Copy assignment operator
template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other) {
	capacity_ = other.capacity_; //Copy capacity
	size_ = other.size_; //Copy size
	array_ = new T[capacity_]; //Allocate memory for the array
	for (int i = 0; i < size_; i++)
		array_[i] = other.array_[i]; //Copy elements from other array
}

//Copy constructor
template <typename T>  
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {  
   if (this != &other) { // Check for self-assignment  
       delete[] array_; // Deallocate old array  
       capacity_ = other.capacity_; // Copy capacity  
       size_ = other.size_; // Copy size  
       array_ = new T[capacity_]; // Allocate memory for the array  
       for (int i = 0; i < size_; i++)  
           array_[i] = other.array_[i]; // Copy elements from other array  
   }  
   return *this; // Return current object  
}

//Add element to the end
template <typename T>
void DynamicArray<T>::pushBack(const T& element) {
	if (capacity_ <= size_)
		resize(); //Resize if needed
	array_[size_] = element; //Add element to the end
	size_++; //Increase size
}

//Remove last element
template <typename T>
void DynamicArray<T>::popBack() {
	if (size_ > 0)
		size_--; //Decrease size
	else
		throw std::out_of_range("Array is empty"); //Check if array is empty
}

//Remove first element
template <typename T>
void DynamicArray<T>::popFront() {
	remove(0); //Remove first element
}

//Insert element at index
template <typename T>
void DynamicArray<T>::insert(int index, const T& element) {
	if (index < 0 || index > size_)
		throw std::out_of_range("Index out of range"); //Check for valid index
	if (size_ >= capacity_)
		resize(); //Resize if needed
	for (int i = size_; i > index; i--)
		array_[i] = array_[i - 1]; //Shift elements to the right
	array_[index] = element; //Insert element at index
	size_++; //Increase size
}

//Remove element at index
template <typename T>
void DynamicArray<T>::remove(int index) {
	if (index < 0 || index >= size_)
		throw std::out_of_range("Index out of range"); //Check for valid index
	for (int i = index; i < size_ - 1; i++)
		array_[i] = array_[i + 1]; //Shift elements to the left
	size_--; //Decrease size
}

//Clear the array
template <typename T>
void DynamicArray<T>::clear() {
	size_ = 0; //Set size to 0
}

//Add element to the end
template <typename T>
T& DynamicArray<T>::at(int index) {
	if (index < 0 || index >= size_)
		throw std::out_of_range("Index out of range"); //Check for valid index
	return array_[index]; //Return element at index
}

//Overload [] operator for non-const access
template <typename T>  
T& DynamicArray<T>::operator[](int index) {  
	return at(index); //Return element at index
}  

//Overload [] operator for const access
template <typename T>  
const T& DynamicArray<T>::operator[](int index) const {  
	return get(index); //Return element at index
}

//Get element at index (const version)
template <typename T>
const T& DynamicArray<T>::get(int index) const {
	if (index < 0 || index >= size_)
		throw std::out_of_range("Index out of range"); //Check for valid index
	return array_[index]; //Return element at index
}

//Get last element (const version)
template <typename T>
const T& DynamicArray<T>::back() const {
	if (size_ <= 0)
		throw std::out_of_range("Array is empty"); //Check if array is empty
	return array_[size_ - 1]; //Return last element
}

//Get first element (const version)
template <typename T>
const T& DynamicArray<T>::front() const {
	if (size_ <= 0)
		throw std::out_of_range("Array is empty"); //Check if array is empty
	return array_[0]; //Return first element
}

//Get size of the array
template <typename T>
int DynamicArray<T>::size() const {
	return size_; //Return size
}

//Get capacity of the array
template <typename T>
int DynamicArray<T>::capacity() const {
	return capacity_; //Return capacity
}

//Check if the array is empty
template <typename T>
bool DynamicArray<T>::empty() const {
	return size_ == 0; //Check if size is 0
}

//Check if the array contains element
template <typename T>
int DynamicArray<T>::find(const T& element) const {
	for (int i = 0; i < size_; i++)
		if (array_[i] == element)
			return i; //Return index of element if found
	return -1; //Return -1 if not found
}

//Check if the array contains element
template <typename T>
bool DynamicArray<T>::contains(const T& element) const {
	return find(element) > -1; //Check if element is found
}

//Resize the array if needed
template <typename T>
void DynamicArray<T>::resize() {
	int newCapacity = capacity_ > 0 ? capacity_ * 2 : DEFAULT_CAPACITY; //Double the capacity
	T* newArray = new T[newCapacity]; //Allocate memory for new array
	for (int i = 0; i < size_; i++)
		newArray[i] = array_[i]; //Copy elements to new array
	delete[] array_; //Deallocate old array
	array_ = newArray; //Set new array
	capacity_ = newCapacity; //Set new capacity
}

#endif // !DYNAMIC_ARRAY_H
