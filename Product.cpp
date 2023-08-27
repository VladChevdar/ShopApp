#include "Product.h"

// Return name
std::string Product::get_name() const
{
	return Name;
}

// Return an item, if it is electronics
float Electronic::return_item(int days_used) const
{
	if (days_used > 14) {
		return 0;
	}
	return Price;
}

// Return positive if other_name is bigger than Name
int Product::compare(const std::string& other_name) const {
	return Name.compare(other_name);
}

// Fix title, ex: iphoe pro = Iphone Pro
std::string Product::title(const std::string& other_name) const {
	if (Name.size() != other_name.size()) {
		return "None";
    }
	int size = Name.size();
    for (int i = 0; i < size; ++i) {
        if (std::tolower(Name[i]) != std::tolower(other_name[i])) {
			return "None";
		}
    }
	std::string new_name = "";
    for (int i = 0; i < size; ++i) {
		new_name += Name[i];
    }
	return new_name;
}

// Return price
int Product::get_price() const
{
	return Price;
}

// Display product
void Product::display()
{
	std::cout << "\nProduct: " << Name;
	std::cout << "\nPrice: $" << Price;
	std::cout << "\nDescription: " << Descr << '\n';
}

// Display electornic item
void Electronic::display_item() {
	display();
	std::cout << "Warranty: " << Warranty << " months\n";
	std::cout << "Brand: " << Brand << '\n';
}

// Display food item
void Food::display_item() {
	display();
	std::cout << "Date: ";
	ExpiryDate.display();
	std::cout << "Ingredients: " << Ingredients << '\n';
}

// Display game item
void Game::display_item() {
	display();
	std::cout << "Minimum age: " << minAge;
	std::cout << "\nRating: " << Rating << " stars\n";
}

// Create a product
void Product::create(const std::string& name, float price, const std::string& descr)
{
	if (price < 0) 
	{
		throw std::invalid_argument("Invalid date");
	}
	Name = name;
	Price = price;
	Descr = descr;
	SKU = 0;

	int size = name.size();
	for (int i = 0; i < size; ++i)
	{
			SKU += name[i];
	}
}

// Create a product with the given data
Product::Product(const std::string& name, float price, const std::string& descr)
{
	create(name, price, descr);
}

// Return stock keeping unit 
int Product::getSKU()
{
		return SKU;
}

// Operators to compare price
bool Product::operator < (int other_price) {
    return Price < other_price;
}

bool Product::operator <= (int other_price) {
    return Price <= other_price;
}

bool Product::operator > (int other_price) {
    return Price > other_price;
}

bool Product::operator >= (int other_price) {
    return Price >= other_price;
}

bool Product::operator == (int other_price) {
    return Price == other_price;
}
