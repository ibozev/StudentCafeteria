/*
 * menu_manager.cpp
 *
 *  Created on: Nov 18, 2018
 *      Author: bozev21
 */
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "Account.h"
#include "Student.h"
#include "Teacher.h"
#include "Product.h"
#include "Drink.h"
#include "Meal.h"
#include "Order.h"
#include "menu_manager.h"

using namespace std;

const string fileAcc = "Accounts.txt";
const string fileProd = "Products.txt";
const string fileMenu = "Menu.txt";
const string fileOrders = "Orders.txt";

namespace menu_manager {

	//anonymous namespace(private)
	namespace {
		//case-insensitive string comparison
		bool caseInSensStringCompare(string &str1, string &str2) {
			return ((str1.size() == str2.size()) && std::equal(str1.begin(),
						str1.end(), str2.begin(), [](char & c1, char & c2)
							{
								return (c1 == c2 || std::toupper(c1) == std::toupper(c2));
							}));
		}

		template <class T>
		void clearVector(vector<T*> &vect) {
			for (typename vector<T*>::iterator it = vect.begin(); it != vect.end(); ++it)
				delete (*it);
			vect.clear();
		}

		//used only for daily menu
		template <class T>
		void sortVector(vector<T*> &vect) {

			std::sort(vect.begin(), vect.end(), []( T* obj1, T* obj2 ) -> bool
			{
			   return obj1->getId() < obj2->getId();
			});
		}

		template <class T>
		void printBorder() {
		}

		//template specialization
		template <>
		void printBorder<Account>() {
			cout << "Account type\t" << "Date of register\t" << "Id\t" << "Owner name\t\t"
					<< "Discount\t" << "Faculty number" << endl;
			for (int i = 0; i < 103; i++)
				cout << "-";
			cout << endl;
		}

		//template specialization
		template <>
		void printBorder<Product>() {
			cout << "Product type\t" << "Id\t" << "Product name\t\t"
					<< "Volume/Weight\t" << "Price" << endl;
			for (int i = 0; i < 103; i++)
				cout << "-";
			cout << endl;
		}

		template <>
		void printBorder<Order>() {
			cout << "Date of order\t" << "Account owner name/faculty number\t"
					<< "Order price" << endl;
			for (int i = 0; i < 103; i++)
				cout << "-";
			cout << endl;
		}

		template <class T>
		void saveToFile(vector<T*> &vect, const string fileName) {
			ofstream outf;

			outf.open(fileName.c_str());

			if (!outf) {
				cerr << "File "<< fileName << " cannot be opened for writing!" << endl;
				std::exit(1);
			}

			for (auto obj : vect)
				outf << (*obj) << endl;

			outf.close();
		}

		void loadFromFile(vector<Account*> &vectAcc){
			ifstream inf(fileAcc, ios::in);

			//if file is empty
			if (inf.peek() == fstream::traits_type::eof())
				return;

			if (!inf) {
				cerr << "File " << fileAcc << " cannot be opened for reading!" << endl;
				std::exit(2);
			}

			int tempType;
			Account *ptrAcc = NULL;

			while (inf >> tempType) {
				Account::AccType accType = static_cast<Account::AccType>(tempType);
				if (accType == Account::AccType::STUDENT) {
					ptrAcc = new Student;
					inf >> (*ptrAcc);
					vectAcc.push_back(ptrAcc);
				}
				else {
					ptrAcc = new Teacher;
					inf >> (*ptrAcc);
					vectAcc.push_back(ptrAcc);
				}
			}
			inf.close();
		}

