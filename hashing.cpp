#include<iostream>
#include<utility>
#include<cstddef>
#include"illegalParameterValue.h"
using namespace std;

//ͷ�ļ�utility��ʹ��pair��ģ��
//ͷ�ļ�cstddef��ʹ��size_t

//�ڵ�-------------------------------------------------------------
template <class K, class E>
struct pairNode
{
    typedef pair<const K, E> pairType;  //����������
    pairType element;           //���ݣ������key����Ϣ����
    pairNode<K, E>* next;   //ָ����һ������
    pairNode(const pairType& thePair) :element(thePair) {}
    pairNode(const pairType& thePair, pairNode<K, E>* theNext) :element(thePair) { next = theNext; }
};
//�ѹؼ���theKeyת��Ϊ�Ǹ�������------------------
template<>
class hash<string>
{
public:
    size_t operator() (const string theKey) const
    {
        unsigned long hashValue = 0;
        int length = (int)theKey.length();
        for (int i = 0; i < length; i++)
            hashValue = 5 * hashValue + theKey.at(i);
        return size_t(hashValue);
    }
};
//ɢ�е����鶨��----------------------------------------
template<class K, class E>
class hashTable
{
public:
    //���캯������������
    hashTable(int theDivisor = 11);
    ~hashTable() { delete[] table; }
    //����
    bool empty() const { return dSize == 0; }//�п�
    int size() const { return dSize; }//����Ԫ�ظ���
    pair<const K, E>* find(const K&) const;//����������������Ϣ
    void insert(const pair<const K, E>&);//�����f (k)����Ԫ�ط���f (k)λ��
    void del(E&);//ɾ��
protected:
    int search(const K&) const;//�����f (k)��Ȼ�󿴱���f (k)���Ƿ���Ԫ��(��������)
    pair<const K, E>** table;//���ָ���ɢ�б�
    hash<K> hash;//�ѹؼ���Kӳ��Ϊһ������
    int dSize;//���е�Ԫ�ظ���
    int divisor;//������
};
//���캯��-----------------------------------------
template<class K, class E>
hashTable<K, E>::hashTable(int theDivisor)
{
    divisor = theDivisor;
    dSize = 0;
    table = new pair<const K, E> * [divisor];
    for (int i = 0; i < divisor; i++)
        table[i] = NULL;
}
//�����Ƿ���theKey��Ԫ���ڱ���,���򷵻�ȫ����Ϣ--------------------------
template<class K, class E>
pair<const K, E>* hashTable<K, E>::find(const K& theKey) const
{
    int index = search(theKey);
    if (table[index] == NULL || table[index]->first != theKey)
        return NULL;//���ڱ���
    return table[index];
}
//���루K,E�������Ѿ����ڣ��ڰѵڶ������޸�----------------------------
template<class K, class E>
void hashTable<K, E>::insert(const pair<const K, E>& thePair)
{
    int index = search(thePair.first);
    if (table[index] == NULL)//û�ҵ������ұ�û��
    {
        table[index] = new pair<const K, E>(thePair);
        dSize++;
    }
    else
        if (table[index]->first == thePair.first)//�ҵ���,����Ӧ��ֵ
            table[index]->second = thePair.second;
        else//������
            throw illegalParameterValue("table full");
}
//�������������ҵ���Ԫ�ػ���õ�Ԫ���򷵻�λ���±�------------------------
template<class K, class E>
int hashTable<K, E>::search(const K& theKey) const
{
    int homeBucket = (int)hash(theKey) % divisor;//������Ҫװ���Ͱ��λ��
    int currentBucket = homeBucket;//��ʱ������һ��Ͱ
    do
    {
        if (table[currentBucket] == NULL || table[currentBucket]->first == theKey)
            return currentBucket;
        currentBucket = (currentBucket + 1) % divisor;//ָ����һ��Ͱ
    } while (currentBucket != homeBucket);
    //�ֻص������homeBucket
    return currentBucket;//��ʱ��ȫ��
}