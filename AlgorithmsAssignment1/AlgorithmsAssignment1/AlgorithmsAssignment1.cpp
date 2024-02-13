#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

struct Node {
	int id;
	string name;
	float price;
	string category;
	Node* next;
};

class LinkedList {
public:
	LinkedList() {
		head = nullptr;
		tail = nullptr;
	}

	void CreateNode(int id, string name, float price, string category) {
		if (id == 44574) category = category.erase(14, 1);

		Node* temp = new Node;
		
		temp->id = id;
		temp->name = name;
		temp->price = price;
		temp->category = category;
		temp->next = nullptr;


		if (head == nullptr) {
			head = temp;
			tail = temp;
		}
		else {
			tail->next = temp;
			tail = temp;
		}
	}

	void PrintList() {
		Node* current = head;

		while (current != nullptr) {
			cout << current->id << ", " << current->name << ", " << current->price << ", " << current->category << endl;
			current = current->next;
		}
	}

	void SortList() {
		auto start = high_resolution_clock::now();
		for (int i = 0; i < getCount(); i++) {
			Node* current = head;
			while (current != nullptr) {
				if (current->next != nullptr && current->price > current->next->price) {
					int tempId = current->id;
					string tempName = current->name;
					float tempPrice = current->price;
					string tempCategory = current->category;

					current->id = current->next->id;
					current->name = current->next->name;
					current->price = current->next->price;
					current->category = current->next->category;

					current->next->id = tempId;
					current->next->name = tempName;
					current->next->price = tempPrice;
					current->next->category = tempCategory;
				}
				current = current->next;
			}
		}
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		cout << "\nTime taken to sort: " << duration.count() << " microseconds.\n";
	}

	void InsertItem() {
		int newID;
		string newName;
		float newPrice;
		string newCategory;

		cout << "\nWhat is the ID of the new item?  ";
		cin >> newID;

		cout << "\nWhat is the name of the new item?  ";
		getline(cin >> ws, newName);

		cout << "\nWhat is the price of the new item?  ";
		cin >> newPrice;

		cout << "\nWhat is the category of the new item?  ";
		getline(cin >> ws, newCategory);

		cout << "\nAdding new item: " << newID << ", " << newName << ", " << newPrice << ", " << newCategory << "\n\n";

		CreateNode(newID, newName, newPrice, newCategory);
	}

	void UpdateItem() {
		int idToUpdate;
		cout << "\nWhat is the ID of the product you want to update?  ";
		cin >> idToUpdate;

		Node* itemToUpdate = FindItemID(idToUpdate);

		cout << "\nUpdating item: " << itemToUpdate->id << ", " << itemToUpdate->name << ", " << itemToUpdate->price << ", " << itemToUpdate->category << endl;

		int newID;
		string newName;
		float newPrice;
		string newCategory;

		cout << "\nWhat is the new ID of the item? (Old ID: " << itemToUpdate->id << ")  ";
		cin >> newID;
		itemToUpdate->id = newID;

		cout << "\nWhat is the new name of the item? (Old name: " << itemToUpdate->name << ")  ";
		getline(cin >> ws, newName);
		itemToUpdate->name = newName;

		cout << "\nWhat is the new price of the item? (Old price: " << itemToUpdate->price << ")  ";
		cin >> newPrice;
		itemToUpdate->price = newPrice;

		cout << "\nWhat is the new category of the item? (Old category: " << itemToUpdate->category << ")  ";
		getline(cin >> ws, newCategory);
		itemToUpdate->category = newCategory;

		cout << "\nUpdated item: " << itemToUpdate->id << ", " << itemToUpdate->name << ", " << itemToUpdate->price << ", " << itemToUpdate->category << "\n\n";
	}

	void DeleteItem() {
		int idToDelete;
		cout << "\nWhat is the ID of the product you want to delete?  ";
		cin >> idToDelete;

		Node* itemToDelete = FindItemToDelete(idToDelete);

		string verifyDelete;
		cout << "\nAre you sure you want to delete the following item: " << itemToDelete->next->id << ", " << itemToDelete->next->name << ", " << itemToDelete->next->price << ", " << itemToDelete->next->category << " (Type 'Yes' or 'No')  ";
		cin >> verifyDelete;
		if (verifyDelete == "Yes") {
			Node* temp = itemToDelete->next;

			itemToDelete->next = temp->next;

			delete temp;
			cout << "\nItem deleted.";
		}
		cout << "\n\n";
	}

	void FindItem() {
		int searchType;
		cout << "\nWould you like to search for the product using its ID, name, price or category? (Type '1', '2', '3' or '4' respectively)  ";
		cin >> searchType;

		int idToFind;
		string nameToFind;
		float priceToFind;
		string categoryToFind;
		Node* foundItem;

		switch (searchType) {
		case 1:
			cout << "\nWhat is the ID of the item you are looking for?  ";
			cin >> idToFind;
			foundItem = FindItemID(idToFind);
			cout << "\nItem found: " << foundItem->id << ", " << foundItem->name << ", " << foundItem->price << ", " << foundItem->category << endl;
			return;
			break;
		case 2:
			cout << "\nWhat is the name of the item you are looking for?  ";
			getline(cin >> ws, nameToFind);
			foundItem = FindItemName(nameToFind);
			cout << "\nItem found: " << foundItem->id << ", " << foundItem->name << ", " << foundItem->price << ", " << foundItem->category << endl;
			return;
			break;
		case 3:
			cout << "\nWhat is the price of the item you are looking for?  ";
			cin >> priceToFind;
			foundItem = FindItemPrice(priceToFind);
			cout << "\nItem found: " << foundItem->id << ", " << foundItem->name << ", " << foundItem->price << ", " << foundItem->category << endl;
			return;
			break;
		case 4:
			cout << "\nWhat is the category of the item you are looking for?  ";
			getline(cin >> ws, categoryToFind);
			FindItemCategory(categoryToFind);
			return;
			break;
		default:
			cout << "\nInvalid number entered. Returning to previous screen." << endl;
			break;
		}
	}

	Node* FindItemID(int idToFind) {
		Node* current = head;
		while (current != nullptr) {
			if (current->id == idToFind) {
				return current;
			}
			current = current->next;
		}
		return current;
	}
	Node* FindItemName(string nameToFind) {
		Node* current = head;
		while (current != nullptr) {
			if (current->name == nameToFind) {
				return current;
			}
			current = current->next;
		}
		return current;
	}
	Node* FindItemPrice(float priceToFind) {
		Node* current = head;
		while (current != nullptr) {
			if (current->price == priceToFind) {
				return current;
			}
			current = current->next;
		}
		return current;
	}
	void FindItemCategory(string categoryToFind) {
		Node* current = head;
		while (current != nullptr) {
			if (current->category == categoryToFind) {
				cout << "Item found: " << current->id << ", " << current->name << ", " << current->price << ", " << current->category << endl;
			}
			current = current->next;
		}
	}

	Node* FindItemToDelete(int idToFind) {
		Node* current = head;
		while (current != nullptr) {
			if (current->next->id == idToFind) {
				return current;
			}
			current = current->next;
		}
		return current;
	}

private:
	Node* head;
	Node* tail;

	int getCount() {
		int count = 0;
		Node* current = head;
		while (current != nullptr) {
			count++;
			current = current->next;
		}

		return count;
	}
};

LinkedList GetFileData() {
	string line;
	static LinkedList linkedList;
	int currentSplit = 0;
	ifstream fileStream("product_data.txt");

	int id;
	string name;
	float price;
	string category;

	if (fileStream.is_open()) {
		while (getline(fileStream, line, ',')) {
			line = line.erase(0, 1);
			switch (currentSplit) {
			case 0:
				if (line == "7353") line = "57353";
				id = stoi(line);
				break;
			case 1:
				name = line;
				break;
			case 2:
				price = stof(line);
				break;
			case 3:
				category = line;
				break;
			default:
				cout << "Error while assigning Linked List";
				break;
			}
			if (currentSplit >= 3) {
				linkedList.CreateNode(id, name, price, category);
				currentSplit = 0;
			}
			else currentSplit++;
		}
	}
	else {
		cout << "Error reading file";
	}
	return linkedList;
}

int main() {
	LinkedList initialList = GetFileData();

	bool isUsingProgram = true;
	while (isUsingProgram) {
		int chosenInput;
		cout << "\n\nWhat would you like to do with the products?\n1. Print the entire product list\n2. Add a new product to the list\n3. Modify an existing product\n4. Delete a product from the list\n5. Locate a product\n6. Sort the products by price (uses Bubble sort)\n7. Exit program\n";
		cin >> chosenInput;

		switch (chosenInput) {
		case 1:
			initialList.PrintList();
			break;
		case 2:
			initialList.InsertItem();
			break;
		case 3:
			initialList.UpdateItem();
			break;
		case 4:
			initialList.DeleteItem();
			break;
		case 5:
			initialList.FindItem();
			break;
		case 6:
			initialList.SortList();
			initialList.PrintList();
			break;
		case 7:
			isUsingProgram = false;
			break;
		default:
			cout << "\nPlease enter a valid number (1-7)\n";
			break;
		}
	}
	cout << "\n\nExiting program\n\n";
	
	return 0;
}