		//тук има параметър за файл, понеже функцията се използва и за работа с vectMenu
		void loadFromFile(vector<Product*> &vect, const string fileName){
			ifstream inf(fileName, ios::in);

			if (inf.peek() == fstream::traits_type::eof())
				return;

			if (!inf) {
				cerr << "File " << fileName << " cannot be opened for reading!" << endl;
				std::exit(3);
			}

			int tempType;
			Product *ptrProd = NULL;

			while (inf >> tempType) {
				Product::ProdType prodType = static_cast<Product::ProdType>(tempType);
				if (prodType == Product::ProdType::DRINK) {
					ptrProd = new Drink;
					inf >> (*ptrProd);
					vect.push_back(ptrProd);
				}
				else {
					ptrProd = new Meal;
					inf >> (*ptrProd);
					vect.push_back(ptrProd);
				}
			}
			inf.close();
		}

		void loadFromFile(vector<Order*> &vectOrders) {
			ifstream inf(fileOrders, ios::in);

			//if file is empty
			if (inf.peek() == fstream::traits_type::eof())
				return;

			if (!inf) {
				cerr << "File " << fileOrders << " cannot be opened for reading!" << endl;
				std::exit(4);
			}

			Order *ptrOrder;
			while (true) {
				ptrOrder = new Order();
				try {
					inf >> (*ptrOrder);
					if (inf.eof())
						break;
				} catch (std::invalid_argument &e) {
					cerr << "Error reaching EOF!!" << endl;
				}
				vectOrders.push_back(ptrOrder);
			}
		}

		//for string (name or faculty number)
		template <class T>
		typename vector<T*>::iterator findObj(vector<T*> &vect, string str) {
			//iterator
			auto it = std::find_if(vect.begin(), vect.end(), [&str](const T* obj)
					{
						string str2 = obj->getName();
						return caseInSensStringCompare(str, str2);
					});

			return it;
		}

		//for int (id)
		template <class T>
		typename vector<T*>::iterator findObj(vector<T*> &vect, int id) {
			//iterator
			auto it = std::find_if(vect.begin(), vect.end(), [&id](const T* obj)
					{
						return (id == obj->getId());
					});
			return it;
		}

		template <class T>
		void exitVector(vector<T*> &vect, const string fileName) {
			saveToFile(vect, fileName);
			clearVector(vect);
		}

		template <class T>
		void printVector(vector<T*> &vect) {
			if (vect.empty()) {
				printBorder<T>();
				cout << "List is empty!" << endl << endl;
				return;
			}
			printBorder<T>();
			for (auto obj : vect)
				obj->printInfo();
			cout << endl;
		}

		bool isExistAcc(vector<Account*> &vect, const string nameOrNum) {
			try {
				auto it = findObj(vect, nameOrNum);

				if (it != vect.end()) {
					cout << "Account was successfully found! Details: " << endl;
					printBorder<Account>();
					(*it)->printInfo();
					return true;
				}
				else
					throw std::invalid_argument("Account doesn't exist!");
			}
			catch (std::invalid_argument &exc) {
				cerr << exc.what() << endl;
				return false;
			}
		}

		void addNewAccount(vector<Account*> &vect) {
			string name;
			int tempType;
			bool condition = true;

			//set type (student or teacher)
			while(condition) {
				cout << "Choose account type. Press 1 for student and 2 for teacher." << endl;
				try {
					cin >> tempType;
					if (tempType != 1 && tempType != 2)
						throw std::invalid_argument("Incorrect account type!");
					condition = false;
				}
				catch(std::invalid_argument &exc) {
					cerr << exc.what() << endl;
				}
			}

			condition = true;

			if (tempType == 1) {
				string fNum;

				while (condition) {
					cout << "Enter faculty number(9 digits): " << endl;
					try {
						cin >> fNum;
						if (fNum.length() != 9)
							throw std::invalid_argument("Faculty number isn't 9 digits!");

						auto position = findObj(vect, fNum);
						if (position != vect.end()) // means the element was found
							throw std::invalid_argument("Student with this "
									"faculty number exist already!");
						condition = false;
					}
					catch(std::invalid_argument &exc) {
						cerr << exc.what() << endl;
					}
				}
				cin.ignore();
				cout << "Enter student's name: " << endl;
				getline(std::cin, name);

				Account::AccType studentType = static_cast<Account::AccType>(tempType-1);
				Student *student = new Student(studentType, name, fNum);
				cout << "You successfully added a new student with details:" << endl;
				printBorder<Account>();
				student->printInfo();
				cout << endl;
				vect.push_back(student);
			}
			else {
				cin.ignore();

				while (condition) {
					cout << "Enter teacher's name: " << endl;
					try {
						getline(std::cin, name);
						auto position = findObj(vect, name);
						if (position != vect.end()) // means the element was found
							throw std::invalid_argument("Teacher with this name exist already!");
						condition = false;
					}
					catch(std::invalid_argument &exc) {
						cerr << exc.what() << endl;
					}
				}
				Account::AccType teacherType = static_cast<Account::AccType>(tempType-1);
				Teacher *teacher = new Teacher(teacherType, name);
				cout << "You successfully added a new teacher with details:" << endl;
				printBorder<Account>();
				teacher->printInfo();
				cout << endl;
				vect.push_back(teacher);
	//			cin.ignore();
			}
		}

