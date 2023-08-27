#include "BST.h"
#include "fstream"

// Remove a node from bst, helper
bool BST::remove_data(const std::string& data)
{
    return remove_data(root, data);
} 

// Remove all nodes
void BST::remove_all() 
{
	root = nullptr;
}


// Remove a node from bst
bool BST::remove_data(std::unique_ptr<Node>& root, const std::string& data)
{
    if (!root) {
        return false;
    }

    if (root->get_item()->compare(data) < 0) {
        return remove_data(root->get_left(), data);
    }
    else if (root->get_item()->compare(data) > 0) {
        return remove_data(root->get_right(), data);
    }
	// Node with only one child or no child
	if (!root->get_left() && !root->get_right())
	{
		root = std::move(nullptr);
		return true;
	}
	else if (!root->get_left())
	{
		std::unique_ptr<Node> temp = std::move(root->get_right());
		root = std::move(temp);
		return true;
	}
	else if (!root->get_right())
	{
		std::unique_ptr<Node> temp = std::move(root->get_left());
		root = std::move(temp);
		return true;
	}

	// Node with two children
	std::unique_ptr<Node>& temp = minValueNode(root->get_right());
	root->set_item(temp->get_item());
	return remove_data(root->get_right(), temp->get_item()->get_name());
}

// Find the smallest
std::unique_ptr<Node>& BST::minValueNode(std::unique_ptr<Node>& node)
{
    std::unique_ptr<Node>* current = &node;
    while ((*current)->get_left())
    {
        current = &((*current)->get_left());
    }
    return *current;
}

// Return the height, helper
int BST::find_height() const
{
	return find_height(root);
}

// Return the height
int BST::find_height(const std::unique_ptr<Node>& node) const
{
	if (!node) {
		return 0;
	}
	return 1 + std::max(find_height(node->get_left()), find_height(node->get_right()));

}

// Return number of nodes in the bst
int BST::count_nodes() const
{
	return count_nodes(root);
}

// Count nodes
int BST::count_nodes(const std::unique_ptr<Node>& node) const
{
	if (!node) {
		return 0;
	}
	return 1 + count_nodes(node->get_left()) + count_nodes(node->get_right());
}

// Copy bst
BST::BST(const BST& other)
{
	root = copy_nodes(other.root);
}

// Copy node with its children
std::unique_ptr<Node> BST::copy_nodes(const std::unique_ptr<Node>& other_root)
{
	if (!other_root) {
		return nullptr;
	}
	auto newNode = std::make_unique<Node>(other_root->get_item()); 
	newNode->set_left(copy_nodes(other_root->get_left()));
    newNode->set_right(copy_nodes(other_root->get_right()));
    return newNode;
}

// Find an item, no matter the lowercase, and return the proper name format
std::string BST::title(const std::string& name) const
{
	return title(root, name);	
}


// Return new formated name
std::string BST::title(const std::unique_ptr<Node>& node, const std::string& name) const
{   
    if (!node) { 
        return "None";
    }

    std::string left = title(node->get_left(), name);
    if (left != "None") {
        return left;
    } 

    std::string this_name = node->get_item()->title(name);
    if (this_name != "None") {
        return this_name;
    }

    return title(node->get_right(), name);
}

// Find an item in the bst
float BST::find(const std::string& name, bool display) const
{
	return find(root, name, display);	
}

// Return price of the item, 0 if not foudn
float BST::find(const std::unique_ptr<Node>& node, const std::string& name, bool display) const
{
	if (!node) {
		return 0;
	}
	int difference = node->get_item()->compare(name);
	if (difference == 0) {
		if (display) {
			node->get_item()->display_item();
		}
		return node->get_item()->get_price();
	}
	if (difference < 0) {
        return find(node->get_left(), name, display);
    }
    return find(node->get_right(), name, display);
}

// Find an item in the bst
float BST::return_item(const std::string& name, int days_used) const
{
	return return_item(root, name, days_used);	
}
// Return price of the item, 0 if not foudn
float BST::return_item(const std::unique_ptr<Node>& node, const std::string& name, int days_used) const
{
	if (!node) {
		return -1; // Item is not in the store
	}
	int difference = node->get_item()->compare(name);
	if (difference == 0) {
        std::cout << "\nReturn in process...\n";
        sleep(1); // Make the user wait 1 sec
		std::shared_ptr<Electronic> e_ptr = std::dynamic_pointer_cast<Electronic>(node->get_item());
		if (!e_ptr) {
			return -2; // Only allow to return electronic
		}
		return e_ptr->return_item(days_used);
	}
	if (difference < 0) {
        return return_item(node->get_left(), name, days_used);
    }
    return return_item(node->get_right(), name, days_used);
}

// Load inventory from external file	
bool BST::load(std::string filename)
{
	std::ifstream file(filename);
	if (!file) {
		std::cerr << "Unable to open file\n";
		return false;
	}
	std::string type;
	while (std::getline(file, type, '|')) {
		if (type == "Electronic") {
			std::vector <std::string> data_list = {};
			int data_size = 5;
			for (int i = 0; i < data_size; i++) {
				std::string data = "";
				std::getline(file, data, '|');
				data_list.push_back(data);
			}
			file.ignore(100, '\n');
			std::shared_ptr<Product> e_ptr = std::make_shared<Electronic>(std::stoi(data_list[3]), data_list[4]);
			e_ptr->create(data_list[0], std::stoi(data_list[1]), data_list[2]);
			add(e_ptr);
		}
		else if (type == "Food") {
			std::vector <std::string> data_list = {};
			int data_size = 5;
			for (int i = 0; i < data_size; i++) {
				std::string data = "";
				std::getline(file, data, '|');
				data_list.push_back(data);
			}
			file.ignore(100, '\n');
			Date data(
				std::stoi(data_list[3].substr(0, 2)),  // Month
				std::stoi(data_list[3].substr(3, 2)),  // Day
				std::stoi(data_list[3].substr(6, 4))   // Year
			);

			std::shared_ptr<Product> f_ptr = std::make_shared<Food>(data, data_list[4]);
			f_ptr->create(data_list[0], std::stoi(data_list[1]), data_list[2]);
			add(f_ptr);
		}
		else if (type == "Game") {
			std::vector <std::string> data_list = {};
			int data_size = 5;
			for (int i = 0; i < data_size; i++) {
				std::string data = "";
				std::getline(file, data, '|');
				data_list.push_back(data);
			}
			file.ignore(100, '\n');

			std::shared_ptr<Product> g_ptr = std::make_shared<Game>(std::stoi(data_list[3]), std::stoi(data_list[4]));
			g_ptr->create(data_list[0], std::stoi(data_list[1]), data_list[2]);
			add(g_ptr);
		}
	}
	file.close();
	return true;
}

// Add an item to the bst, helper
int BST::add(std::shared_ptr<Product>& item) {
    return add(root, item);
}

// Add an item to the bst
int BST::add(std::unique_ptr<Node>& node, std::shared_ptr<Product>& item) {
    if (!node) {
        node = std::make_unique<Node>(item);
        return 1;
    }
    
    if (node->get_item()->compare(item->get_name()) < 0)
	{
        return add(node->get_left(), item);
    } else {
        return add(node->get_right(), item);
    }
}

// Display all, helper
int BST::display_all() const {
    return display_all(root);
}

// Display all
int BST::display_all(const std::unique_ptr<Node>& node) const {
    if (!node) {
        return 0;
    }
    
    //node->get_item()->display();
    node->display_item();
    int count = 1 + display_all(node->get_left());
	node->display_item();
	count += display_all(node->get_right());
    return count;
}

