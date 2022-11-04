#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//This program is used to make a Book database with records that the user can 
//manipulate. I was going to use switch-case, inheritance, polymorphism and try-catch 
//blocks and other CMPT135 features, but felt only the ones I have used were necessary 
//to solve the problems.

class Book
{
private:
	string Title;	//Title of the book
	string Author;	//Author of the book
	int DateOfPublication;	//Publication year/date of the book
	string Type;	//Type of the book (Hardcover, Softcover, Digital)
	int numOfPages;	//Number of pages in the book

public:

	//Constructors
	Book(); //Constructs a default book with default values
	Book(const string &title, const string &author, const int &date, const string &type, const int &pages); //Constructs a non-default book with parameter values
	
	//Since no pointers are involved as member variables, 
	//there is no copy constructor, destructor or assignment operator overloaded

	//Getters
	string getTitle() const;
	string getAuthor() const;
	int getDate() const;
	string getType() const;
	int getPages() const;

	//Setters
	void setTitle(const string &title);
	void setAuthor(const string &author);
	void setDate(const int &date);
	void setType(const string &type);
	void setPages(const int &pages);

	//Other Member and Friend Functions
	
	//Overloaded operators
	bool operator==(const Book& b) const;  //to compare two books
	bool operator<(const Book &b) const;  //to sort alphabetically by title

	//Overloaded istream and ostream operators
	friend ostream& operator<<(ostream& out, const Book &b);
	friend istream& operator>>(istream& in, Book &b);
};

typedef vector<Book> vectorBook;	//changes vector<Book> to vectorBook for easier coding

Book::Book() : Title("N/A"), Author("N/A"), DateOfPublication(0), Type("N/A"), numOfPages(0) {}  

Book::Book(const string &title, const string &author, const int &date, const string &type, const int &pages)
{
	this->Title = title;
	this->Author = author;
	this->DateOfPublication = date;
	this->Type = type;
	this->numOfPages = pages;
}

string Book::getTitle() const {return Title;}
string Book::getAuthor() const {return Author;}
int Book::getDate() const {return DateOfPublication;}
string Book::getType() const {return Type;}
int Book::getPages() const {return numOfPages;}

void Book::setTitle(const string &title) {this->Title = title;}
void Book::setAuthor(const string &author) {this->Author = author;}
void Book::setDate(const int &date) 
{
	//Sets the date/year to the parameter value but ensures it is between 0 and 2020
	//If not, asks the user to enter the date again
	
	this->DateOfPublication = date;
	while(DateOfPublication < 0 || DateOfPublication > 2020)
	{
		cout << "\Please Enter the Date of Publication. The date must be less than 2020 and greater than 0: ";
		cin >> this->numOfPages;
	}
}
void Book::setType(const string &type) 
{
	//Ensures the string parameter is either "Hardcover", "Sofcover" or "Digital"
	//Or else asks user to enter the type again and sets the type to the parameter

	while(true)
	{
		if(type == "Hardcover")
			break;
		else if(type == "Softcover")
			break;
		else if(type == "Digital")
			break;
		else
		{
			cout << "\tThe Type of book you entered is incorrect! Please re-enter the type of book. A book can be Hardcover, Softcover or Digital: ";
			cin >> this->Type;
		}
	}
	this->Type = type;
}
void Book::setPages(const int &pages) 
{
	//Sets the number of pages to the parameter value but ensure it is greater than 0 
	//If not, asks the user to enter the number of pages again

	this->numOfPages = pages;	
	while(numOfPages < 0)
	{
		cout << "\tEnter the Number of Pages. The number must be greater than 0: ";
		cin >> this->numOfPages;
	}
}

bool Book::operator==(const Book &b) const
{
	//This function compares whether every member variabe in the calling object and the parameter are equal to ensure the books are equal
	//This function will be used by the find function used with vector
	
	if(this->Title == b.Title && this->Author == b.Author && this->DateOfPublication == b.DateOfPublication && this->numOfPages == b.numOfPages && this->Type == b.Type)
		return true;
	else
		return false;
}

bool Book::operator<(const Book &b) const
{
	//This function compares the calling object with the parameter, specifically the title
	//This will be done to sort books alphabetically

	if(this->getTitle() < b.getTitle())
		return true;
	return false;
}

ostream& operator<<(ostream& out, const Book &b)
{
	//overloaded << operator to print a book record in a specific format
	
	out << setw(30) << left << b.getTitle() << setw(30) << left << b.getAuthor() << setw(10);
	out << left << b.getDate() << setw(15) << left << b.getType() << setw(10) << left << b.getPages();	
	return out;
}

istream& operator>>(istream& in, Book &b)
{
	//overloaded >> operator to enter book information into the database
	
	cout << endl << "Please enter a book: " << endl;
	cout << "\tEnter the Title: ";
	in >> b.Title;
	cout << "\tEnter the Author: ";
	in >> b.Author;
	
	cout << "\tPlease Enter the Date of Publication. The date must be less than 2020 and greater than 0: ";
	in >> b.DateOfPublication;
		
	//Ensures the date, type and number of pages are not invalid
	
	while(b.getDate() > 2020 || b.getDate() < 0)
	{
		cout << "The date you entered is invalid!. Please try again. The date must be less than 2020 and greater than 0: ";
		in >> b.DateOfPublication;
	}
	
	cout << "\tEnter the Type of Book. A book can be Hardcover, Softcover or Digital: ";
	in >> b.Type;

	while(true)
	{
		if(b.getType() == "Hardcover")
			break;
		else if(b.getType() == "Softcover")
			break;
		else if(b.getType() == "Digital")
			break;
		else
		{
			cout << "\tThe Type of book you entered is incorrect! Please re-enter the type of book. A book can be Hardcover, Softcover or Digital: ";
			in >> b.Type;
		}
	}

	do
	{
		cout << "\tEnter the Number of Pages. The number must be greater than 0: ";
		in >> b.numOfPages;

	}while(b.numOfPages <= 0);
	
	cout << endl;
	return in;
}


