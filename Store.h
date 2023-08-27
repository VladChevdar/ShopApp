#ifndef STORE_H
#define STORE_H

#include "BST.h"
#include <forward_list>
#include <iomanip>

class Store
{
public:
	Store();
	bool add_to_cart(const std::string& item_name); // Return false if not found
	bool remove_from_cart(const std::string& item_name); // Return false if item is not in the cart
	bool checkout_cart(int& user_funds); // Return true if enought money to buy items inside the cart
	int apply_coupon(const std::string coupond_code); // Apply a coupon to a cart
	void display_inventory() const; // Display all inventory
	void display_cart() const; // Display all items in cart
	int display_total() const; // Display total price for all items in the cart
	void display_item(const std::string& item) const; // Display an item
	bool remove_item(const std::string& data); // Remove an item from the inventory
	void display_stats() const; // Display height and #of nodes in the inventory (bst)
	void remove_all(); // Remove all items from inventory
	float return_item(const std::string& name, int days_used); // Return an item
    int display_purchase_history() const; // Return number of purchases items

private:
	BST storage; // Stores products
	std::forward_list<std::string> cart; // Stores products that user adds
	std::vector <std::string> item_history; // History of all items purchased in the store
	std::vector <float> price_history; // History of the price item was bought for
	std::string coupon;
	float total; // Total price of all items in the Cart
};

#endif
