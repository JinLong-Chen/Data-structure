#include<iostream.h>
#include<stdlib.h>
#include"linearList.h"
const int defaultSize=100;
template<class T>
class SeqList:public LinearList<T>{
    protected:
        T *data;
        int maxSize;
        int last;     //当前已存表项的最后位置（从0开始）
        void reSize(int newSize);
    public:
        SeqList(int sz=defaultSize);               //构造函数
        SeqList(SeqList<T>& L);                    //复制构造函数
        ~SeqList(){delete[] data;}                 //析构函数
        int Size()const{return maxSize;}           //计算表最大可容纳表项个数
        int Length()const{return last+1;}          //计算表长度
        int Search(T& x)const;                     //搜索X在表中位置，函数返回表项序号
        int Locate(int i)const;                    //定位第i个表项，函数返回表项序号
        bool getData(int i,T&x)const;              //取第i个表项的值
            {if(i>0&&i<=last+1){x=data[i-1];return true;}else return false;}
        void setData(int i,T& x);                  //用x修改第i个表项的值
            {if(i>0&&i<=last+1) data[i-1]=x;}
        bool Insert(int i,T& x);                   //在第i个表项之后插入x
        bool Remove(int i,T& x);                   //删除第i个表项，通过x返回表项的值
        bool IsEmpty()                             //判表空否，空则返回true,否则返回false
            {return (last==-1)?true:false}
        bool IsFull()                              //判表满否，满则返回true,否则返回false
            {return (last==maxSize-1)?true:false}
        void input()i                              //输入
        void output()i                             //输出
        SeqList(T) operator=(SeqList<T>& L);       //表整体赋值
}

template<class T>
SeqList<T>::SeqList(int sz){
    //构造函数 通过指定参数sz定义数组长度；
    if(sz > 0){
        maxSize=sz;
        last=-1;     //置表的实际长度为空
        data=new T[maxSize];     //创建循序表存储数组
        if(data==NULL)            //动态分配失败
            {cerr<<"存储分配错误！"<<endl;exit(1);}
    }
};

template<class T>
SeqList<T>::SeqList(SeqList<T>& L){
    //复制构造函数 用参数表中给出的已有顺序表初始化新建的顺序表。
    maxSize=L.size();
    last=L.length()-1;
    T value;
    data=new T[maxSize];
    if (data==NULL){
        cerr<<"存储分配错误！"<<endl;
        exit(1);
    }
    for(int i=1;i<=last+1;i++){
        L.getData(i,value);
        data[i-1]=value;
    }
};

template<class T>
void SeqList<T>::reSize(int newSize){
    //私有函数：扩充顺序表的存储数组空间大小，新数组的元素个数为newSize
    if(newSize<0)
        {cerr<<"无效的数组大小"<<endl;return;}
    if(newSize!=maxSize)
        T* newarray= new T[newSize];
        if(newarray==NULL)
            {cerr"存储分配错误！"<<endl;exit(1);};
        int n=last+1;
        T* srcptr = data;      //源数组首地址
        T* destptr = newarray; //目的数组首地址
        while(n--)*destptr++=*srcptr++; //保存源数组中old data;
        delete []data;
        data=newarray;
        maxSize=newSize;
};

template<class T>
int SeqList<T>::Search(T& x)const{
    //搜索函数：在表中顺序搜索与给定值x匹配的表项，找到则函数返回该表项是第几个元素。否则函数返回0，表示搜索失败
    for(int i=0;i<=last;i++){
        if(data[i]==x)          //顺序搜索
            return i+1;
    }    
    return 0;                   //搜索失败
};

template<class T>
int SeqList<T>::Locate(int i)const{
    if(i>=1&&i<=last+1)
        return i;
    else
        return 0;
};

template<class T>
bool SeqList<T>::Insert(int i,T& x){
//插入函数：将新元素x插入到表中第i个表项之后。若插入成功则返回true,插入失败则返回false。
    if(last==maxSize-1)return false; //表满 不能插入
    if(i<0||i>last+1) return false;  //参数i不合理，不能插入
    for(int j=last;j>=i;j--)    
        data[j+1]=data[j];           //依次后移，空出第i号位置
    data[i]=x;
    last++;
    return true;
};

template<class T>
bool SeqList<T>::Remove(int i,T& x){
    if(last==-1)return false;
    if(i<1||i>last+1)return false;
    x=data[i-1];
    for(int j=i;j<=last;j++){
        data[j-1]=data[j];
    }
    last--;
    return true;
};

template<class T>
void SeqList<T>::input(){
//从标准输入（键盘）逐个数据输入，建立顺序表
    cout<<"开始建立顺序表，请输入表中元素个数:";
    while(1){
        cin>>last;
        if(last<=maxSize)break;   
        cout<<"表元素个数输入错误，范围不能超过"<<maxSize-1<<":";
    }
    for(int i= 0;i<=last;i++){
        cin>>data[i];
        cout<<i+1<<endl;
    }
};

template<class T>
void SeqList<T>::output(){
//将顺序表全部元素输出到屏幕上
    cout<<"顺序表当前元素最后位置为："<<last<<endl;
    for(int i=0;i<=last;i++){
        cout<<"#"<<i+1<<":"<<data[i]<<endl;
    }    
};

template<class T>
SeqList<T>::SeqList<T>::operator=(SeqList<T>& L){
//重载操作：顺序表整体赋值。若当前调用此操作的表对象为L1，代换形参L的表对象为L2，
//则使用方式为L1=L2。
    maxSize=L.Size();
    last=L.length()-1;
    T value;
    data = new T[maxSize];
    if(data==NULL)
        {cerr<<"存储分配失败！"<<endl;exit(1);}
    if(int i=1;i<last+1;i++){
        L.getData(i,value);
        data[i-1]=value;
    }
}