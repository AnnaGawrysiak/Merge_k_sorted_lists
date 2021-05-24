#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <utility>
#include <iterator>

typedef std::pair<std::list<int>::iterator, std::list<int>::iterator> pi;

/*
Question: Write a program that takes as input a set of sorted sequences and computes the union of these sequences as a sorted sequence.

Example:

Input
[ [3,5,7], [0,6], [0, 6, 28] ]

Output:
 [0, 0, 3, 5, 6, 6, 7, 28]
*/

struct comparator
{
    bool operator()(pi a, pi b)
    {
        return *a.first > *b.first;
    }
};


void printList(const std::list<int>& mylist);

std::list <int> mergeKLists(const std::vector<pi>& heads_and_tails);

void add_list(std::vector<pi>& heads_and_tails, std::list<int> list);

int main()
{
    int k = 3;

    std::list<int> list1 = { 1, 5, 7 };
    std::list<int> list2 = { 2, 3, 6, 9 };
    std::list<int> list3 = { 4, 8, 10 };

    // a vector od pairs to store the head and tail iterators of the linked lists

    std::vector<pi> heads_and_tails;
    add_list(heads_and_tails, list1);
    add_list(heads_and_tails, list2);
    add_list(heads_and_tails, list3);
    heads_and_tails.reserve(k);

    printList(mergeKLists(heads_and_tails));

    return 0;
}

std::list <int> mergeKLists(const std::vector<pi>& heads_and_tails)
{
    std::list<int> result;

    // create an empty min-heap
    std::priority_queue <pi, std::vector<pi>, comparator> pq;

    // push the first node of each list into the min-heap
    for (unsigned int i = 0; i < heads_and_tails.size(); i++)
    {
        pq.push(heads_and_tails.at(i)); 
    }

    while (!pq.empty())
    {
        // extract the min element from the heap
        pi top = pq.top();
        result.push_back(*top.first);
        pq.pop();

        // take the next node from the "same" list and insert it into the min-heap (if exists)
        if (std::next(top.first, 1) != top.second)
        {
            pq.push(std::make_pair(std::next(top.first, 1), top.second));
        }

    }

    return result;
}

void printList(const std::list<int>& mylist)
{
    for (auto const& i : mylist) {
        std::cout << i << std::endl;
    }

}

void add_list(std::vector<pi>& heads_and_tails, std::list<int> mylist)
{
    heads_and_tails.push_back(std::make_pair(mylist.begin(), mylist.end()));
}