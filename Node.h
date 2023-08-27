#ifndef NODE_H
#define NODE_H

#include <memory>
#include "Product.h"

class Node
{
public:
    Node();
    Node(const std::shared_ptr<Product>& other);

    void set_right(std::unique_ptr<Node>&& other); // Set right child
    void set_left(std::unique_ptr<Node>&& other); // Set left child
    void set_item(const std::shared_ptr<Product>& other); // Set item data

    const std::shared_ptr<Product>& get_item() const; // Return private item data
    void display_item() const; // Display item
    std::unique_ptr<Node>& get_left(); // Return left child
    std::unique_ptr<Node>& get_right(); // Return right child

private:
    std::shared_ptr<Product> item; // Stores product
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
};

#endif

