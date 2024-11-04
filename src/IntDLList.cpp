#include "IntDLList.hpp"
#include <iostream>

bool Iterator::operator!=(const Iterator& other)const
{
  return this->_current!=other._current;
}
int Iterator::operator*()const
{
  return this->_current->GetData();
}
const Iterator& Iterator::operator++()
{
  if(_current)
  {
    this->_current=this->_current->GetNext();
  }
  return *this;
}

bool ReverseIterator::operator!=(const ReverseIterator& other)const
{
  return this->_current!=other._current;
}
int ReverseIterator::operator*()const
{
  return this->_current->GetData();
}
const ReverseIterator& ReverseIterator::operator++()
{
  if(_current)
  {
    this->_current=this->_current->GetPrev();
  }
  return *this;
}


IntDLList::IntDLList()
{
  this->_header=this->_tail=nullptr;
  this->_Length=0;
}

IntDLList::~IntDLList()
{
  this->clear();
}

bool IntDLList::IsEmpty()
{
  return this->_Length==0;
}

int IntDLList::GetLength()
{
  return this->_Length;
}
IntDLLNode* IntDLList::Head()
{
  return this->_header;
}
IntDLLNode* IntDLList::Tail()
{
  return this->_tail;
}
void IntDLList::Push(int data)
{
  if(this->_Length==0)
  {
    this->_header=this->_tail=new IntDLLNode(data);
    this->_Length++;
    return;
  }
    this->_header->SetPrev(new IntDLLNode(data,this->_header->GetPrev(),this->_header));
    this->_header=this->_header->GetPrev();
    this->_Length++;
}
void IntDLList::Insert(int data,IntDLLNode* pos)
{
  if(pos==nullptr)
  {
    std::cout<<"Error: Invalid Position"<<std::endl;
    return;
  }
  if(pos==this->_header)
  {
    this->Push(data);
    return;
  }
  IntDLLNode* tmp;
  for(tmp=this->_header;tmp!=nullptr && tmp!=pos;tmp=tmp->GetNext());
  if(tmp!=nullptr)
  {
    tmp->SetPrev(new IntDLLNode(data,tmp->GetPrev(),tmp));
    tmp->GetPrev()->GetPrev()->SetNext(tmp->GetPrev());
    this->_Length++;
  }
}
void IntDLList::Insert(int data,int index)
{
  //判断索引是否合法,index<0
  if(index>(this->_Length-1) || index<0)
  {
    std::cout<<"Error:Invalid index,Insert faild"<<std::endl;
    return ;
  }
  //处理index==0
  if(index==0)
  {
    this->Push(data);
    return;
  }
  //index>0
  IntDLLNode *tmp=this->_header;
  for(int count=0;count<index;++count)
  {
    if(tmp==nullptr)
    {
      std::cout<< "Error:Reached end of list unexpectedly"<<std::endl;
      return;
    }
    tmp=tmp->GetNext();
  }
  tmp->SetPrev(new IntDLLNode(data,tmp->GetPrev(),tmp));
  tmp->GetPrev()->GetPrev()->SetNext(tmp->GetPrev());
  this->_Length++;
  this->_Length++;
}
void IntDLList::Append(int data)
{
  if(this->_Length==0)
  {
    this->_header=this->_tail=new IntDLLNode(data);
    this->_Length++;
    return;
  }
  this->_tail->SetNext(new IntDLLNode(data,this->_tail,this->_tail->GetNext()));
  this->_tail=this->_tail->GetNext();
  this->_Length++;
}
int* IntDLList::Shift()
{
  if(this->_Length<=0)
  {
    std::cout<<"Error : list is Empty!!";
    return nullptr;
  }
  int* value_ptr{new int(this->_header->GetData())};
  if(this->_header==this->_tail)
  {
    delete this->_header;
    this->_header=this->_tail=nullptr;
    this->_Length--;
    return value_ptr;
  }
  IntDLLNode* tmp{this->_header};
  this->_header=this->_header->GetNext();
  this->_header->SetPrev(tmp->GetPrev());
  delete tmp;
  this->_Length--;
  return value_ptr;
}
int* IntDLList::Remove(IntDLLNode* pos)
{
  if (pos == nullptr) {
      std::cout << "Error: Invalid pos" << std::endl;
      return nullptr;
  }
  
  if (this->_Length <= 0) {
      std::cout << "Error: list is Empty!!" << std::endl;
      return nullptr;
  }

  int* value_ptr = new int(pos->GetData());
  
  // 处理单节点情况
  if (this->_Length == 1) {
      if (pos == this->_header) {
          delete pos;
          this->_header = this->_tail = nullptr;
          this->_Length--;
          return value_ptr;
      }
      delete value_ptr; // 清理已分配的内存
      return nullptr;
  }
  // 查找要删除的节点的前一个节点
  IntDLLNode* tmp = this->_header;
  if (pos == this->_header)
  { // 处理头节点
    this->_header = pos->GetNext();
    this->_header->SetPrev(pos->GetPrev());
  } 
  else 
  {
    for(;tmp != nullptr && tmp!= pos;tmp = tmp->GetNext());
    if (tmp == nullptr)
    { // 如果没有找到 pos
          delete value_ptr;
          return nullptr;
    }
    pos->GetPrev()->SetNext(pos->GetNext());
    pos->GetNext()->SetPrev(pos->GetPrev());
    // 如果是尾节点，更新尾指针
    if (pos == this->_tail) {
        this->_tail = pos->GetPrev();
    }
  }
  delete pos; // 删除节点
  this->_Length--; // 减少长度
  return value_ptr;
}
int* IntDLList::Remove(int index)
{
  if (this->_Length <= 0)
  {
      std::cout << "错误：列表为空！" << std::endl;
      return nullptr;
  }

  if (index < 0 || index >= this->_Length)
  {
      std::cout << "错误：索引超出范围！" << std::endl;
      return nullptr;
  }

  IntDLLNode* current = this->_header;

  // 遍历到指定索引
  for (int i = 0; i < index; ++i)
  {
      current = current->GetNext();
  }

  int* value_ptr = new int(current->GetData()); // 存储要删除节点的数据

  if (current->GetPrev() == nullptr) // 如果删除的是头节点
  {
      this->_header = current->GetNext();
      this->_header->SetPrev(current->GetPrev());
  }
  else // 删除非头节点
  {
      current->GetPrev()->SetNext(current->GetNext());
      current->GetNext()->SetPrev(current->GetPrev());
  }

  if (current == this->_tail) // 如果删除的是尾节点
  {
      this->_tail = current->GetPrev();
  }

  delete current; // 删除节点
  this->_Length--; // 减少长度
  return value_ptr; // 返回删除的值
}
int* IntDLList::Pop()
{
  if (this->_Length <= 0) {
      std::cout << "Error: list is Empty!!" << std::endl;
      return nullptr;
  }
  int* value_ptr=new int(this->_tail->GetData());
  if(this->_Length==1)
  {
    delete this->_tail;
    this->_header=this->_tail=nullptr;
    this->_Length--;
    return value_ptr;
  }
  IntDLLNode* tmp=this->_tail;
  this->_tail=tmp->GetPrev();
  this->_tail->SetNext(tmp->GetNext());
  delete tmp;
  this->_Length--;
  return value_ptr;
}
bool IntDLList::clear()
{ 
  // 检查链表是否为空
  if (this->IsEmpty()) {
      return false; // 如果链表已经为空，返回false
  }

  IntDLLNode* current = this->_header; // 从头节点开始
  IntDLLNode* nextNode = nullptr;

  // 遍历链表并删除每个节点
  while (current != nullptr)
  {
    // 输出当前节点的数据
    std::cout << "Deleting node with data: " << current->GetData() << std::endl;
    nextNode = current->GetNext(); // 保存下一个节点
    if (nextNode != nullptr) {
        nextNode->SetPrev(current->GetPrev());
    }
    delete current; // 删除当前节点
    current = nextNode; // 移动到下一个节点
  }

  // 清空链表的头尾指针和长度
  _header = nullptr;
  _tail = nullptr;
  _Length = 0; // 更新链表长度
  return true; // 返回true表示清空成功
}
bool IntDLList::Inlist(const IntDLLNode *pos)
{
  if(pos==nullptr)
  {
    return false;
  }
  for(IntDLLNode* tmp=this->_header;tmp!=nullptr;tmp=tmp->GetNext())
  {
    if(tmp==pos)
    {
      return true;
    }
  }
  return false;
}
bool IntDLList::Inlist(const int target)
{
  for(auto i:*this)
  {
    if(i==target)
    {
      return true;
    }
  }
  return false;
}
IntDLLNode* IntDLList::Find(int target)const
{
  if(this->_Length==0)
  {
    std::cout<<"Error: List is Empty!!"<<std::endl;
    return nullptr;
  }
  IntDLLNode* tmp=this->_header;
  for(;tmp!=nullptr && tmp->GetData()!= target;tmp=tmp->GetNext());
  if(tmp==nullptr)
  {
    std::cout<<"Error: target not in list!"<<std::endl;
    return nullptr;
  }
  return tmp;
}
void IntDLList::Print()const
{
  for(auto i:*this)
  {
    std::cout << i << " "; // 打印当前节点的数据
  }
  std::cout << std::endl; // 打印换行
}
void IntDLList::ReversePrint()const
{ 
  for (auto i = rbegin(); i != rend(); ++i) 
  {
    std::cout << *i << " "; // 打印当前节点的数据
  }
  std::cout << std::endl; // 打印换行
}

Iterator IntDLList::begin()const
{
  return Iterator(this->_header);
}
Iterator IntDLList::end()const
{
   return Iterator(nullptr);
}
//反向遍历支持
ReverseIterator IntDLList::rbegin()const
{
  return ReverseIterator(this->_tail);
}
ReverseIterator IntDLList::rend()const
{
   return ReverseIterator(nullptr);
}
