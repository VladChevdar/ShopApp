#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>
#include <stdexcept> 
#include <algorithm>
#include "Date.h"

class Product
{
public:
	Product() : Name("None"), Price(0), Descr("None"), SKU(0) {}
	Product(const std::string& name, float price, const std::string& descr);
    virtual ~Product() = default;
	virtual int compare(const std::string& other_name) const; // Compare the name
	virtual void create(const std::string& name, float price, const std::string& descr); // Create a product
	virtual std::string title(const std::string& other_name) const;
	virtual int get_price() const; // Return price of the item
	virtual std::string get_name() const; // Return name
	virtual void display(); // Display product
	virtual void display_item() = 0;
	int getSKU(); // Return SKU

	// Compares the price of the product to other given price
	bool operator < (int other_price);
	bool operator <= (int other_price);
	bool operator > (int other_price);
	bool operator >= (int other_price);
	bool operator == (int other_price);

protected:
	std::string Name; // Name of the product
	int Price; // Price of the product
	std::string Descr; // Description of the product
	int SKU; // Stock keeping unit for the product
};

class Electronic : public Product
{
public:
	Electronic() : Product(), Warranty(0), Brand("None") {}
	Electronic(int warranty, const std::string& brand) : Warranty(warranty), Brand(brand) {}
	float return_item(int days_used) const;// Return price of returned product
	virtual void display_item();

private:
	int Warranty; // Product warranty in months (units)
	std::string Brand; // Name of the brand of the product
};

class Game : public Product
{
public:
	Game() : Product(), minAge(0), Rating(0) {}
	Game(int min_age, float rating) : minAge(min_age), Rating(rating) {}
	virtual void display_item();

	

private:
	int minAge; // Minimum age to play the game
	float Rating; // Rating of the game in stars
};

class Food : public Product
{
public:
	Food() : Product(), ExpiryDate() {}
	Food(const Date& other_date, const std::string& ingredients) : ExpiryDate(other_date), Ingredients(ingredients) {} 
	virtual void display_item();


private:
	Date ExpiryDate; // Exparation date MM-DD-YYYY
	std::string Ingredients; // List of ingredients
};

	
#endif
