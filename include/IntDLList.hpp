#ifndef  __INTDLLIST_HPP_
#define __INTDLLIST_HPP_

class IntDLLNode
{
  public:
    IntDLLNode():_item(0),_prev(nullptr),_next(nullptr){};
    IntDLLNode(int el,IntDLLNode* Prevptr=nullptr,IntDLLNode* Nextptr=nullptr):_item(el),_prev(Prevptr),_next(Nextptr){};
    void SetData(int el){_item=el;};
    void SetNext(IntDLLNode* Nextptr){_next=Nextptr;};
    void SetPrev(IntDLLNode* Prevptr){_prev=Prevptr;};
    int GetData()const{return this->_item;};
    IntDLLNode* GetNext()const{return this->_next;};
    IntDLLNode* GetPrev()const{return this->_prev;};
  private:
    int _item;
    IntDLLNode *_prev;
    IntDLLNode *_next;
};

class Iterator
{
  public:
    Iterator(IntDLLNode* ptr):_current(ptr){}
    bool operator!=(const Iterator& other )const;
    int operator*()const;
    const Iterator& operator++();
  private:
    IntDLLNode *_current;
};

class ReverseIterator
{
  public:
    ReverseIterator(IntDLLNode* ptr):_current(ptr){}
    bool operator!=(const ReverseIterator& other )const;
    int operator*()const;
    const ReverseIterator& operator++();
  private:
    IntDLLNode *_current;
};

class IntDLList
{
  public:
    IntDLList();
    ~IntDLList();
    bool IsEmpty(); //判空
    int GetLength(); //获取链表长度
    IntDLLNode* Head(); //返回头指针
    IntDLLNode* Tail(); //返回尾指针
    void Push(int data);
    void Insert(int data,IntDLLNode* pos);
    void Insert(int data,int index);
    void Append(int data);
    int* Shift();
    int* Remove(IntDLLNode* pos);
    int* Remove(int index);
    int* Pop();
    bool clear();   //清空链表
    bool Inlist(const IntDLLNode *pos); //判断节点是否在链表中
    bool Inlist(const int target);  //判断数据所在节点是否在链表中
    IntDLLNode* Find(int target)const;
    void Print()const;  //遍历打印 
    void ReversePrint()const;  //遍历打印 

    Iterator begin()const;
    Iterator end()const;
    ReverseIterator rbegin()const;
    ReverseIterator rend()const;
    class ReverseAdapter 
    {
    public:
      IntDLList& list;
      ReverseAdapter(IntDLList& lst) : list(lst) {}
      ReverseIterator begin() { return list.rbegin();}
      ReverseIterator end() { return list.rend();}
    };
    // 方法以便调用适配器
    ReverseAdapter reverse_adapter() 
    {
      return ReverseAdapter(*this);
    }
  private:
    int _Length;
    IntDLLNode *_header,*_tail;
};

#endif // ! __INTDLLIST_HPP_
