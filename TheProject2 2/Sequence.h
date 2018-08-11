

#ifndef Sequence_h
#define Sequence_h

#include <iostream>
#include <string>

typedef std::string ItemType;

class Sequence
{
public:
    Sequence();
    ~Sequence(); /// destructor
    Sequence (const Sequence &other); //S // copy constructor
    Sequence& operator=(const Sequence& rhs);//assignment operator
    bool empty() const;
    int size() const;
    bool insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    void dump();
    
private:
    
    
    struct Node
    {
        ItemType m_data;
        Node* m_next;
        Node* m_prev;
        int m_pos; // keep track of position
    };
    
    int m_size;
    Node* m_head;
    
    
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);







#endif /* Sequence_h */