class Database
{
private:
	vectorBook Data;
public:
	//Constructors
	Database();
	Database(vectorBook &data);

	//No need for Copy Constructor, Assignment Operator, or Destructor

	//Other Member Functions
	
	int getSize() const; //returns the size of the vector
	void newBook(const Book &b);
	void removeBook(const Book &b);
	
	//Search functions for individual books
	Book searchBook(const Book &b);
	Book searchTitle(const string &title);
	Book searchAuthor(const string &author);
	Book searchType(const string &tyoe);
	Book searchDate(const int &date);
	Book searchPages(const int &pages);
	
	//Modification functions for individual books
	void updateTitle(const string &title, Book &b); 
	void updateAuthor(const string &author, Book &b);
	void updateType(const string &type, Book &b);
	void updateDate(const int &date, Book &b);
	void updatePages(const int &pages, Book &b);
	
	//Searching and printing all books that match the parameter
	void searchAllBooks(const Book &b);
	void searchAllTitles(const string &title);
	void searchAllAuthors(const string &author);
	void searchAllTypes(const string &type);
	void searchAllDates(const int &date);
	void searchAllPages(const int &pages);

	//Printing Book records
	string outputData(const int &index);
	void print();
};

Database::Database() : Data(0) {}; //Constructs a default Database with size 0

Database::Database(vectorBook &data) : Data(data) {} //Constructs a non-default Database with all the values from a vectorBook parameter

int Database::getSize() const {return Data.size();} //Returns the size of the Data vectorBook

void Database::newBook(const Book &b)
{
	//This function appends a new book to the Database and then sorts it using the 
	//vector sort algorithm, which uses the overloaded < operator
	
	this->Data.push_back(b);

	//sort elements by book title
	vectorBook::iterator its = this->Data.begin();
	vectorBook::iterator ite = this->Data.end();
	sort(its, ite);
}

void Database::removeBook(const Book &b)
{
	//This function uses the find function for vectors to search for a specific book
	//using the overloaded == operator. if the returned iterator value is not Data.end() then
	//it uses the erase function to delete the element, if it is Data.end(), it prints an error message
	
	vectorBook::iterator it1 = this->Data.begin();
	vectorBook::iterator it2 = this->Data.end();
	vectorBook::iterator it = find(it1, it2, b);

	if(it != it2)
		Data.erase(it);
	else
		cout << "The book you attempted to delete cannot be found. Please try again. " << endl;

}

Book Database::searchBook(const Book &b)
{
	//This funtion uses the find function with vectors to search for a book
	//If the iterator returned is not Data.end(), then the the dereference of
	//the iterator (a book) is returned, or else an empty book is constructed and returned
	
	Book a;
	vectorBook::iterator it = find(this->Data.begin(), this->Data.end(), b);
	if(it == this->Data.end())
		return a;
	else
		return *it;
}

Book Database::searchTitle(const string &title)
{
	//This function uses sequential search to find the first book in the Database
	//that has a title that matches the parameter string. If no titles are found, 
	//an empty book is constructed and returned, hence the title would be "N/A" 
	
	for(int i = 0; i < Data.size(); i++)
	{
		if(Data[i].getTitle() == title)
			return Data[i];
	}

	Book b;
	return b;
}

Book Database::searchAuthor(const string &author)
{
	//This function uses sequential search to find the first book in the Database
	//that has an author that matches the parameter string. If no authors are found, 
	//an empty book is constructed and returned, hence the author would be "N/A"
	
	for(int i = 0; i < Data.size(); i++)
	{
		if(Data[i].getAuthor() == author)
			return Data[i];
	}

	Book b;
	return b;
}

Book Database::searchDate(const int &date)
{
	//This function uses sequential search to find the first book in the Database
	//that has a date(year) that matches the parameter integer. If no matching integers are found, 
	//an empty book is constructed and returned, hence the date would be 0
	
	for(int i = 0; i < Data.size(); i++)
	{
		if(Data[i].getDate() == date)
			return Data[i];
	}

	Book b;
	return b;
}

Book Database::searchType(const string &type)
{
	//This function uses sequential search to find the first book in the Database
	//that has a type that matches the parameter string. If no matching types are found, 
	//an empty book is constructed and returned, hence the author would be "N/A"
	
	for(int i = 0; i < Data.size(); i++)
	{
		if(Data[i].getType() == type)
			return Data[i];
	}

	Book b;
	return b;
}

Book Database::searchPages(const int &pages)
{
	//This function uses sequential search to find the first book in the Database
	//that has a number of pages that matches the parameter integer. If no matching  
	//integers are found, an empty book is constructed and returned, hence the number 
	//of pages would be 0

	for(int i = 0; i < Data.size(); i++)
	{
		if(Data[i].getPages() == pages)
			return Data[i];
	}

	Book b;
	return b;
}

void Database::updateTitle(const string &title, Book &b) 
{
	//this function uses the removeBook() function to search and delete the book parameter
	//then it modifies the title of the book parameter with the string parameter and appends
	//the modified book to the database using the newBook() function
	
	this->removeBook(b);
	b.setTitle(title);	
	this->newBook(b);
	return;
}

void Database::updateAuthor(const string &author, Book &b)
{
	//this function uses the removeBook() function to search and delete the book parameter
	//then it modifies the author of the book parameter with the string parameter and appends
	//the modified book to the database using the newBook() function
	
	this->removeBook(b);
	b.setAuthor(author);	
	this->newBook(b);
	return;
}

void Database::updateType(const string &type, Book &b)
{
	//this function uses the removeBook() function to search and delete the book parameter
	//then it modifies the type of the book parameter with the string parameter and appends
	//the modified book to the database using the newBook() function
	
	this->removeBook(b);
	b.setType(type);	
	this->newBook(b);
	return;
}

