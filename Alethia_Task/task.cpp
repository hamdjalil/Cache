#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

//Node is the vector elements existing inside the cache

class Node
{

public:
    //int key;
    vector<int> value;
    Node *prev, *next;
    Node()
    {
    }
    Node(vector<int> v)
    {

        value = v;
        prev = NULL;
        next = NULL;
    }
};

//double linked list as the cache data structure

class DoublyLinkedList
{
    Node *front, *rear;
    vector<Node *> buckets;

public:
    DoublyLinkedList()
    {
        front = NULL;
        rear = NULL;
        vector<int> n;
        Node *add = new Node(n);
        buckets.push_back(add);
    }

    //extend the cache

    Node *addHead(int key)
    {
        vector<int> v;
        v.push_back(key);
        Node *page = new Node(v);
        if (!front && !rear) //if list is empty
        {
            front = rear = page;
        }
        else
        {
            page->next = front;
            front->prev = page;
            front = page;
        }
        return page;
    }
    //remove element from cache
    void removeKey(Node *page)
    {

        if (front == NULL || page == NULL)
            return;

        if (front == page)
            front = page->next;

        if (page->next != NULL)
            page->next->prev = page->prev;

        if (page->prev != NULL)
            page->prev->next = page->next;

        delete page;
    }
    //get size of cache
    void findSize()
    {
        int res = 0;
        Node *temp = front;

        while (temp != NULL)
        {
            res++;
            temp = temp->next;
        }
        cout << "size is " << res << endl;
        return;
    }
    //print cache
    void printList()
    {

        Node *temp = front;

        while (temp != NULL)
        {
            // cout << temp->key << endl;
            vector<int> ans;
            ans = temp->value;

            for (int i = 0; i < ans.size(); ++i)
            {
                std::cout << ans[i];
            }
            cout << " -> ";

            temp = temp->next;
        }
        cout << endl;

        return;
    }
};

//cache class

class Cache
{

    int size;
    DoublyLinkedList *dList;

    Node **arr; //array to hold node address at indexes
    int arr_cap;
    int arr_size;
    Node **arr_index; //array to hold node address with data value as index
    int arr_index_cap;
    int arr_index_size;

public:
    Cache()
    {

        size = 0;
        dList = new DoublyLinkedList();

        arr = new Node *[1];
        arr_cap = 10;
        arr_size = 0;
        arr_index = new Node *[1];
        arr_index_cap = 10;
        arr_index_size = 0;
    }

    //update arrays when new element is added

    void append_arr(int key, Node *page, int size)
    {
        //resize arr
        if (size >= arr_cap)
        {

            arr_cap = 2 * arr_cap;
            Node **new_arr = new Node *[arr_cap];

            for (int i = 0; i < size; ++i)
            {

                new_arr[i] = arr[i];
            }

            delete[] arr;

            arr = new_arr;
        }
        //resize arr_index
        if (key > arr_index_size)
        {

            arr_index_cap = key + 1;
            Node **new_arr_index = new Node *[arr_index_cap];

            for (int i = 0; i < arr_index_size; ++i)
            {
                new_arr_index[i] = arr_index[i];
            }

            //delete[] arr_index; // delete old arr

            arr_index = new_arr_index;
        }

        //arr will contain node address at index = size

        arr[size] = page;
        arr_size++;
        //arr_index will contain node address at index = value of data

        arr_index[key] = page;
        arr_index_size = key + 1;
    }

    //update array when getElement removes element from cache

    void removeIndex(int i)
    {
        Node **new_array = new Node *[arr_cap];
        std::copy(arr, arr + i, new_array);
        std::copy(arr + i + 1, arr + size, new_array + i);
        delete[] arr;
        arr = new_array;
        --arr_size;
    }

    //get element at key index

    vector<int> getElement(int key)
    {
        vector<int> v;
        vector<int> old_vec;
        //return  if index is greater than actual cache
        if (key >= size)
        {
            return v;
        }

        //get vector at index

        old_vec = arr[key]->value;

        //remove element from cache

        dList->removeKey(arr[key]);
        size--;
        //update address arrays
        removeIndex(key);

        arr_index[old_vec[0]] = 0;
        //arr[key] = NULL;

        return old_vec;
    }

    //insert element in chache

    void insertElement(int key)
    {
        //if data already exists, return to avoid duplicates

        if (arr_index[key] != 0)
        {

            return;
        }

        vector<int> block;

        //cout << arr_index[key]->value << endl;

        //add element to cache linked list

        Node *page = dList->addHead(key);

        //update arrays

        append_arr(key, page, size);
        size++;
    }

    //get range based on start, end indexes
    vector<vector<int> > getRange(int start, int end)
    {

        vector<vector<int> > v;
        vector<int> old_vec;
        for (int i = start; i < end; ++i)
        {
            if (arr[i] != NULL)
            {
                old_vec = arr[i]->value;

                v.push_back(old_vec);
            }
        }
        return v;
    }

    void getSize()
    {

        dList->findSize();
        return;
    }
    //print cache
    void getList()
    {

        dList->printList();
        return;
    }
    //destructor

    ~Cache()
    {

        delete[] arr;
        delete[] arr_index;
        delete dList;
    }
};

int main()
{
    Cache cache;
    //add elements
    cache.insertElement(12);
    cache.insertElement(3);
    //check for duplicates
    cache.insertElement(12);
    cache.insertElement(1);
    cache.insertElement(8);
    cache.insertElement(7);
    cache.getList();
    cache.getSize();
    //remove elements via index
    cache.getElement(2);
    cout << "after removing index " << endl;
    //cache.insertElement(1);

    cache.getList();
    cache.getSize();
    //get range via index
    vector<vector<int> > range;
    range = cache.getRange(0, 4);
    cout << "elements in range are " << endl;

    for (int i = 0; i < range.size(); i++)
    {
        for (
            auto it = range[i].begin();
            it != range[i].end(); it++)

            cout << *it << " ";
        cout << endl;
    }

    return 0;
}
