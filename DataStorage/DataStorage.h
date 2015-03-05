#ifndef DATASTORAGE_H
#define DATASTORAGE_H
#include <vector>
#include <string>

using namespace std;
class DataStorage{

private:
	vector<string> itemList;
	vector<string> recentInput;

public:
	DataStorage();
	void showWelcomeMessage();
	void addItem(string item);
	void displayList();
	void deleteItem(int itemNumber);
	void clearItem();
	void sortItem();
	void setRecentInput(string command, string item);
	void executeUndo();
	vector<string> getRecentInput();
	vector<string> searchItem(string word);
	void displaySearch(vector<string> searchList);
	vector<string> getItemList();
};
#endif