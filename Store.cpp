#include "Store.h"

// Initilize data
Store::Store() {
    if (!storage.load("Inventory.txt")) {
        throw std::runtime_error("Failed to load the inventory!");
    }
	item_history.clear();
	price_history.clear();
	coupon = "None";
    total = 0;
}

// Remove an item from the inventory
bool Store::remove_item(const std::string& item)
{
	return storage.remove_data(item);
}

// Display history, return the number of purchases
int Store::display_purchase_history() const
{
	int size = item_history.size();
    if (!size) {
        return 0;
    }
    std::cout << "\n" << std::string(14, '-') 
              << " Receipt " << std::string(17, '-') << "\n"
              << "Description" << std::string(25 - std::string("Description").length(), ' ') 
              << std::string(5, ' ') << "Price" << "\n"
              << std::string(40, '-') << "\n";

    for (int i = 0; i < size; ++i) {
        std::string itemName = item_history[i];
        if (itemName.length() > 30) {
            itemName = itemName.substr(0, 27) + "...";
        }
        std::cout << itemName << std::string(30 - itemName.length(), ' ') 
                  << "$" << std::fixed << std::setprecision(2) << price_history[i] << '\n';
    }
	std::cout << std::string(40, '-') << "\n\n"; // Footer
    std::cout << "14 days return policy on all electronics\n";
	std::cout << std::string(40, '-') << "\n\n"; // Footer
                                              
    return size;
}

// Remove an item from the inventory
float Store::return_item(const std::string& item, int days_used)
{
	std::string this_item = storage.title(item);
	int size = item_history.size();
	float return_value = storage.return_item(this_item, days_used);
    if (return_value < 1) {
        return return_value;
    }
    for (int i = 0; i < size; ++i)
    {
        if (item_history[i] == this_item) {
            return_value = price_history[i];
            item_history.erase(item_history.begin() + i);
            price_history.erase(price_history.begin() + i);
            return return_value;
        }
    }
	return -3; // Item was never bought in the store
}

// Remove all items from the inventory
void Store::remove_all()
{
	return storage.remove_all();
}

// Display the height and node count of bst
void Store::display_stats() const 
{
	std::cout << "Tree height: " << storage.find_height() << '\n';
	std::cout << "Total nodes: " << storage.count_nodes() << '\n';
}

// Display an item
void Store::display_item(const std::string& item) const {
    if (!storage.find(item, true)) {
        std::cout << "\nItem was not found in the store\n";
    }
}

// Display price of all items in the cart, helper function
int Store::display_total() const {
    if (cart.empty()) {
        std::cout << "\nThe cart is empty\n";
        return 0;
    }

    std::cout << "\nItems in your cart: \n";
    int count = 0;
    for (const auto& item : cart) {
        std::cout << item << '\n';
        count++;
    }

    std::cout << "\nPurchase Total: $" << total << '\n';
    return count;
}

// Add an item to the cart
bool Store::add_to_cart(const std::string& item) {
	std::string this_item = storage.title(item);
	if (this_item == "None") {
		return false;
	}
    float Price = storage.find(this_item, true);
    if (!Price) {
        return false;
    }
	if (coupon == "Summer") {
		Price -= Price / 5.0;
	}
    cart.push_front(this_item);  
    total += Price;
    return true;
}

// Checkout all items from the cart, and add to history
bool Store::checkout_cart(int& user_funds) {
    if (user_funds >= total)
	{
		// Write to history
		std::copy(cart.begin(), cart.end(), std::back_inserter(item_history));
		int cart_size = std::distance(cart.begin(), cart.end());
		int history_size = price_history.size();
		// Print cool receipt
		std::cout << "\n" << std::string(14, '-') 
				  << " Receipt " << std::string(17, '-') << "\n"
				  << "Description" << std::string(25 - std::string("Description").length(), ' ') 
		          << std::string(5, ' ') << "Price" << "\n"
				  << std::string(40, '-') << "\n";

		for (int i = history_size; i < history_size + cart_size; ++i) {
			float final_price = storage.find(item_history[i], false);
            if (coupon == "Summer") {
                final_price -= final_price / 5.0;
            }
            price_history.push_back(final_price);

            // Format item name
            std::string itemName = item_history[i];
            if (itemName.length() > 30) {
                itemName = itemName.substr(0, 27) + "...";
            }
            std::cout << itemName << std::string(30 - itemName.length(), ' ') 
                      << "$" << std::fixed << std::setprecision(2) << final_price << '\n';
		}
		std::cout << std::string(40, '-') << "\n" // Footer
				  << "Total" << std::string(25 - std::string("Total").length(), ' ') 
		          << std::string(5, ' ') << '$' << std::fixed << std::setprecision(2) << total << "\n"
				  << std::string(40, '-') << "\n"; // Footer
		if (coupon == "Summer") {
			std::cout << "Savings" << std::string(25 - std::string("Savings").length(), ' ') 
					  << std::string(5, ' ') << '$' << std::fixed 
					  << std::setprecision(2) << (total/0.8)/5.0  << "\n"
					  << std::string(40, '-') << "\n"; // Footer
		}
		// End of cool receipt print

        user_funds -= total;
        cart.clear();
        total = 0;
        return true;
    }
    return false;
}

// Remove an item from the cart
bool Store::remove_from_cart(const std::string& item) {
    bool itemFound = false;
    for (auto it = cart.begin(), prev = cart.before_begin(); it != cart.end(); ++prev, ++it) {
        if (*it == item) {
            float price = storage.find(item, false);
            if (price) {
				if (coupon == "Summer") {
					price -= price / 5.0;
				}
                total -= price;
                cart.erase_after(prev);
                itemFound = true;
                break;
            }
        }
    }
    return itemFound;
}

// Give a discount to all items in the cart if valid coupon
int Store::apply_coupon(const std::string coupon) {
    if (coupon == "Summer")
	{
		if (this->coupon == coupon) {
			return 2;
		}
		total -= total / 5.0;
		this->coupon = coupon;
        std::cout << "Discount of $" << total / 5.0 << " was applied\n";
        std::cout << "New total: $" << total << '\n';

        return 0;
    }
    return 1;
}

// Display all items in the inventory
void Store::display_inventory() const {
    int count = storage.display_all();
    if (count == 0) {
        std::cout << "The inventory is empty\n";
    } else {
        std::cout << "\nTotal of " << count << " items\n";
    }
}

// Display all items in the cart
void Store::display_cart() const {
	if (cart.empty()) {
		std::cout << "The cart is empty\n";
		return;
	}
    
    std::cout << "\nItems in your cart:\n";
	for (const auto& item : cart) {
		if (!storage.find(item, true)) {
			std::cout << "Unknown item in the cart\n";
		}
	}
}

