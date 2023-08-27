// Vlad Chevdar | CS302 | Aug 18, 2023
// The purpose of this program is to let user
// Buy items from the storage

#include "Store.h"
#include <limits>

int main() {
	int option = 0;
    bool mayEditStorage = true;
	int card_balance = 10000; // Stores user's money
	Store shop; // Manages cart and store's storage
	std::cout << "\n --- Welcome to the Retail Realm --- \n";
	do {
		{
			bool flag = true;
			while (flag)
			{
				std::cout << "\n(1) - Add item to cart\n" 
						  << "(2) - Remove item from cart\n"
						  << "(3) - Show cart contents\n"
						  << "(4) - Proceed to checkout\n"
						  << "(5) - Process a return\n"
						  << "(6) - Search for an item\n"
						  << "(7) - Remove an item from storage\n"
						  << "(8) - List entire storage\n"
						  << "(9) - View card balance\n"
						  << "(0) - Exit store\n"
						  << "\nSelect an option: ";

				std::cin >> option;
				std::cin.ignore(100, '\n');

				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Invalid option!\n";
				} else if (option < 0 || option > 9) {
					std::cout << "Invalid option!\n";
				} else {
					flag = false;
				}
			}
		}

		if (1 == option) {

			std::string product_name = "";
			std::cout << "Item: ";
			std::getline(std::cin, product_name);
			if (!shop.add_to_cart(product_name)) {
				std::cout << "This item is not available in our store.\n";
			} else {
				std::cout << '\n' << product_name << " was added to your cart\n";
                mayEditStorage = false;
			}
		}
		else if (2 == option) {
			if (shop.display_total()) {
                std::string product_name = "";
                std::cout << "\nItem to remove: ";
                std::getline(std::cin, product_name);
                if (!shop.remove_from_cart(product_name)) {
                    std::cout << product_name << " was not found in your cart\n";
                } else {
                    std::cout << product_name << " was removed from your cart\n";
                }
            }
		}
		else if (3 == option)
		{
			shop.display_cart();
		}
		else if (4 == option)
		{
			if (shop.display_total()) {
				std::cout << "Available Wallet Balance: $" << card_balance << '\n';
				do {
					bool flag = true;
					while (flag)
					{
						std::cout << "\n(1) - Redeem a Coupon Code\n"
								  << "(2) - Proceed to Payment\n"
								  << "(3) - Go Back to Main Menu\n"
								  << "(0) - Exit the Store\n"
								  << "\nSelect an option: ";

						std::cin >> option;
						std::cin.ignore(100, '\n');

						if (std::cin.fail()) {
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							std::cout << "Invalid option.\n";
						} else if (option < 0 || option > 3) {
							std::cout << "Invalid option!\n";
						} else {
							flag = false;
						}
					}
					if (1 == option) {
						std::string coupon = "";
						std::cout << "Enter your coupon code: ";
						std::getline(std::cin, coupon);
						int apply = shop.apply_coupon(coupon);
						if (apply == 1) {
							std::cout << "The coupon code is invalid\n";
						} else if (apply == 2) {
							std::cout << "\nThe coupon code was already applied\n";
						}
					}
					else if (2 == option) {
						if (!shop.checkout_cart(card_balance)) {
							std::cout << "Insufficient funds! Items cannot be purchased\n";
						} else {
							std::cout << " *** Thank you for shopping with us ***\n";
						}
						option = 3;
					}
				} while (option == 1);
			}
		}
		else if (5 == option)
        {
            if (!shop.display_purchase_history()) {
				std::cout << "You purchase history is empty\n";
            } 
            else {
                std::string product_name = "";
                int days_used = 0;
		    	bool flag = true;

                std::cout << "Item to return: ";
                std::getline(std::cin, product_name);

                while (flag)
                {
                    std::cout << "Enter the number of days since your purchase: ";
                    std::cin >> days_used;
                    std::cin.ignore(100, '\n');

                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid option!\n";
                    } else if (option < 0) {
                        std::cout << "Invalid option!\n";
                    } else {
                        flag = false;
                    }
                }
                float return_value = shop.return_item(product_name, days_used);

                if (return_value == 0) {
                    std::cout << "Return is only avaliable for the first 14 days!\n";
                } else if (return_value == -1) {
                    std::cout << "This item was never sold to you!\n";
                } else if (return_value == -2) {
                    std::cout << "Only electronics can be returned!\n";
                } else if (return_value == -3) {
                    std::cout << product_name << " was not found in your purchase history!\n";
                } else {
                    card_balance += return_value;
                    std::cout << product_name << " was returned for $" << return_value << '\n';
                    std::cout << "New card balance: $" << card_balance << '\n';
                }
            }
		}
		else if (6 == option) {
			std::string product_name = "";
			std::cout << "Item to display: ";
			std::getline(std::cin, product_name);
			shop.display_item(product_name);
		}
		else if (7 == option) {
            if (!mayEditStorage) {
                std::cout << "This option expired once you placed an item into your cart!\n";

            } else {
                std::string product_name = "";
                std::cout << "Item to remove: ";
                std::getline(std::cin, product_name);
                if (product_name == "all")
                {
                        shop.remove_all();	
                        shop.display_stats();
                } else {
                    if (!shop.remove_item(product_name)) {
                        std::cout << product_name << " was not found in the store\n";
                    } else {
                        std::cout << product_name << " was removed from the store\n";
                        shop.display_stats();
                    }
                }
            }
        }
		else if (8 == option) {
			shop.display_inventory();
		}
		else if (9 == option) {
			std::cout << "Card balance: $" << card_balance << '\n';
		}
	} while (option);

	return 0;
}
