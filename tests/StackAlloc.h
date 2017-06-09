
#ifndef STACK_ALLOC_H
#define STACK_ALLOC_H

#include <memory>

template <typename T>
struct StackNode_
{
  T data;
  StackNode_* prev;
};

/** T is the object to store in the stack, Alloc is the allocator to use */
template <class T, class Alloc = std::allocator<T> >
class StackAlloc
{
  public:
    typedef StackNode_<T> Node;
    typedef typename Alloc::template rebind<Node>::other allocator;

    /** Default constructor */
    StackAlloc() {head_ = 0; }
    /** Default destructor */
    ~StackAlloc() { clear(); }

    /** Returns true if the stack is empty */
    bool empty() {return (head_ == 0);}

    /** Deallocate all elements and empty the stack */
    void clear() {
      Node* curr = head_;
      while (curr != 0)
      {
        Node* tmp = curr->prev;
        allocator_.destroy(curr);
        allocator_.deallocate(curr, 1);
        curr = tmp;
      }
      head_ = 0;
    }

    /** Put an element on the top of the stack */
    void push(T element) {
      Node* newNode = allocator_.allocate(1);
      allocator_.construct(newNode, Node());
      newNode->data = element;
      newNode->prev = head_;
      head_ = newNode;
    }

    /** Remove and return the topmost element on the stack */
    T pop() {
      T result = head_->data;
      Node* tmp = head_->prev;
      allocator_.destroy(head_);
      allocator_.deallocate(head_, 1);
      head_ = tmp;
      return result;
    }

    /** Return the topmost element */
    T top() { return (head_->data); }

  private:
    allocator allocator_;
    Node* head_;
};

#endif // STACK_ALLOC_H