void Database::updateDate(const int &date, Book &b)
{
	//this function uses the removeBook() function to search and delete the book parameter
	//then it modifies the date of the book parameter with the integer parameter and appends
	//the modified book to the database using the newBook() function
	
	this->removeBook(b);
	b.setDate(date);	
	this->newBook(b);
	return;
}

void Database::updatePages(const int &pages, Book &b)
{
	//this function uses the removeBook() function to search and delete the book parameter
	//then it modifies the number of pages of the book parameter with the integer parameter 
	//and appends the modified book to the database using the newBook() function
	
	this->removeBook(b);
	b.setPages(pages);	
	this->newBook(b);
	return;
}

void Database::searchAllBooks(const Book &b)
{
	//Searches sequentially for all the books that match the Book parameter and prints them all
	//Or else prints an error message

	Book a = this->searchBook(b);
	if(a == b)
	{
		for(int i = 0; i < Data.size(); i++)
		{
			if(Data[i] == b)
				cout << Data[i] << endl;
		}
	}
	else
		cout << "No books found in the database." << endl;
}

void Database::searchAllTitles(const string &title)
{
	//Searches sequentially for all the book titles that match the string parameter and prints them all
	//Or else prints an error message
	
	Book a = this->searchTitle(title);
	if(a.getTitle() != "N/A")
	{
		for(int i = 0; i < Data.size(); i++)
		{
			if(Data[i].getTitle() == title)
				cout << this->Data[i] << endl;
		}
	}
	else
		cout << "No Books found in the database." << endl;
}

void Database::searchAllAuthors(const string &author)
{
	//Searches sequentially for all the book authors that match the string parameter and prints them all
	//Or else prints an error message
	
	Book a = this->searchAuthor(author);
	if(a.getAuthor() != "N/A")
	{
		for(int i = 0; i < Data.size(); i++)
		{
			if(Data[i].getAuthor() == a.getAuthor())
				cout << this->Data[i] << endl;
		}
	}
	else
		cout << "No Books found in the database." << endl;
}

void Database::searchAllTypes(const string &type)
{
	//Searches sequentially for all the book types that match the string parameter and prints them all
	//Or else prints an error message
	
	Book a = this->searchType(type);
	if(a.getType() != "N/A")
	{
		for(int i = 0; i < Data.size(); i++)
		{
			if(Data[i].getType() == type)
				cout << this->Data[i] << endl;
		}
	}
	else
		cout << "No Books found in the database." << endl;
}

void Database::searchAllDates(const int &date)
{
	//Searches sequentially for all the book dates that match the integer parameter and prints them all
	//Or else prints an error message
	
	Book a = this->searchDate(date);
	if(a.getDate() != 0)
	{
		for(int i = 0; i < Data.size(); i++)
		{
			if(Data[i].getDate() == date)
				cout << this->Data[i] << endl;
		}
	}
	else
		cout << "No Books found in the database." << endl;
}

void Database::searchAllPages(const int &pages)
{
	//Searches sequentially for all the book pages that match the integer parameter and prints them all
	//Or else prints an error message
	
	Book a = this->searchPages(pages);
	if(a.getPages() != 0)
	{
		for(int i = 0; i < Data.size(); i++)
		{
			if(Data[i].getPages() == pages)
				cout << this->Data[i] << endl;
		}
	}
	else
		cout << "No Books found in the database." << endl;
}

string Database::outputData(const int &index)
{
	//Returns a string that is made using the overloaded << operator to print the Book record

	stringstream ss;
	ss << Data[index];
	return ss.str();
}

void Database::print()
{
	//Uses the overloaded << operator to print the data in the Database 

	for(int i = 0; i < this->Data.size(); i++)
		cout << Data[i] << endl;
}

int HomepageMenu(Database &v, Book &b);
void addMenu(Database &v, Book &b); 
void deleteMenu(Database &v, Book &b);
void updateMenu(Database &v, Book &B);
void searchMenu(Database &v, Book &b);
void inputMenu(Database &v, Book &b);
void outputMenu(Database &v, Book &b);

int HomepageMenu(Database &v, Book &b)
{
	//The function takes a Database object and Book object by reference as parameters
	//Displays the main menu of the application

	system("cls");
	cout << "Welcome to Raj's Book Database! " << endl;
	cout << "What would you like to do?" << endl << endl;
	cout << "\t1. Add a new book record. " << endl;
	cout << "\t2. Delete an exisitng book record. " << endl;
	cout << "\t3. Update records. " << endl;
	cout << "\t4. Search. " << endl;
	cout << "\t5. Upload a new database from a file. " << endl;
	cout << "\t6. Save a databse to a file. " << endl;
	cout << "\t7. Exit Application." << endl << endl;
	
	//Enter the menu option and ensure it is within the range

	int choice;
	cout << "\tPlease Enter the number corresponding to your choice. ";
	cin >> choice;
	
	while(choice < 1 || choice > 7)
	{
		cout << "\tYour entry was invalid! Please Enter the number corresponding to your choice. ";
		cin >> choice;
	}

	//Depending on the choice of the user, launches different functions that are other menus

	if(choice == 1)
	{
		addMenu(v, b);
	}	
	else if(choice == 2)
	{
		deleteMenu(v, b);
	}
	else if(choice == 3)
	{
		updateMenu(v, b);
	}
	else if(choice == 4)
	{
		searchMenu(v, b);
	}
	else if(choice == 5)
	{
		inputMenu(v, b);
	}
	else if(choice == 6)
	{
		outputMenu(v, b);
	}
	else
	 return 0;
}

