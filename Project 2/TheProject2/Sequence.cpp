

#include "Sequence.h"


Sequence::Sequence()
{
    
    m_head = nullptr;
    m_size = 0;
    
};

bool Sequence::empty() const
{
    if (m_head == nullptr)
        return true;
    return false;
}

int Sequence::size() const
{
    
    return m_size;
}




bool Sequence::insert(int pos, const ItemType& value)
{
    if (pos <0 || pos > size()) //if position is negative or doesn't exist
        return false;
    if (size()==0 || pos ==0) //empty list/front of list.
    {
        Node* newGuy = new Node; // pointer to new Node
        newGuy->m_pos=0;
        newGuy->m_data = value;
        newGuy->m_prev = nullptr;
        newGuy->m_next = m_head;
        
        Node* p = m_head;
        if (p !=nullptr) // run through list to increase position of everything after
        {
            
            while (p->m_next!= nullptr) //other cases
            {
                p->m_pos++;
                p = p->m_next;
            }
            if(p->m_next==nullptr) //this accounts for the last item in the list
                p->m_pos++;
        }
        
        
        m_head = newGuy;
        // head pointer points to new thing
        m_size++; //increase size
        
    }
    else if (pos == size() && size() != 0) //end of list
    {
        Node* p = m_head;
        while(p->m_next != nullptr)
        {
            if (p->m_pos==pos)
                break;
            p= p->m_next;
        }
        /*if (p->m_pos != pos) //if adding on to end of list
         {*/
        Node* newGuy = new Node;
        newGuy->m_data = value;
        newGuy->m_prev = p;
        newGuy->m_next = nullptr; //null on account the end shouldn't point to anything
        newGuy->m_pos = pos;
        p->m_next= newGuy;
        m_size++;
        return true;
        /* }*/
    }
    
    else //middle of list
    {
        Node* p = m_head;
        while(p->m_next != nullptr)
        {
            if (p->m_next->m_pos==pos)
                break;
            p= p->m_next; //find position before insertion
        }
        
        Node* temp1 = p; //position before insertion
        Node* temp2 = p->m_next; //position after insertion
        Node* newGuy = new Node;
        temp1->m_next = newGuy; //set previous node's next pointer to new node
        newGuy->m_prev = temp1; //set new node's previous pointer to the previous nosde
        newGuy->m_next=temp2; //set new nodes' enxt pointer to next node
        temp2->m_prev = newGuy;// set next node's previous pointer to new node
        newGuy->m_data = value;
        newGuy->m_pos = pos;
        
        
        while (newGuy->m_next!= nullptr) // increment positions
        {
            newGuy->m_next->m_pos++;
            newGuy = newGuy->m_next;
        }
        m_size++;
        
    }
    return true;
    
};


int Sequence:: insert(const ItemType& value)
{
    Node* p = m_head;
    
    if (p->m_data!= value|| p->m_data > value) //repeatedly run through code to find
    {
        while(p->m_next != nullptr) //run through code to find where node has value
        {
            if (p->m_data >= value)
                break;
            p= p->m_next;
        }
    }
    if (p->m_next==nullptr) //account for if last node has value (prev code does not account)
        insert(size(), value); //insert
    else
        insert(p->m_pos, value);
    
    return p->m_pos;
}

bool Sequence::erase(int pos)
{
    if (pos<0|| pos >= size()) //if invalid position
        return false;
    
    if (pos ==0 && size()==1) //one element list
    {
        Node *p = m_head;
        m_head = nullptr;
        delete p;
        m_size--; //no need to modify m_pos in this case...
    }
    
    else if (pos ==0 && size()!= 1) //front of list
    {
        Node *p = m_head;
        p->m_next->m_prev = nullptr; //new head of list's prev pointer must be null
        m_head = p-> m_next;
        
        Node *posMod = p;
        while(posMod->m_next!= nullptr)//modify position
        {
            posMod->m_next->m_pos--;
            posMod = posMod->m_next;
        }
        delete p;
        m_size--;
    }
    
    else if (pos != size()-1) //middle of list
    {
        Node *p = m_head;
        while(p->m_next!= nullptr)
        {
            if (p->m_next->m_pos == pos)
                break;
            p = p->m_next; //find position
        }
        
        Node*temp1 =p; //position before deletion
        Node*temp2 = p->m_next->m_next;//position after deletion
        Node* posMod = temp1;
        temp1->m_next = temp2; //next to skip over to-be-deleted node
        temp2->m_prev =temp1;//prev to skip over to-be-deleted node
        delete p->m_next; //delete the destined-to-be-deleted node
        while(posMod->m_next!= nullptr) //modify private position of each
        {
            posMod->m_next->m_pos--;
            posMod = posMod->m_next;
        }
        
        m_size--;
        
    }
    else //the end has come
    {
        Node *p = m_head;
        while(p->m_next!= nullptr) //this should end up pointing to the last node
            p = p->m_next;
        Node*temp = p->m_prev;
        temp->m_next = nullptr;
        delete p;
        m_size--; //finished - no need to modify m_pos size
    }
    
    return true;
}