		void addNewProduct(vector<Product*> &vect) {
			string name;
			int tempType;
			double price;
			bool condition = true;

			//set type (drink or meal)
			while(condition) {
				cout << "Choose product type. Press 1 for drink and 2 for meal." << endl;
				try {
					cin >> tempType;
					if (tempType != 1 && tempType != 2)
						throw std::invalid_argument("Incorrect product type!");
					condition = false;
				}
				catch(std::invalid_argument &exc) {
					cerr << exc.what() << endl;
				}
			}

			cin.ignore();
			condition = true;

			if (tempType == 1) {
				double volume;

				while (condition) {
					cout << "Enter drink's name: " << endl;
					try {
						getline(std::cin, name);
						auto position = findObj(vect, name);
						if (position != vect.end()) // means the element was found
							throw std::invalid_argument("Drink with this name exist already!");
						condition = false;
					}
					catch(std::invalid_argument &exc) {
						cerr << exc.what() << endl;
					}
				}

				cout << "Enter drink's volume (in liters): " << endl;
				cin >> volume;

				cout << "Enter drink's price (in leva): " << endl;
				cin >> price;

				Product::ProdType drinkType = static_cast<Product::ProdType>(tempType-1);
				Drink *drink = new Drink(drinkType, name, price, volume);
				cout << "You successfully added a new drink with details:" << endl;
				printBorder<Product>();
				drink->printInfo();
				cout << endl;
				vect.push_back(drink);
			}
			else {
				double weight;

				while (condition) {
					cout << "Enter meal's name: " << endl;
					try {
						getline(std::cin, name);
						auto position = findObj(vect, name);
						if (position != vect.end()) // means the element was found
							throw std::invalid_argument("Meal with this name exist already!");
						condition = false;
					}
					catch(std::invalid_argument &exc) {
						cerr << exc.what() << endl;
					}
				}
				cout << "Enter meal's weight (in grams): " << endl;
				cin >> weight;

				cout << "Enter meal's price (in leva): " << endl;
				cin >> price;

				Product::ProdType mealType = static_cast<Product::ProdType>(tempType-1);
				Meal *meal = new Meal(mealType, name, price, weight);
				cout << "You successfully added a new meal with details:" << endl;
				printBorder<Product>();
				meal->printInfo();
				cout << endl;
				vect.push_back(meal);
	//			cin.ignore();
			}
		}