void addMenu(Database &v, Book &b)
{
	//The function takes a Database object and Book object by reference as parameters
	//It appends the Book that was entered into the Database using the newBook() function
	//Then it takes the user back to the HomepageMenu
	
	system("cls");
	
	cin >> b;
	v.newBook(b);
	cout << "The new record has been added to the database. Returning to main menu. " << endl;
	system("pause");
	HomepageMenu(v, b);
	
}

void deleteMenu(Database &v, Book &b)
{
	//The function takes a Database object and Book object by reference as parameters
	//Displays the search menu in order to ask the user how they would like to search for
	//the record
	
	system("cls");
	cout << "Please search a book to be removed from the database." << endl;
	cout << "Books can be searched in multpile ways: " << endl;
	cout << "\t1. You could search for a book(s) to delete by entering the whole record." << endl;
	cout << "\t2. You could search for a book(s) to delete by title. " << endl;
	cout << "\t3. You could search for a book(s) to delete by the Author's name. " << endl;
	cout << "\tPlease enter a number corresponding to your choice: ";
	
	//Enter the users' choice and ensure it is within the range
	
	int choice;
	cout << "\t";
	cin >> choice;

	while(choice < 1 || choice > 3)
	{
		cout << "The number you entred was not part of the choice. Please try again. " << endl;
		cin >> choice;
	}

	if(choice == 1)
	{
		//If the user chooses one, asks them to search the book by entering all the details,
		//if the book is found (the searchBook function returns an actual book with a title 
		//that is not "N/A") then asks the user to confirm the delete operation. If they do,
		//the book is deleted and the user is returned to the HomepageMenu() or else prints
		//an error message. If the book is not found (book returned by searchBook that has a
		//title "N/A"), then it prints an error message
		
		system("cls");
		cin >> b;
		Book r = v.searchBook(b);
		if(r.getTitle() != "N/A")
		{
			int delOption;
			cout << "Enter 1 if you would like to delete the following record: " << endl;
			cout << r << endl;
			cin >> delOption;
			if(delOption == 1)
			{
				v.removeBook(r);
				cout << "Thank you, the record has been deleted. Returning to the main menu." << endl;
				system("pause");
				HomepageMenu(v, b);
			}
			else
			{
				cout << "The delete operation could not be performed, please try again." << endl;
				system("pause");
				HomepageMenu(v, b);
				
			}
		}
		else
		{
			cout << "The book you entered was not found in the database. Please try again. " << endl;
			system("pause");
			HomepageMenu(v, b);
		}
	}
	else if(choice == 2)
	{
		//If the user chooses two, asks them to search the book by entering the book title,
		//if the book is found (the searchTitle function returns an actual book with a title 
		//that is not "N/A") then asks the user to confirm the delete operation. If they do,
		//the book is deleted and the user is returned to the HomepageMenu() or else prints
		//an error message. If the book is not found (book returned by searchTitle that has a
		//title "N/A"), then it prints an error message
		
		system("cls");
		string title;
		cout << "Please enter the title you wish to search: ";
		cin >> title;
		Book r = v.searchTitle(title);
		if(r.getTitle() != "N/A")
		{
			int delOption;
			cout << "Enter 1 if you would like to delete the following record: " << endl;
			cout << r << endl;
			cin >> delOption;
			if(delOption == 1)
			{
				v.removeBook(r);
				cout << "Thank you, the record has been deleted. Returning to the main menu." << endl;
				system("pause");
				HomepageMenu(v, b);
			}
			else
			{
				cout << "The delete operation could not be performed, please try again." << endl;
				system("pause");
				HomepageMenu(v, b);
				
			}
		}
		else
		{
			cout << "The title you entered was not found in the database. Please try again. " << endl;
			system("pause");
			HomepageMenu(v, b);
		}
	}
	else if(choice == 3)
	{
		//If the user chooses three, asks them to search the book by entering the book's author,
		//if the book is found (the searchAuthor function returns an actual book with an author 
		//that is not "N/A") then asks the user to confirm the delete operation. If they do,
		//the book is deleted and the user is returned to the HomepageMenu() or else prints
		//an error message. If the book is not found (book returned by searchAuthor that has an
		//author "N/A"), then it prints an error message
		
		system("cls");
		string author;
		cout << "Please enter the author you wish to search: ";
		cin >> author;
		Book r = v.searchAuthor(author);
		if(r.getAuthor() != "N/A")
		{
			int delOption;
			cout << "Enter 1 if you would like to delete the following record: " << endl;
			cout << r << endl;
			cin >> delOption;
			if(delOption == 1)
			{
				v.removeBook(r);
				cout << "Thank you, the record has been deleted. Returning to the main menu." << endl;
				system("pause");
				HomepageMenu(v, b);
			}
			else
			{
				cout << "The delete operation could not be performed, please try again." << endl;
				system("pause");
				HomepageMenu(v, b);
				
			}
		}
		else
		{
			cout << "The title you entered was not found in the database. Please try again. " << endl;
			system("pause");
			HomepageMenu(v, b);
		}
	}
	
}

