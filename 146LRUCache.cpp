/**
    See more: https://stackoverflow.com/questions/3578083/what-is-the-best-way-to-use-a-hashmap-in-c
    In C/C++, an ordered map internally uses red-black trees for O(logn) insert and access.
    But an unordered map uses hash table for amortized O(1) insert and access.
    
    We approach this problem by using an unordered map (hash table) and a priority queue (doubly linked list):
    get:    access the (k, (v, pointer to linked list node)) pair in hash table, if not exist, return -1
            if exist, remove the node from queue, enqueue, return v
    put:    access the pair in hash table, if exist, do nothing
            if not exist, if length of queue == capacity, dequeue, also delete that node from hash table, then enqueue and put
            
    Runtime: amortized O(1) for both operations 
**/

class LRUCache {
public:   
    LRUCache(int capacity) {
        length = 0;
        cap = capacity;
    }
    
    int get(int key) {
        std::unordered_map<int, node*>::iterator it = ht.find(key);
        if(it == ht.end()){ // If key does not exist, return -1
            return -1;
        }else{ // If key exists, return value, rearrange the priority
            node* n = ht[it->first];
            cout<<"key: "<< it->first<<" return: "<<n->val<<endl;
            rearrange(n);
            return n->val;
        }
    }
    
    void put(int key, int value) {
        std::unordered_map<int, node*>::iterator it = ht.find(key);
        if(it != ht.end()){ // If key already exists, reset the value, rearrange the priority
            ht[key]->val = value;
            rearrange(ht[key]);
            return;
        }else{ // If key does not exist, enqueue from head
            node* n = new node(); // Dynamically allocated list node for constant addressing on heap
            n->k = key; n->val = value;
            if(!length){ // If empty, the head is also tail
                head = n;
                tail = n;
            } else{
                n->next = head;
                head->prev = n;
                head = n;
            }
            ht[key] = n;
            cout<<"put: "<<key<<" with value: "<<(ht[key])->val<<endl;
            length++;
            if(length > cap){
                evict();
            }
        }
    }
private:
    struct node{
        int k;
        int val; 
        node* prev; 
        node* next; 
    };
  
    std::unordered_map<int, node*> ht;
    node* head; node* tail;
    int length, cap;

    void rearrange(node* n){
        if(n == head){return;}
        else if(n == tail){
            n->prev->next = 0; 
            tail = n->prev;
        } else{
            n->prev->next = n->next;
            n->next->prev = n->prev;
        }
        n->prev = 0;
        n->next = head;
        head->prev = n;
        head = n;
    }
    
    void evict(){
        cout<<"evict key "<<tail->k<<endl;
        int key = tail->k;
        if(length == 1){delete tail; tail = 0; head = 0;}
        else{
            node* removed = tail;
            removed->prev->next = 0;
            tail = removed->prev; 
            delete removed;
        }
        ht.erase(key);
        length--;
    }

};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */