#include "object.h"
#include "list.h"
#include "fsarray.h"

#include <string>
#include <iostream>
using std::string;
using std::istream;
using std::ostream;

FSArray::FSArray(size_t capacity) : _capacity(capacity){
	_data = new Object*[_capacity];
	for (size_t i = 0; i < _capacity; i++) {
		_data[i] = nullptr;
	}
}
FSArray::FSArray(const FSArray& list) : _capacity(list._capacity){
	// Is there a bug here? --> Solved by setting _size to be protected
	_size = list._size;
	_data = new Object*[_capacity];
	for (size_t i = 0; i < _size; i++) { // Issa correction to the _capacity
		_data[i] = list.Get(i)->Clone();
	}
	for (size_t i = _size; i < _capacity; i++){
		_data[i] = nullptr;
	}
}
FSArray::~FSArray(){
	for (size_t i = 0; i < _size; i++) {
		delete _data[i];
	}
	delete[] _data;
}
const FSArray& FSArray::operator=(const FSArray& rhs){
	if (&rhs == this){
		return *this;
	}
	if (_capacity != rhs._capacity){
		Clear();
		delete[] _data;
		_capacity = rhs._capacity;
		_data = new Object*[_capacity];
		for (size_t i = 0; i < _capacity; i++) {
			_data[i] = nullptr;
		}
	}
	for (size_t i = 0; i < rhs.Size(); i++) {
		_data[i] = rhs.Get(i)->Clone();
	}
	return *this;
}

bool FSArray::Insert(Object* element, size_t position){
	// Check if the position is valid
	if (position > _size)
		return false;
	// Check if there is enough space
	if (_capacity == _size)
		return false;

	if (position < _size){ // We need to shift
		// WARNING WILL ROBINSON : Lost in Space Reference
		// Be careful with size_t when subtracting
		for (size_t i = _size; i > position; i--){
			_data[i] = _data[i - 1]; 
		}
	}
	_data[position] = element;
	_size++;
	return true;
}
int FSArray::IndexOf(Object* element)const{
	return -1;
}
Object* FSArray::Remove(size_t position){
	return nullptr;
}
Object* FSArray::Get(size_t position)const{
	return nullptr;
}
string FSArray::ToString()const{
	return "";
}
ostream& FSArray::Write(ostream& output)const{
	return output;
}
istream& FSArray::Read(istream& input){
	return input;
}
void FSArray::Clear(){
	for (size_t i = 0; i < Size(); i++) {
		delete _data[i];
		_data[i] = nullptr;
	}
	// Something missing here?
}