void updateMenu(Database &v, Book &b)
{
	//The function takes a Database object and Book object by reference as parameters
	//Displays the search menu in order to ask the user how they would like to search for
	//the record
	
	system("cls");
	cout << "Please search a book that you want to modify from the database." << endl;
	cout << "Books can be searched in multpile ways: " << endl;
	cout << "\t1. You could search for a book(s) to update by entering the whole record." << endl;
	cout << "\t2. You could search for a book(s) to update by title. " << endl;
	cout << "\t3. You could search for a book(s) to update by the Author's name. " << endl;
	cout << "\tPlease enter a number corresponding to your choice: ";

	//Enter the users' choice and ensure it is within the range
	
	int choice;
	cout << "\t";
	cin >> choice;

	while(choice < 1 || choice > 3)
	{
		cout << "The number you entred was not part of the choice. Please try again. " << endl;
		cin >> choice;
	}

	if(choice == 1)
	{
		//If the user chooses one, asks them to search the book by entering all the details,
		//if the book is found (the searchBook function returns an actual book with a title 
		//that is not "N/A") then display a menu asking the user what modification they would like
		//to make. If the book is not found (book returned by searchBook that has a
		//title "N/A"), then it prints an error message

		cin >> b;
		Book r = v.searchBook(b);
		if(r.getTitle() != "N/A")
		{
			system("cls");
			int modOption;
			cout << "What information would you like to update on the following record: " << endl;
			cout << v.searchBook(b);
			cout << endl << "\t1. Update title. " << endl;
			cout << "\t2. Update author. " << endl;
			cout << "\t3. Update type. " << endl;
			cout << "\t4. Update publication date. " << endl;
			cout << "\t5. Update number of pages. " << endl;
			cout << "\tEnter the number of the option you choose: ";
			cin >> modOption;

			//Ensures the value the user entered are in the range required
			
			while(modOption < 1 || modOption > 5)
			{
				cout << "The number you entered is incorrect, please try again: ";
				cin >> modOption;
			}

			if(modOption == 1)
			{
				//If user selects one, asks the user for the new title then updates it
				//in the Database and prints the new record, followed by returning 
				//the user to the HomepageMenu()
				
				cout << "Please enter the new title of the book: ";
				string temp;
				cin >> temp;
				
				v.updateTitle(temp, r);

				cout << "Thank you, the record has been updated. Returning to the main menu. " << endl;
				cout << v.searchTitle(temp) << endl;
				system("pause");
				HomepageMenu(v, b);
			}
			else if(modOption == 2)
			{
				//If user selects two, asks the user for the new author then updates it
				//in the Database and prints the new record, followed by returning 
				//the user to the HomepageMenu()
				
				cout << "Please enter the new author of the book: ";
				string temp;
				cin >> temp;
				
				v.updateAuthor(temp, r);

				cout << "Thank you, the record has been updated. Returning to the main menu. " << endl;
				cout << v.searchAuthor(temp) << endl;
				system("pause");
				HomepageMenu(v, b);
			}
			else if(modOption == 3)
			{
				//If user selects three, asks the user for the type, ensures it is valid
				//then updates it in the Database and prints the new record, followed by  
				//returning the user to the HomepageMenu()
				
				cout << "Please enter the new type of the book (Hardcover, Softcover, Digital): ";
				string temp;
				cin >> temp;

				while(true)
				{
					if(temp == "Hardcover")
						break;
					else if(temp == "Softcover")
						break;
					else if(temp == "Digital")
						break;
					else
					{
						cout << "\tThe Type of book you entered is incorrect! Please re-enter the type of book. A book can be Hardcover, Softcover or Digital: ";
						cin >> temp;
					}
				}
				
				v.updateType(temp, r);

				cout << "Thank you, the record has been updated. Returning to the main menu. " << endl;
				cout << v.searchBook(r) << endl;
				system("pause");
				HomepageMenu(v, b);
			}
			else if(modOption == 4)
			{
				//If user selects four, asks the user for the date, ensures it is valid
				//then updates it in the Database and prints the new record, followed by  
				//returning the user to the HomepageMenu()
				
				cout << "Please enter the new publication date of the book: ";
				int temp;
				cin >> temp;

				while(temp < 0 || temp > 2020)
				{
					cout << "\Please Enter the Date of Publication. The date must be less than 2020 and greater than 0: ";
					cin >> temp;
				}
				
				v.updateDate(temp, r);

				cout << "Thank you, the record has been updated. Returning to the main menu. " << endl;
				cout << v.searchBook(r) << endl;
				system("pause");
				HomepageMenu(v, b);
			}
			else
			{
				//If user selects five, asks the user for the number of pages, ensures it is valid
				//then updates it in the Database and prints the new record, followed by  
				//returning the user to the HomepageMenu()
				
				cout << "Please enter the new number of pages of the book: ";
				int temp;
				cin >> temp;
				
				v.updatePages(temp, r);

				cout << "Thank you, the record has been updated. Returning to the main menu. " << endl;
				cout << v.searchBook(r) << endl;
				system("pause");
				HomepageMenu(v, b);
			}
		}
		else
		{
			cout << "The book you entered was not found in the database. Please try again. " << endl;
			system("pause");
			HomepageMenu(v, b);
		}
	}

	else if(choice == 2)
	{
		//If the user chooses two, asks them to search the book by entering the book title
		//if the book is found (the searchTitle function returns an actual book with a title 
		//that is not "N/A") then display a menu asking the user what modification they would like
		//to make. If the book is not found (book returned by searchBook that has a
		//title "N/A"), then it prints an error message

		system("cls");
		string temp;
		cout << "Please enter the title you would like to search: ";
		cin >> temp;
		Book r = v.searchTitle(temp);
		if(r.getTitle() != "N/A")
		{
			
			int modOption;
			cout << "What information would you like to update on the following record: " << endl;
			cout << v.searchTitle(temp);
			cout << endl << "\t1. Update title. " << endl;
			cout << "\t2. Update author. " << endl;
			cout << "\t3. Update type. " << endl;
			cout << "\t4. Update publication date. " << endl;
			cout << "\t5. Update number of pages. " << endl;
			cout << "\tEnter the number of the option you choose: ";
			cin >> modOption;

			//Ensures the value the user entered are in the range required
			
			while(modOption < 1 || modOption > 5)
			{
				cout << "The number you entered is incorrect, please try again: ";
				cin >> modOption;
			}

			if(modOption == 1)
			{
				//If user selects one, asks the user for the new title then updates it
				//in the Database and prints the new record, followed by returning 
				//the user to the HomepageMenu()
				
				cout << "Please enter the new title of the book: ";
				string temp;
				cin >> temp;
				
				v.updateTitle(temp, r);

				cout << "Thank you, the record has been updated. Returning to the main menu. " << endl;
				cout << v.searchTitle(temp) << endl;
				system("pause");
				HomepageMenu(v, b);
			}
			else if(modOption == 2)
			{
				//If user selects two, asks the user for the new author then updates it
				//in the Database and prints the new record, followed by returning 
				//the user to the HomepageMenu()
				
				cout << "Please enter the new author of the book: ";
				string temp;
				cin >> temp;
				
				v.updateAuthor(temp, r);

				cout << "Thank you, the record has been updated. Returning to the main menu. " << endl;
				cout << v.searchAuthor(temp) << endl;
				system("pause");
				HomepageMenu(v, b);
			}
			else if(modOption == 3)
			{
				//If user selects three, asks the user for the type, ensures it is valid
				//then updates it in the Database and prints the new record, followed by  
				//returning the user to the HomepageMenu()
				
				cout << "Please enter the new type of the book (Hardcover, Softcover, Digital): ";
				string temp;
				cin >> temp;

				while(true)
				{
					if(temp == "Hardcover")
						break;
					else if(temp == "Softcover")
						break;
					else if(temp == "Digital")
						break;
					else
					{
						cout << "\tThe Type of book you entered is incorrect! Please re-enter the type of book. A book can be Hardcover, Softcover or Digital: ";
						cin >> temp;
					}
				}
				
				v.updateType(temp, r);

				cout << "Thank you, the record has been updated. Returning to the main menu. " << endl;
				cout << v.searchBook(r) << endl;
				system("pause");
				HomepageMenu(v, b);
			}
			else if(modOption == 4)
			{
				//If user selects four, asks the user for the date, ensures it is valid
				//then updates it in the Database and prints the new record, followed by  
				//returning the user to the HomepageMenu()
				
				cout << "Please enter the new publication date of the book: ";
				int temp;
				cin >> temp;

				while(temp < 0 || temp > 2020)
				{
					cout << "\Please Enter the Date of Publication. The date must be less than 2020 and greater than 0: ";
					cin >> temp;
				}
				
				v.updateDate(temp, r);

				cout << "Thank you, the record has been updated. Returning to the main menu. " << endl;
				cout << v.searchBook(r) << endl;
				system("pause");
				HomepageMenu(v, b);
			}
			else
			{
				//If user selects five, asks the user for the number of pages, ensures it is valid
				//then updates it in the Database and prints the new record, followed by  
				//returning the user to the HomepageMenu()
				
				cout << "Please enter the new number of pages of the book: ";
				int temp;
				cin >> temp;
				
				v.updatePages(temp, r);

				cout << "Thank you, the record has been updated. Returning to the main menu. " << endl;
				cout << v.searchBook(r) << endl;
				system("pause");
				HomepageMenu(v, b);
			}
		}
		else
		{
			cout << "The book you entered was not found in the database. Please try again. " << endl;
			system("pause");
			HomepageMenu(v, b);
		}
	}
	else
	{
		//If the user chooses three, asks them to search the book by entering the book author
		//if the book is found (the searchAuthor function returns an actual book with an author 
		//that is not "N/A") then display a menu asking the user what modification they would like
		//to make. If the book is not found (book returned by searchAuthor that has a
		//title "N/A"), then it prints an error message

		system("cls");
		string temp;
		cout << "Please enter the author you would like to search: ";
		cin >> temp;
		Book r = v.searchAuthor(temp);
		if(r.getTitle() != "N/A")
		{
			
			int modOption;
			cout << "What information would you like to update on the following record: " << endl;
			cout << r;
			cout << endl << "\t1. Update title. " << endl;
			cout << "\t2. Update author. " << endl;
			cout << "\t3. Update type. " << endl;
			cout << "\t4. Update publication date. " << endl;
			cout << "\t5. Update number of pages. " << endl;
			cout << "\tEnter the number of the option you choose: ";
			cin >> modOption;

			//Ensures the value the user entered are in the range required
			
			while(modOption < 1 || modOption > 5)
			{
				cout << "The number you entered is incorrect, please try again: ";
				cin >> modOption;
			}

			if(modOption == 1)
			{
				//If user selects one, asks the user for the new title then updates it
				//in the Database and prints the new record, followed by returning 
				//the user to the HomepageMenu()
				
				cout << "Please enter the new title of the book: ";
				string temp;
				cin >> temp;
				
				v.updateTitle(temp, r);

				cout << "Thank you, the record has been updated. Returning to the main menu. " << endl;
				cout << v.searchTitle(temp) << endl;
				system("pause");
				HomepageMenu(v, b);
			}
			else if(modOption == 2)
			{
				//If user selects two, asks the user for the new author then updates it
				//in the Database and prints the new record, followed by returning 
				//the user to the HomepageMenu()
				
				cout << "Please enter the new author of the book: ";
				string temp;
				cin >> temp;
				
				v.updateAuthor(temp, r);

				cout << "Thank you, the record has been updated. Returning to the main menu. " << endl;
				cout << v.searchAuthor(temp) << endl;
				system("pause");
				HomepageMenu(v, b);
			}
			else if(modOption == 3)
			{
				//If user selects three, asks the user for the type, ensures it is valid
				//then updates it in the Database and prints the new record, followed by  
				//returning the user to the HomepageMenu()
				
				cout << "Please enter the new type of the book (Hardcover, Softcover, Digital): ";
				string temp;
				cin >> temp;

				while(true)
				{
					if(temp == "Hardcover")
						break;
					else if(temp == "Softcover")
						break;
					else if(temp == "Digital")
						break;
					else
					{
						cout << "\tThe Type of book you entered is incorrect! Please re-enter the type of book. A book can be Hardcover, Softcover or Digital: ";
						cin >> temp;
					}
				}
				
				v.updateType(temp, r);

				cout << "Thank you, the record has been updated. Returning to the main menu. " << endl;
				cout << v.searchBook(r) << endl;
				system("pause");
				HomepageMenu(v, b);
			}
			else if(modOption == 4)
			{
				//If user selects four, asks the user for the date, ensures it is valid
				//then updates it in the Database and prints the new record, followed by  
				//returning the user to the HomepageMenu()
				
				cout << "Please enter the new publication date of the book: ";
				int temp;
				cin >> temp;

				while(temp < 0 || temp > 2020)
				{
					cout << "\Please Enter the Date of Publication. The date must be less than 2020 and greater than 0: ";
					cin >> temp;
				}
				
				v.updateDate(temp, r);

				cout << "Thank you, the record has been updated. Returning to the main menu. " << endl;
				cout << v.searchBook(r) << endl;
				system("pause");
				HomepageMenu(v, b);
			}
			else
			{
				//If user selects five, asks the user for the number of pages, ensures it is valid
				//then updates it in the Database and prints the new record, followed by  
				//returning the user to the HomepageMenu()
				
				cout << "Please enter the new number of pages of the book: ";
				int temp;
				cin >> temp;
				
				v.updatePages(temp, r);

				cout << "Thank you, the record has been updated. Returning to the main menu. " << endl;
				cout << v.searchBook(r) << endl;
				system("pause");
				HomepageMenu(v, b);
			}
		}
		else
		{
			cout << "The book you entered was not found in the database. Please try again. " << endl;
			system("pause");
			HomepageMenu(v, b);
		}
	}
}