int Sequence::remove(const ItemType& value)
{
    
    int removedItem = 0; //counter for removed items
    Node* p = m_head;
    while (p->m_next!= nullptr)
    {
        Node* temp1 = p; //position before deletion
        Node*temp2 = p->m_next;//position of deletion
        if (p->m_data== value)
        {
            erase(temp1->m_pos); //delete the node
            removedItem++;
        }
        p = temp2;
        
    }
    if (p->m_next==nullptr) //account for if last node has value
    {
        if (p->m_data == value)
            erase(p->m_pos);
        removedItem++;
    }
    return removedItem;
    
}


bool Sequence:: get(int pos, ItemType& value) const
{
    if (pos<0 || pos >= size())
        return false;
    else
    {
        Node* p = m_head;
        if (p->m_pos == pos)
            value = p->m_data;
        else
        {
            while(p->m_next!= nullptr)
            {
                if (p->m_pos == pos)
                    break;
                p = p->m_next;
            }
            value = p->m_data;
        }
        
    }
    return true;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos<0 || pos >= size())
        return false;
    else
    {
        Node* p = m_head;
        if (p->m_pos == pos) //if first node has proper position
            p->m_data = value;
        else
        {
            while(p->m_next!= nullptr) 
            {
                if (p->m_next->m_pos == pos)
                { p->m_next->m_data = value;
                    break;
                }
                p = p->m_next;
            }
            if (p->m_next==nullptr) //check if last node has position
                p->m_data = value;
        }
        
    }
    return true;
    
}

int Sequence::find(const ItemType& value) const
{
    int p = -1;
    Node* q = m_head;
    if (q->m_data == value) //if first node has value
        p = q->m_pos;
    else
    {
        while(q->m_next!= nullptr) //run through list to find if other value
        {
            if (q->m_next->m_data == value)
            {
                p = q->m_next->m_pos;
                break;
            }
            q = q->m_next;
        }
    }
    
    return p;
}




void Sequence::swap(Sequence& other)
{
    
    if (m_head != other.m_head)
    {
        Node* temp = other.m_head; //saving pointer
        other.m_head = this->m_head;
        this->m_head = temp;
        
        int tmp = other.m_size;
        other.m_size = m_size;
        m_size = tmp;
        
        
    }
    
    
    
}


Sequence::~Sequence() //destructor
{
    Node*p = m_head;
    if (p!= nullptr)
    {
        while (p->m_next!= nullptr)
        {
            Node*temp2= p->m_next;
            delete p;
            p = temp2;
        }
        delete p;
        
    }
    
}

Sequence& Sequence::operator =(const Sequence& rhs) //assignment

{
    if (this != &rhs)
    {
        Sequence temp(rhs);
        swap(temp);
    }
    return *this;
    
}

Sequence::Sequence(const Sequence &other) //copy constructor
{
    m_size = other.m_size;
    Node* p = other.m_head;
    for (int i =0; i< other.m_size; i++)
    {
        this->insert(i, p->m_data);
        p = p->m_next;
    }
    
}



void Sequence::dump()
{
    Node*p = m_head;
    while (p != nullptr)
    {
        std::cout << p->m_data << " " << p->m_pos << std::endl ;
        p = p->m_next;
    }
    
}





int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    return -1;
}
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
}