		void addNewOrder(vector<Account*> &vectAcc,
				vector<Order*> &vectOrders)
		{
			/*vectMenu e definiran tuk, zashtoto ako sme promenqli dnevnoto menu predi tova
			 	 to shte trqbwa pak da prochetem fileMenu*/
			vector<Product*> vectMenu;
			vector<string> products;
			string numOrName, lineOfNums;
			double discount, wholePrice = 0, finalPrice;
			int id;

			cout << "Making a new order." << endl;
			cout << "Enter account's faculty number for student or name for teacher: " << endl;
			getline(cin, numOrName);

			if (!isExistAcc(vectAcc, numOrName))
				return;
			cout << endl;

			//check for white spaces => name or faculty number
			if(numOrName.find_first_of(' ') != std::string::npos)
				discount = 20.00; //teacher
			else
				discount = 30.00; //student

			cout << "Choose which products you want to add to your order." << endl;
			cout << "Enter ids separated by spaces: " << endl;
			cout << "                                   Daily Menu" << endl;
			loadFromFile(vectMenu, fileMenu);
			sortVector(vectMenu);
			printVector(vectMenu);

			getline(cin, lineOfNums);
			std::istringstream stream(lineOfNums);
			while (stream >> id) {
				try {
					auto it = findObj(vectMenu, id);
					if (it != vectMenu.end()) {
						products.push_back((*it)->getName());
						wholePrice += (*it)->getPrice();
					}
					else
						throw std::invalid_argument(" doesn't exist!");
				}
				catch (std::invalid_argument &exc) {
					cerr << "Product with  id " << id << exc.what() << endl;
					//oder selected products will be added to the order anyway
				}
			}
			cout << "You successfully added a new order with details:" << endl;

			finalPrice = wholePrice - ((discount/100) * wholePrice);
			Order *ptrOrder = new Order(numOrName, products, finalPrice);
			vectOrders.push_back(ptrOrder);
			ptrOrder->printInfo();
			cout << endl;
			clearVector(vectMenu);
		}

		//for accounts and products; orders cannot be removed
		template <class T>
		void removeItem(vector<T*> &vect) {
			int delId;

			if (vect.empty()) {
				cout << "Chosen list is empty!" << endl;
				return;
			}

			cout << "Enter object's id, which you want to remove from a list below: "<<endl<<endl;
			printVector(vect);

			try {
				cin >> delId;
				auto position = findObj(vect, delId);

				if (position != vect.end()) {// means the element was found
					vect.erase(position);
					cout << "Object was successfully deleted!" << endl << endl;
				}
				else
					throw std::invalid_argument("Chosen id doesn't exist!");
			}
			catch (std::invalid_argument &exc) {
				cerr << exc.what() << endl;
			}
			cin.ignore();
		}

		//Accounts cannot be edited
		void editProduct(vector<Product*> &vect) {
			int chosenId;
			double newValue, newPrice;

			if (vect.empty()) {
				cout << "There is no products!" << endl;
				return;
			}

			cout << endl << "Enter product's id, which you want to edit from a list below: "
					<< endl << endl;
			sortVector(vect);
			printVector(vect);

			try {
				cin >> chosenId;
				auto position = findObj(vect, chosenId);

				if (position != vect.end()) {// means the element was found
					cout << "Enter new product's volume/weight (in liters/grams): " << endl;
					cin >> newValue;
					//pointer to pointer
					(*position)->setNewValue(newValue);

					cout << "Enter new product's price: " << endl;
					cin >> newPrice;
					(*position)->setNewPrice(newPrice);
					cout << "Object was successfully edited!" << endl << endl;
				}
				else
					throw std::invalid_argument("Chosen id doesn't exist!");
			}
			catch (std::invalid_argument &exc) {
				cerr << exc.what() << endl;
			}
	//		cin.ignore();
		}

		void createDailyMenu(vector<Product*> &vectProd) {
			ofstream outf(fileMenu.c_str());
			string lineOfNums;
			int id;

			if (vectProd.empty()) {
				cout << "There is no products to add in the daily menu!" << endl;
				return;
			}

			if (!outf) {
				cerr << "File "<< fileMenu << " cannot be opened for writing!" << endl;
				std::exit(1);
			}

			cout << "Choose which products you want to add to today's daily menu." << endl;
			cout << "Enter ids separated by spaces: " << endl;
			printVector(vectProd);

			getline(cin, lineOfNums);
			std::istringstream stream(lineOfNums);
			while (stream >> id) {
				try {
					auto it = findObj(vectProd, id);
					if (it != vectProd.end())
						outf << (**it) << endl;
					else
						throw std::invalid_argument(" doesn't exist!");
				}
				catch (std::invalid_argument &exc) {
					cerr << "Product with  id " << id << exc.what() << endl;
					//other products will be added to menu anyway
				}
				catch (exception &exc) {
					cerr << "Error occurred while creating daily menu!" << endl;
					return;
				}
			}
			cout << "Daily menu was successfully created!" << endl << endl;
			outf.close();
		}

		/*не проверявам за дубликати, възможно е да се добави повтарящ се продукт,
		 	 след което да се редактира в менюто и така да имаме два продукта но
		 	 примерно с различно тегло и цена*/
		//vectMenu<*> защото всички функции работят с вектори от указатели
		void editDailyMenu(vector<Product*> &vectProd) {
			ofstream outf;
			int choice;
			bool isEdited = false;
			vector<Product*> vectMenu;

			loadFromFile(vectMenu, fileMenu);

			cout << "Press 1 to add Product in daily menu." << endl;
			cout << "Press 2 to remove Product from menu." << endl;
			cout << "Press 3 to edit Product from menu." << endl;

			try {
				cin >> choice;
				switch(choice) {
					case 1:
						cin.ignore();
						createDailyMenu(vectProd);
						isEdited = true;
						break;
					case 2:
						if (vectMenu.empty())
							cout << "Menu is empty!" << endl;
						else
							removeItem(vectMenu);
						break;
					case 3:
						if (vectMenu.empty())
							cout << "Menu is empty!" << endl;
						else
							editProduct(vectMenu);
						break;
					default:
						throw std::invalid_argument("Incorrect number!");
				}
			}
			catch (std::invalid_argument &exc) {
				cerr << exc.what() << endl;
			}

			if (isEdited)
				outf.open(fileMenu.c_str(), ios_base::app);
			else
				outf.open(fileMenu.c_str());

			if (!outf) {
				cerr << "File "<< fileMenu << " cannot be opened for write/append!" << endl;
				std::exit(1);
			}

			for (auto obj : vectMenu)
				outf << (*obj) << endl;

			clearVector(vectMenu);
			outf.close();
		}

		void printDailyMenu() {
			vector<Product*> vectMenu;

			cout << "                                   Daily Menu" << endl;
			loadFromFile(vectMenu, fileMenu);
			sortVector(vectMenu);
			printVector(vectMenu);
			clearVector(vectMenu);
		}

		void showAccOrders(vector<Account*> &vectAcc, vector<Order*> &vectOrders) {
			string numOrName/*, ownerName*/;
			int count = 0;

			getline(cin, numOrName);

			if (!isExistAcc(vectAcc, numOrName))
				return;

			cout <<endl<<endl<<"List with all orders from account: "<<numOrName<<endl<<endl;
			printBorder<Order>();
			for (auto it = vectOrders.begin(); it != vectOrders.end(); it++) {
				string ownerName = (*it)->getOwnerName();
				if (caseInSensStringCompare(ownerName, numOrName)) {
					(*it)->printInfo();
					count++;
				}
			}
			if (count == 0)
				cout << "This account has no orders already!" << endl;
		}

		void printHelp(){
			cout << "'1' -> add new account - student or teacher" << endl;
			cout << "'2' -> add new product - drink or meal" << endl;
			cout << "'3' -> add new order" << endl;
			cout << "'4' -> remove account by ID" << endl;
			cout << "'5' -> remove product by ID" << endl;
			cout << "'6' -> edit product by ID" << endl;
			cout << "'7' -> print all registered accounts" << endl;
			cout << "'8' -> print all products" << endl;
			cout << "'9' -> print all orders" << endl;
			cout << "'10' -> check by faculty number if the student is registered" << endl;
			cout << "'11' -> check by name if the teacher is registered" << endl;
			cout << "'12' -> create new daily menu" << endl;
			cout << "'13' -> edit existing daily menu" << endl;
			cout << "'14' -> print daily menu" << endl;
			cout << "'15' -> print all orders to a particular student" << endl;
			cout << "'16' -> print all orders to a particular teacher" << endl;
			cout << "'17' -> exit from the program" << endl;
		}
	}


