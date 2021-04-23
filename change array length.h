//改变数组长度
template<class T>
void changeLength(T*& arr, int oldLength, int newLength)
{
	T* temp = new T[newLength];
	int number = min(oldLength, newLength);
	copy(arr, arr + number, temp); //参数分别是首指针，末指针，目标位置指针
	delete[]arr;
	arr = temp;
}