void searchMenu(Database &v, Book &b)
{
	//The function takes a Database object and Book object by reference as parameters
	//Displays the search menu in order to ask the user how they would like to search for
	//the record
	
	system("cls");
	cout << "What would you like to search? " << endl;
	cout <<"\t1. Search for entire book record." << endl;
	cout <<"\t2. Search by Title." << endl;
	cout <<"\t3. Search by Author." << endl;
	cout <<"\t4. Search by Type." << endl;
	cout <<"\t5. Search by Publication Date." << endl;
	cout <<"\t6. Search by Number of Pages." << endl;
	cout << "\tPlease enter your option: ";
	
	//Enter the users choice and ensure it is within the range
	
	int choice;
	cin >> choice;

	while(choice < 1 || choice > 6)
	{
		cout << "Your entry was invalid! Please try again: ";
		cin >> choice;
	}

	if(choice == 1)
	{
		//If the user chooses one, asks them to search the book by entering all the details
		//if the book is found (the searchBook function returns an actual book with a title 
		//that is not "N/A") then prints all the books found using searchAllBooks and the user 
		//is returned to the HomepageMenu(). If the book is not found (book returned by searchBook 
		//that has a title "N/A", then it prints an error message and returns to HomepageMenu()
		
		system("cls");
		cin >> b;
		
		Book a = v.searchBook(b);
		if(a.getTitle() == "N/A") 
		{
			cout << "No records were found that match your search entry." << endl; 
			system("pause");
			HomepageMenu(v, b);
		}
		else
		{
			v.searchAllBooks(b);
			system("pause");
			HomepageMenu(v, b);
		}
	}
	else if(choice == 2)
	{
		//If the user chooses two, asks them to search the book by entering book title
		//if the book is found (the searchTitle function returns an actual book with a title 
		//that is not "N/A") then prints all the books found using searchAllTitles and the user 
		//is returned to the HomepageMenu(). If the book is not found (book returned by searchTitle 
		//that has a title "N/A"), then it prints an error message and returns to HomepageMenu()
		
		system("cls");
		string temp;
		cout << "Please enter the title you wish to search: ";
		cin >> temp;
		
		Book a = v.searchTitle(temp);
		if(a.getTitle() == "N/A") 
		{
			cout << "No records were found that match your search entry." << endl; 
			system("pause");
			HomepageMenu(v, b);
		}
		else
		{
			v.searchAllTitles(temp);
			system("pause");
			HomepageMenu(v, b);
		}
	}
	else if(choice == 3)
	{
		//If the user chooses three, asks them to search the book by entering book author
		//if the book is found (the searchAuthor function returns an actual book with a author 
		//that is not "N/A") then prints all the books found using searchAllAuthors and the user 
		//is returned to the HomepageMenu(). If the book is not found (book returned by searchAuthor 
		//that has a author "N/A"), then it prints an error message and returns to HomepageMenu()
		
		system("cls");
		string temp;
		cout << "Please enter the name of the author you wish to search: ";
		cin >> temp;
		
		Book a = v.searchAuthor(temp);
		if(a.getAuthor() == "N/A") 
		{
			cout << "No records were found that match your search entry." << endl; 
			system("pause");
			HomepageMenu(v, b);
		}
		else
		{
			v.searchAllAuthors(temp);
			system("pause");
			HomepageMenu(v, b);
		}
	}
	else if(choice == 4)
	{
		//If the user chooses four, asks them to search the book by entering book type and ensures
		//validity, if the book is found (the searchType function returns an actual book with a type 
		//that is not "N/A") then prints all the books found using searchAllTypes and the user 
		//is returned to the HomepageMenu(). If the book is not found (book returned by searchType 
		//that has a type "N/A"), then it prints an error message and returns to HomepageMenu()
		
		system("cls");
		string temp;
		cout << "Please enter the type of book you wish to search: ";
		cin >> temp;
		
		while(true)
		{
			if(temp == "Hardcover")
				break;
			else if(temp == "Softcover")
				break;
			else if(temp == "Digital")
				break;
			else
			{
				cout << "\tThe Type of book you entered is incorrect! Please re-enter the type of book. A book can be Hardcover, Softcover or Digital: ";
				cin >> temp;
			}
		}
		
		Book a = v.searchType(temp);
		if(a.getType() == "N/A") 
		{
			cout << "No records were found that match your search entry." << endl; 
			system("pause");
			HomepageMenu(v, b);
		}
		else
		{
			v.searchAllTypes(temp);
			system("pause");
			HomepageMenu(v, b);
		}
	}
	else if(choice == 5)
	{
		//If the user chooses five, asks them to search the book by entering book date and ensures
		//validity, if the book is found (the searchDate function returns an actual book with a date 
		//that is not 0) then prints all the books found using searchAllDates and the user 
		//is returned to the HomepageMenu(). If the book is not found (book returned by searchDate 
		//that is 0), then it prints an error message and returns to HomepageMenu()
		
		system("cls");
		int temp;
		cout << "Please enter the year of publication you wish to search: ";
		cin >> temp;
		
		while(temp < 0 || temp > 2020)
		{	
			cout << "\tThe year you entered is incorrect! Please re-enter the type of publication year: ";
			cin >> temp;	
		}
		
		Book a = v.searchDate(temp);
		if(a.getDate() == 0) 
		{
			cout << "No records were found that match your search entry." << endl; 
			system("pause");
			HomepageMenu(v, b);
		}
		else
		{
			v.searchAllDates(temp);
			system("pause");
			HomepageMenu(v, b);
		}
	}
	else
	{
		//If the user chooses six, asks them to search the book by entering the book's number of pages and ensures
		//validity, if the book is found (the searchPage function returns an actual book with a page 
		//that is not 0) then prints all the books found using searchAllPages and the user 
		//is returned to the HomepageMenu(). If the book is not found (book returned by searchPage 
		//that is 0), then it prints an error message and returns to HomepageMenu()
		
		system("cls");
		int temp;
		cout << "Please enter the number of pages you wish to search: ";
		cin >> temp;
		
		while(temp < 0)
		{	
			cout << "\tThe number of pages you entered is incorrect! Please re-enter the number of pages: ";
			cin >> temp;	
		}
		
		Book a = v.searchPages(temp);
		if(a.getPages() == 0) 
		{
			cout << "No records were found that match your search entry." << endl; 
			system("pause");
			HomepageMenu(v, b);
		}
		else
		{
			v.searchAllPages(temp);
			system("pause");
			HomepageMenu(v, b);
		}
	}
}

