#include<iostream>
#include<utility>
#include<cstddef>
#include"illegalParameterValue.h"
using namespace std;

//头文件utility中使用pair类模板
//头文件cstddef中使用size_t

//节点-------------------------------------------------------------
template <class K, class E>
struct pairNode
{
    typedef pair<const K, E> pairType;  //定义新类型
    pairType element;           //数据，本身分key、信息部分
    pairNode<K, E>* next;   //指向下一个数据
    pairNode(const pairType& thePair) :element(thePair) {}
    pairNode(const pairType& thePair, pairNode<K, E>* theNext) :element(thePair) { next = theNext; }
};
//把关键词theKey转换为非负的整数------------------
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
//散列的数组定义----------------------------------------
template<class K, class E>
class hashTable
{
public:
    //构造函数、析构函数
    hashTable(int theDivisor = 11);
    ~hashTable() { delete[] table; }
    //方法
    bool empty() const { return dSize == 0; }//判空
    int size() const { return dSize; }//返回元素个数
    pair<const K, E>* find(const K&) const;//搜索并返回所有信息
    void insert(const pair<const K, E>&);//计算出f (k)，把元素放在f (k)位置
    void del(E&);//删除
protected:
    int search(const K&) const;//计算出f (k)，然后看表中f (k)处是否有元素(返回索引)
    pair<const K, E>** table;//存放指针的散列表
    hash<K> hash;//把关键字K映射为一个整数
    int dSize;//表中的元素个数
    int divisor;//表容量
};
//构造函数-----------------------------------------
template<class K, class E>
hashTable<K, E>::hashTable(int theDivisor)
{
    divisor = theDivisor;
    dSize = 0;
    table = new pair<const K, E> * [divisor];
    for (int i = 0; i < divisor; i++)
        table[i] = NULL;
}
//查找是否含有theKey的元素在表中,在则返回全部信息--------------------------
template<class K, class E>
pair<const K, E>* hashTable<K, E>::find(const K& theKey) const
{
    int index = search(theKey);
    if (table[index] == NULL || table[index]->first != theKey)
        return NULL;//不在表中
    return table[index];
}
//插入（K,E），若已经存在，在把第二部分修改----------------------------
template<class K, class E>
void hashTable<K, E>::insert(const pair<const K, E>& thePair)
{
    int index = search(thePair.first);
    if (table[index] == NULL)//没找到，并且表没满
    {
        table[index] = new pair<const K, E>(thePair);
        dSize++;
    }
    else
        if (table[index]->first == thePair.first)//找到了,改相应的值
            table[index]->second = thePair.second;
        else//表满了
            throw illegalParameterValue("table full");
}
//遍历整个表，若找到该元素或空置单元，则返回位置下标------------------------
template<class K, class E>
int hashTable<K, E>::search(const K& theKey) const
{
    int homeBucket = (int)hash(theKey) % divisor;//理论上要装填的桶的位置
    int currentBucket = homeBucket;//此时正在哪一个桶
    do
    {
        if (table[currentBucket] == NULL || table[currentBucket]->first == theKey)
            return currentBucket;
        currentBucket = (currentBucket + 1) % divisor;//指向下一个桶
    } while (currentBucket != homeBucket);
    //又回到最初的homeBucket
    return currentBucket;//此时表全满
}