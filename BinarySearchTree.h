#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "Stack.h"
#include "List.h"
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

struct Employee {
    int id;
    int age;
    string name;

    Employee(int id = -1, int age = -1, string name = "")
        : id{ id }, age{ age }, name{ name } { }
};

class BinarySearchTree
{

public:

    struct BinaryNode
    {
        Employee element;
        BinaryNode* left{};
        BinaryNode* right{};

        BinaryNode(const Employee& theElement, BinaryNode* lt, BinaryNode* rt)
            : element{ theElement }, left{ lt }, right{ rt } { }     

        BinaryNode(Employee&& theElement, BinaryNode* lt, BinaryNode* rt)
            : element{ std::move(theElement) }, left{ lt }, right{ rt } { }

        BinaryNode() {}
    };

    BinarySearchTree() : root{ nullptr }
    {
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree()
    {
        makeEmpty();
    }

    /**
     * Find the smallest item in the tree.
     * return default employee if empty
     */
    const Employee& findMin() const
    {
        if (isEmpty()) {
            return Employee();
        }
        return findMin(root)->element;
    }

    /**
     * Find the largest item in the tree.
     * return default employee if empty
     */
    const Employee& findMax() const
    {
        if (isEmpty()) {
            return Employee();
        }
        return findMax(root)->element;
    }

    /**
     * Prints employee info if id found in tree
     */
    bool find(const int id) const
    {
        return find(id, root);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const
    {
        return (root == nullptr);
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty()
    {
        if (root != nullptr) {
            makeEmpty(root);
        }
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Employee& x)
    {
        if (!find(x.id, root))
        {
            insert(x, root);
        }
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const int id)
    {
        if (find(id, root))
        {
            remove(id, root);
        }
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void report() const
    {
        Stack<BinaryNode*> tree;
        BinaryNode* temp = root;

        while (!tree.isEmpty() || temp != nullptr)
        {
            if (temp != nullptr)
            {
                tree.push(temp);
                temp = temp->left;
            }
            else
            {
                temp = tree.top();
                tree.pop();
                if (temp != nullptr)
                {
                    cout << endl << "Employee Name: " << temp->element.name << ", ID: " << temp->element.id << ", Age: " << temp->element.age << endl;
                    temp = temp->right;
                }
            }
        }
    }

private:

    BinaryNode* root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Employee& x, BinaryNode*& t)
    {
        BinaryNode* item = new BinaryNode(x, nullptr, nullptr);
        BinaryNode* tree = t;
        int loop = 1;

        if (t != nullptr) {
            do
            {
                if (x.id < (tree->element.id))
                {
                    if (tree->left == nullptr)
                    {
                        tree->left = item;
                        loop = 0;
                    }
                    tree = tree->left;
                }
                else
                {
                    if (tree->right == nullptr)
                    {
                        tree->right = item;
                        loop = 0;
                    }
                    tree = tree->right;
                }
            } while (loop == 1);
        }
        else {
            t = item;
        }
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove(const int id, BinaryNode*& t)
    {
        if (t == nullptr)
            return;   
        if (id < t->element.id)
            remove(id, t->left);
        else if (t->element.id < id)
            remove(id, t->right);
        else if (t->left != nullptr && t->right != nullptr) 
        {
            t->element = findMin(t->right)->element;
            remove(t->element.id, t->right);
            if (t->left != nullptr) {
                BinaryNode* temp = root->left;
                return;
            }
            else {
                BinaryNode* temp = root->right;
            }
        }
        else
        {
            return;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode* findMin(BinaryNode* t) const
    {
        if (isEmpty())
        {
            return nullptr;
        }

        BinaryNode* temp = t;

        while (temp->left != nullptr)
        {
            temp = temp->left;
        }
        return temp;
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode* findMax(BinaryNode* t) const
    {
        if (isEmpty())
        {
            return nullptr;
        }

        BinaryNode* temp = t;

        while (temp->right != nullptr)
        {
            temp = temp->right;
        }
        return temp;
    }


    /**
     * id is item to search for.
     * t is the node that roots the subtree.
     */
    bool find(const int id, BinaryNode* t) const
    {
        if (t == nullptr) {
            return false;
        }
        if (t->element.id == id)
        {
            cout << "Employee was found\n" << endl;
            return true;
        }
        else if (id < t->element.id)
        {
            if (t->left == nullptr)
            {
                cout << "Employee not found.\n" << endl;
                return false;
            }
            else
            {
                return find(id, t->left);
            }
        }
        else if (id > t->element.id)
        {
            if (t->right == nullptr)
            {
                cout << "Employee not found.\n" << endl;
                return false;
            }
            else
            {
                return find(id, t->right);
            }
        }
    }

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(BinaryNode*& t)
    {
        while (!isEmpty())
        {
            remove(root->element.id, root);
        }
    }
};

#endif