	void fillUpVectors(vector<Account*> &vectAcc,
			vector<Product*> &vectProd, vector<Order*> &vectOrders)
	{
		loadFromFile(vectAcc);
		loadFromFile(vectProd, fileProd);
		loadFromFile(vectOrders);
	}

	void exit(vector<Account*> &vectAcc,
			vector<Product*> &vectProd, vector<Order*> &vectOrders)
	{
		exitVector(vectAcc, fileAcc);
		exitVector(vectProd, fileProd);
		exitVector(vectOrders, fileOrders);
	}

	void userInterface(std::vector<Account*> &vectAcc,
			std::vector<Product*> &vectProd, std::vector<Order*> &vectOrders)
	{
		int command;
		string numOrName;

		cout << "Press '0' for help." << endl;
		while(command != 17){
			while(true) {
				cout << endl <<"It is main menu." << endl << "command > ";
				try {
					cin >> command;
					if (cin.fail())
						throw std::invalid_argument("Incorrect input!");
					break;
				}
				catch(exception &exc) {
					cin.clear();
					cin.ignore();
					cerr << exc.what() << endl;
				}
			}

			switch(command) {
				case(17):
					cout << "Exiting..." << endl;
					break;
				case(0):
					printHelp();
					break;
				case(1):
					addNewAccount(vectAcc);
					break;
				case(2):
					addNewProduct(vectProd);
					break;
				case(3):
					cin.ignore();
					addNewOrder(vectAcc, vectOrders);
					break;
				case(4):
					cout << "Removing account by id!" << endl;
					removeItem(vectAcc);
					break;
				case(5):
					cout << "Removing product by id!" << endl;
					removeItem(vectProd);
					break;
				case(6):
					editProduct(vectProd);
					break;
				case(7):
					printVector(vectAcc);
					break;
				case(8):
					printVector(vectProd);
					break;
				case(9):
					printVector(vectOrders);
					break;
				case(10):
					cin.ignore();
					cout << "Enter student's faculty number!" << endl;
					getline(cin, numOrName);
					isExistAcc(vectAcc, numOrName);
					break;
				case(11):
					cin.ignore();
					cout << "Enter teacher's name!" << endl;
					getline(cin, numOrName);
					isExistAcc(vectAcc, numOrName);
					break;
				case(12):
					cin.ignore();
					createDailyMenu(vectProd);
					break;
				case(13):
					editDailyMenu(vectProd);
					break;
				case(14):
					printDailyMenu();
					break;
				case(15):
					cout << "Enter student's faculty number: " << endl;
					cin.ignore();
					showAccOrders(vectAcc, vectOrders);
					break;
				case(16):
					cout << "Enter teacher's name: " << endl;
					cin.ignore();
					showAccOrders(vectAcc, vectOrders);
					break;
				default:
					cout << "Invalid command!" << endl << endl;
			}
		}
	}

	//explicit template instantiation
    template void printVector<Account>(vector<Account*> &vect);
    template void printVector<Product>(vector<Product*> &vect);
    template void printVector<Order>(vector<Order*> &vect);

    template void exitVector<Account>(vector<Account*> &vect, const string fileName);
    template void exitVector<Product>(vector<Product*> &vect, const string fileName);
    template void exitVector<Order>(vector<Order*> &vect, const string fileName);

    template void removeItem<Account>(vector<Account*> &vect);
    template void removeItem<Product>(vector<Product*> &vect);
};

