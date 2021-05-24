#include <iostream>
#include <queue>
#include <list>
#include <utility>
#include <memory>
#include <vector>

//Question: Write a program that takes as input a set of sorted sequences and computes the union of these sequences as a sorted sequence.
//
//Example:
//
//Input
//[ [3,5,7], [0,6], [0, 6, 28] ]
//
//Output:
// [0, 0, 3, 5, 6, 6, 7, 28]

// A Linked List Node
struct Node
{
    int data;
    std::shared_ptr<Node> next;

    Node(int data)
    {
        this->data = data;
        this->next = nullptr;
    }
};

// Comparison object to be used to order the min-heap
struct comparator
{
    bool operator()(const std::shared_ptr<Node> lhs, const std::shared_ptr<Node> rhs) const {
        return lhs->data > rhs->data;
    }
};

void printList(const std::list<int>& mylist);
std::list<int> mergeKLists(std::shared_ptr<Node> list[], int k);
std::vector<int> insert_all(std::list<int> mylist);

int main()
{

    const int k = 3;

    std::list<int> list1 = { 1, 5, 7 };
    std::list<int> list2 = { 2, 3, 6, 9 };
    std::list<int> list3 = { 4, 8, 10, 24 };

    // an array to store the head nodes of the linked lists
    std::shared_ptr<Node> list[k];

    list[0] = std::make_shared<Node>(Node(1));
    list[0]->next = std::make_shared<Node>(Node(5));
    list[0]->next->next = std::make_shared<Node>(Node(7));

    list[1] = std::make_shared<Node>(Node(2));
    list[1]->next = std::make_shared<Node>(Node(3));
    list[1]->next->next = std::make_shared<Node>(Node(6));
    list[1]->next->next->next = std::make_shared<Node>(Node(9));

    list[2] = std::make_shared<Node>(Node(4));
    list[2]->next = std::make_shared<Node>(Node(8));
    list[2]->next->next = std::make_shared<Node>(Node(10));
    list[2]->next->next->next = std::make_shared<Node>(Node(24));

    // Merge all lists into one
    std::list<int> output = mergeKLists(list, k);
    printList(output);

    return 0;
}

std::list<int> mergeKLists(std::shared_ptr<Node> list[], int k)
{
    std::list<int> result;

    // create an empty min-heap
    std::priority_queue <std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, comparator> pq;

    //push the first node of each list into the min-heap
    for (int i = 0; i < k; i++)
    {
        pq.push(list[i]);
    }

    while (!pq.empty())
    {
        std::shared_ptr<Node> top = pq.top();
        result.push_back(top->data);
        pq.pop();

        // take the next node from the "same" list and insert it into the min-heap
        if (top->next != nullptr)
            pq.push(top->next);

    }

    return result;
}

void printList(const std::list<int>& mylist)
{
    for (auto i : mylist)
    {
        std::cout << i << " -> ";
    }
    std::cout << std::endl;
}


std::vector<int> insert_all(std::list<int> mylist)
{
    // an array to store the head nodes of the linked lists
    std::shared_ptr<Node> vec_of_heads;

}