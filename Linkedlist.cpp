#include <iostream>
#include <memory>
#include <exception>
#include <forward_list>

namespace Aamir
{
    // exception classes
    class Empty_except : public std::exception
    {
        virtual char const *what() const noexcept override
        {
            return "Invalid operation! : Empty List";
        }
    };
    class Out_of_range : public std::exception
    {
        virtual char const *what() const noexcept override
        {
            return "Invalid operation! : Out of bounds";
        }
    };

    // Node Class
    template <typename T>
    class Node
    {
    public:
        T data;
        typedef std::shared_ptr<Node<T>> Nodeptr;
        Nodeptr next;
        Node() : next(nullptr), data() {}
        Node(T val) : next(nullptr), data(val) {}
        Node(T val, Nodeptr nxt) : data(val), next(nxt) {}
    };

    // Singly Linked List Class
    template <typename T>
    class List
    {
        typedef std::shared_ptr<Node<T>> Nodeptr;
        Nodeptr head;
        Nodeptr tail;
        std::size_t nodeSize;
        bool insert_pos_valid(size_t pos){
            return pos<=nodeSize;
        }
        bool search_pos_valid(size_t pos){
            return pos<nodeSize;
        }
        Nodeptr search(size_t pos){
            if(!search_pos_valid(pos)){
                throw Out_of_range();
            }
            Nodeptr temp=head;
            for(int i=0;i<pos;i++){
                temp=temp->next;
            }
            return temp;
        }

    public:
        List() : head(nullptr), tail(nullptr), nodeSize(0) {}
        List(std::initializer_list<T> L):List()
        {
            for(auto it=L.begin();it!=L.end();it++)
            {
                this->push_back(*it);
            }
        }
        bool empty()
        {
            return !(nodeSize);
        }
        void reverse()
        {
            Nodeptr prev, curr, next;
            prev = nullptr;
            curr = nullptr;
            next = nullptr;
            curr = head;
            while (curr != nullptr)
            {
                next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }
            head = prev;
        } 
        void display()
        {
            std::shared_ptr<Node<T>> temp = head;
            while (temp != nullptr)
            {
                std::cout << temp->data << " ";
                temp = temp->next;
            }
        }
        void push_front(T val)
        {
            std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(val);
            if (head == nullptr)
            {
                head = tail = newNode;
            }
            else
            {
                newNode->next = head;
                head = newNode;
            }
            nodeSize++;
        }
        void push_back(T val)
        {
            std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(val);
            if (head == nullptr)
            {
                head = tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
            nodeSize++;
        }
        T pop_front()
        {
            if (empty())
            {
                throw Empty_except();
            }
            T temp = head->data;
            head = head->next;
            if(head==nullptr){
                tail=head;
            }
            nodeSize--;
            return temp;
        }
        T pop_back()
        {

            if (empty())
            {
                throw Empty_except();
            }
            T tempval = tail->data;
            if (nodeSize == 1)
            {
                head = nullptr;
                tail=nullptr;
            }
            else if (nodeSize == 2)
            {
                head->next = nullptr;
                tail = head;
            }
            else
            {
                Nodeptr temp = head;
                for (int i = 0; i < nodeSize - 2; i++)
                {
                    temp = temp->next;
                }
                tail = temp;
                temp->next = nullptr;
            }

            nodeSize--;
            return tempval;
        }
        
        void insert(size_t pos, T val=T())
        {
            if (!(insert_pos_valid(pos)))
            {
                throw Out_of_range();
            }
            if (pos == 0)
            {
                this->push_front(val);
                return;
            }
            else
            {
                Nodeptr temp = this->search(pos-1);
                Nodeptr newNode(new Node<T>(val, temp->next));
                temp->next = newNode;
                if(pos==nodeSize){
                    tail=newNode;
                }
                nodeSize++;
            }
            
        }
        T erase(size_t pos){
            if(!search_pos_valid(pos)){
                throw Out_of_range();
            }
            else{
                
                if(pos==0){
                    return this->pop_front();
                }
                else if(pos==nodeSize-1){
                    return this->pop_back();
                }
                else{
                    Nodeptr temp=this->search(pos-1);
                    T tempval;
                    tempval=(temp->next)->data;
                    temp->next=(temp->next)->next;
                    nodeSize--;
                    return tempval;
                }
            }
        }
        T &at(size_t pos){
            return (this->search(pos))->data;
        }
        T &front(){
            if(empty()){
                throw Empty_except();
            }
            return head->data;
        }
        T &back(){
            if(empty()){
                throw Empty_except();
            }
            return tail->data;
        }
        size_t size(){
            return nodeSize;
        }
        void clear(){
            head=tail=nullptr;
            nodeSize=size_t();
        }
        T& operator[](size_t index){
            return (this->search(index))->data;
        }
    };
}
int main()
{

    Aamir::List<int> L1 = {1,2,3,4};
    try{
        
        std::cout<<L1[0];

        
    }
    catch(std::exception &e){
        std::cerr<<e.what();
    }
    
    ///sflksklfkdlsjdlkfjds
    return 0;
}
