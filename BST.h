#ifndef BST_H
#define BST_H

#include "Node.h"
#include <unistd.h>

class BST
{
public:
    BST() : root(nullptr) {}
    BST(const BST& other); // Deep copy of the whole bst
		
	bool load(std::string filename ); // Load inventory from external file	
    int add(std::shared_ptr<Product>& item); // Add a node to the bst
    int display_all() const; // Display all nodes
	float find(const std::string& name, bool display) const; // Find a node
	float return_item(const std::string& name, int days_used) const; // Return an item, helper

	int find_height() const; // Return height of the tree
	int count_nodes() const; // Return count of nodes in the tree
	bool remove_data(const std::string& data); // Remove a node from bst
	void remove_all(); // Remove all nodes in bst
	std::string title(const std::string& name) const;

private:
	std::string title(const std::unique_ptr<Node>& node, const std::string& name) const;
	std::unique_ptr<Node>& minValueNode(std::unique_ptr<Node>& node); // Return node with min value
	bool remove_data(std::unique_ptr<Node>& root, const std::string& data); // Remove a node
	int find_height(const std::unique_ptr<Node>& node) const; // Return height
	int count_nodes(const std::unique_ptr<Node>& node) const; // Return #of nodes
	std::unique_ptr<Node> copy_nodes(const std::unique_ptr<Node>& source); // Copy root with its children

	float find(const std::unique_ptr<Node>& node, const std::string& name, bool display) const; // Return price of the node if found, else return 0
	float return_item(const std::unique_ptr<Node> & node, const std::string& name, int days_used) const; // Return an item
    int display_all(const std::unique_ptr<Node>& root) const; // Display all nodes
    int add(std::unique_ptr<Node>& root, std::shared_ptr<Product>& item); // Add a node

private:
    std::unique_ptr<Node> root;
};

#endif
