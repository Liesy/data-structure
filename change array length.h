//�ı����鳤��
template<class T>
void changeLength(T*& arr, int oldLength, int newLength)
{
	T* temp = new T[newLength];
	int number = min(oldLength, newLength);
	copy(arr, arr + number, temp); //�����ֱ�����ָ�룬ĩָ�룬Ŀ��λ��ָ��
	delete[]arr;
	arr = temp;
}