void inputMenu(Database &v, Book &b)
{
	//The function takes a Database object and Book object by reference as parameters
	//Asks the user to confirm the file input, each line is appended to the Database 
	//if they do, file is input. Then asks the user whether they would like to see the 
	//input fill printed, if they confirm print the Database input, followed by returning 
	//to the HomepageMenu, or else they return to the HomepageMenu()

	system("cls");
	cout << "Confirm input of database called Database.txt? Press 1 to confirm. ";
	int choice;
	cin >> choice;

	if(choice == 1)
	{
		ifstream fin;
		fin.open("Database.txt");
		if(fin.fail())
		{
			cout << "The databse input failed. Returning to main menu." << endl;
			system("pause");
			HomepageMenu(v, b);
		}
			
		string title, author, type;
		int date, pages;
			
		while(fin.eof() == false)
		{
			fin >> title >> author >> date >> type >> pages;
			b.setTitle(title);
			b.setAuthor(author);
			b.setDate(date);
			b.setType(type);
			b.setPages(pages);
			v.newBook(b);
		}
		
		int choice;
		cout << "The file has been input into the database. Press 1 to print and view the database. ";
		cin >> choice;
		cout << endl;

		if(choice == 1)
		{
			v.print();
			cout << endl << "Returning to main menu. " << endl;
			system("pause");
			HomepageMenu(v, b);
		}	
		else
		{			
			cout << "Returning to main menu." << endl;
			system("pause");
			HomepageMenu(v, b);
		}
		fin.close();
	}
	else
	{
		cout << "Returning to main menu. " << endl;
		system("pause");
		HomepageMenu(v, b);
	}
}

