#include "Node.h"

// Display item
void Node::display_item() const
{
	item->display_item();
}

// Set all data to null, default
Node::Node() : item(nullptr), left(nullptr), right(nullptr)
{
}

// Copy data
Node::Node(const std::shared_ptr<Product>& other) : item(other), left(nullptr), right(nullptr)
{
}

// Set right child
void Node::set_right(std::unique_ptr<Node>&& other) {
    right = std::move(other);
}

// Set left child
void Node::set_left(std::unique_ptr<Node>&& other) {
    left = std::move(other);
}

// Set item
void Node::set_item(const std::shared_ptr<Product>& other) {
    item = other;
}

// Return item
const std::shared_ptr<Product>& Node::get_item() const {
    return item;
}

// Return left child
std::unique_ptr<Node>& Node::get_left() {
    return left;
}

// Return right child
std::unique_ptr<Node>& Node::get_right() {
    return right;
}