void outputMenu(Database &v, Book &b)
{
	//The function takes a Database object and Book object by reference as parameters
	
	system("cls");
	cout << "The database can be saved to the file MyDataBase.txt in two ways: " << endl;
	cout << "\t1. Overwrite the file MyDataBase.txt. " << endl;
	cout << "\t\t(Warning this will erase all data in the database and replace it with the new data) " << endl;
	cout << "\t2. Add the new data to the already existing database in the file MyDataBase.txt." << endl;
	cout << "\t\t(The appended data will not be sorted alphabetically by title)" << endl;
	cout << "\tPlease enter your option: ";
	int choice;
	cin >> choice;

	//Enter the users choice and ensure it is within the range
	
	while(choice < 1 || choice > 2)
	{
		cout << "Invalid entry! Please try again: ";
		cin >> choice;
	}

	//If user selects one, then the database is updated by constructing a new textfile with the new data
	//or else the data is appended to the existing text document
	
	if(choice == 1)
	{
		ofstream fout("MyDataBase.txt");
		if(fout.fail())
		{
			cout << "The databse output failed. Returning to main menu." << endl;
			system("pause");
			HomepageMenu(v, b);
		}

		for(int i = 0; i < v.getSize(); i++)
			fout << v.outputData(i) << endl;
		
		fout.close();
		cout << "The file MyDataBase.txt has been updated. Returning to main menu." << endl;
		system("pause");
		HomepageMenu(v,b);
	}
	else
	{
		ofstream fout("MyDataBase.txt", ios::app);
		if(fout.fail())
		{
			cout << "The databse output failed. Returning to main menu." << endl;
			system("pause");
			HomepageMenu(v, b);
		}

		for(int i = 0; i < v.getSize(); i++)
			fout << v.outputData(i) << endl;
		
		fout.close();
		cout << "The file MyDataBase.txt has been updated. Returning to main menu." << endl;
		system("pause");
		HomepageMenu(v,b);
	}
}


int main()
{
	//Create a default Database and Book pass them as parameters to HomepageMenu
	Database v;
	Book b;
	HomepageMenu(v, b);
}