#include <iostream>
#include <conio.h>

using namespace std;

struct node
{
	int key_value;
	node *left;
	node *right;
} *newNode, *root = NULL, *current, *current2, *pre, *temp;

void MainMenu();
void insert();
void search();
void modifyData();
void deleteNode();
void preorder(node*);
void inorder(node*);
void postorder(node*);
void displayPath(node*);
void displayAllParents(node*);
void displayAllTerminals(node*);
void display(node*);
void findSmallest(node*);
void findLargest(node*);
void findParent(node*);
void countNodes(node*, int&);
int sumNodes(node*);
void goBack();

void main()
{

	MainMenu();
	
	cout << endl;
	system("pause");
}

void MainMenu()
{
	system("CLS");
	cout << "\n\n1. Create Nodes in the Tree\n2. Search in the Tree\n3. Modify data in a node in the Tree\n4. Delete node in the Tree\n5. Display\n6. Smallest number in the Tree\n7. Largest number in the Tree\n8. Find parent node\n9. Count nodes\n10. Sum of all nodes\n11. Exit\n\nEnter your choice:\n";
	char ch = _getche();
	switch (ch)
	{
	case '1':
	{
		insert();
		break;
	}
	case '2':
	{
		search();
		break;
	}
	case  '3':
	{
		modifyData();
		break;
	}
	case  '4':
	{
		deleteNode();
		break;
	}
	case  '5':
	{
		display(root);
		break;
	}
	case  '6':
	{
		findSmallest(root);
		break;
	}
	case  '7':
	{
		findLargest(root);
		break;
	}
	case  '8':
	{

		findParent(root);
		break;
	}
	case  '9':
	{
		int count = 0;
		countNodes(root, count);
		cout << "Total nodes in Tree: " << count;
		break;
		
	}
	case  '10':
	{
		cout << "Sum of all nodes in Tree: " << sumNodes(root);
		break;
		
	}
	case '11':
		exit(0);
	default:
		cout << "\aWRONG ENTRY!!!";
	}
}
void insert()
{
	system("CLS");
	int value;
	newNode = new node;
	cout << "Enter value: ";
	cin >> value;
	newNode->key_value = value;
	newNode->left = NULL;
	newNode->right = NULL;

	if (root == NULL)
	{
		root = newNode;
		cout << "Root node is added!\n";
	}
	else if (root->left == NULL && value < root->key_value)
	{
		root->left = newNode;
		cout << "Root left child is added!\n";
	}
	else if (root->right == NULL && value > root->key_value)
	{
		root->right = newNode;
		cout << "Root right child is added\n";
	}
	else
	{
		if (value < root->key_value)
			current = root->left;
		else
			current = root->right;

		while (current != NULL)
		{
			pre = current;
			if (value > current->key_value)
			{
				current = current->right;
			}
			else
			{
				current = current->left;
			}
		}
		if (value > pre->key_value)
		{
			pre->right = newNode;
			cout << "Right child is added\n";
		}
		else
		{
			pre->left = newNode;
			cout << "Left child is added\n";
		}
	}

	cout << "\n\nPress ENTER to add more or ESCAPE to go back to Main Menu.\n";
	char ch = _getch();
	if (ch == 13)
		insert();
	else if (ch == 27)
		MainMenu();
	else
		cout << "\n\aWrong entry!!!";
}
void deleteNode()
{
	system("CLS");
	cout << "Enter node data of which you wanna delete: ";
	int value;
	cin >> value;

	bool check = false;

	if (root == NULL)
	{
		cout << "Tree is empty!\n";
	}
	else
	{
		current = root;

		while (current != NULL)
		{

			if (current->key_value == value)
			{
				check = true;
				break;
			}

			pre = current;

			if (value < current->key_value)
			{
				current = current->left;
			}
			else if (value > current->key_value)
				current = current->right;
		}
	}

	if (check)
	{
		cout << value << " is found\n\n";

		if (current->left==NULL && current->right==NULL)
		{
			if (current==root)
			{
				delete current;
				root = NULL;
			}
			else if (pre->left == current)
			{
				temp = current;
				pre->left = NULL;
				delete temp;
			}
			else if (pre->right == current)
			{
				temp = current;
				pre->right = NULL;
				delete temp;
			}
		}
		else if (current->left!=NULL && current->right==NULL)
		{
			temp = current;
			pre->left = current->left;
			delete current;
		}
		else if (current->right != NULL && current->left == NULL)
		{
			temp = current;
			pre->right = current->right;
			delete current;
		}
		else
		{
			current2 = current->right;
			while (current2->left!=NULL)
			{
				pre = current2;
				current2 = current2->left;
			}

			current->key_value = current2->key_value;
			temp = current2;
			pre->left = NULL;
			delete temp;
		}

		cout << value << " is deleted!";
	}
	else
	{
		cout << "\n\a" << value << " is not in the Tree!";
	}

	cout << "\n\nPress ENTER to delete more or ESCAPE to go back to Main Menu.\n";
	char ch = _getch();
	if (ch == 13)
		deleteNode();
	else if (ch == 27)
		MainMenu();
	else
		cout << "\n\aWrong entry!!!";
	MainMenu();
}
void search()
{
	system("CLS");
	cout << "Enter node data which you wanna search: ";
	int value;
	cin >> value;

	bool check = false;
	
	if (root == NULL)
	{
		cout << "Tree is empty!\n";
	}
	/*else if (root->key_value == value)
	{
		check = true;
	}
	else if (root->left->key_value == value)
	{
		check = true;
	}
	else if (root->right->key_value == value)
	{
		check = true;
	}
	else
	{
		if (value < root->key_value)
			current = root->left;
		else
			current = root->right;
		
		cout << current;

		while (current != NULL)
		{
			pre = current;
			if (value > current->key_value)
			{
				
				if (current->key_value == value)
				{
					check = true;
				}
				current = current->right;
				
			}
			else
			{
				current = current->left;
				if (pre->key_value == value)
				{
					check = true;
				}
				
			}
		}
	}*/
	else
	{
		current = root;

		while(current!=NULL)
		{
			if (current->key_value==value)
			{
				check = true;
				break;
			}

			if (value < current->key_value)
			{
				current = current->left;
			}
			else if(value > current->key_value)
				current = current->right;
		}
	}

	if (check)
	{
		cout << value << " is found"; 
	}
	else
		cout << "\n\a" << value << " is not in the Tree!";

	cout << "\n\nPress ENTER to search more or ESCAPE to go back to Main Menu.\n";
	char ch = _getch();
	if (ch == 13)
		search();
	else if (ch == 27)
		MainMenu();
	else
		cout << "\n\aWrong entry!!!";
	MainMenu();
}
void modifyData()
{
	system("CLS");
	cout << "Enter node data which you wanna modify: ";
	int value;
	cin >> value;

	bool check = false;

	if (root == NULL)
	{
		cout << "Tree is empty!\n";
	}
	else
	{
		current = root;

		while (current != NULL)
		{
			if (current->key_value == value)
			{
				check = true;
				break;
			}

			if (value < current->key_value)
			{
				current = current->left;
			}
			else if (value > current->key_value)
				current = current->right;
		}
	}

	if (check)
	{
		cout << value << " is found\n\n";

		cout << "Enter new data: ";
		cin >> current->key_value;

		cout << "\nModified Successfully!";
	}
	else
		cout << "\n\a" << value << " is not in the Tree!";

	cout << "\n\nPress ENTER to modify more data or ESCAPE to go back to Main Menu.\n";
	char ch = _getch();
	if (ch == 13)
		modifyData();
	else if (ch == 27)
		MainMenu();
	else
		cout << "\n\aWrong entry!!!";
	MainMenu();
}
void preorder(node *c)
{
	if (c!=NULL)
	{
		cout << c->key_value<< " ";
		preorder(c->left);
		preorder(c->right);
	}
}
void inorder(node* c)
{
	if(c!=NULL)
	{
		preorder(c->left);
		cout << c->key_value << " ";
		preorder(c->right);
	}
}
void postorder(node* c)
{
	if (c != NULL)
	{
		preorder(c->left);
		preorder(c->right);
		cout << c->key_value << " ";
	}
}
void displayPath(node* c)
{
	system("CLS");
	cout << "Enter node data of which you wanna get path: ";
	int value;
	cin >> value;

	bool check = false;

	if (root == NULL)
	{
		cout << "Tree is empty!\n";
	}
	else
	{
		current = c;

		while (current != NULL)
		{

			if (current->key_value == value)
			{
				check = true;
				break;
			}

			pre = current;

			if (value < current->key_value)
			{
				current = current->left;
			}
			else if (value > current->key_value)
				current = current->right;
		}
	}

	if (check)
	{
		//cout << value << " is found";

		current = c;

		while (current != NULL)
		{
			cout << current->key_value;

			if (current->key_value == value)
			{
				break;
			}

			cout << " -> ";

			pre = current;

			if (value < current->key_value)
			{
				current = current->left;
			}
			else if (value > current->key_value)
				current = current->right;

		}
	}
	else
	{
		cout << "\n\a" << value << " is not in the Tree!";
	}
		
	cout << "\n\nPress ENTER to get more paths or ESCAPE to go back to Main Menu.\n";
	char ch = _getch();
	if (ch == 13)
		displayPath(c);
	else if (ch == 27)
		MainMenu();
	else
		cout << "\n\aWrong entry!!!";
	MainMenu();
}
void displayAllParents(node* c)
{
	if (c == NULL)
	{
		cout << "Tree is empty!\n";
	}
	else
	{
		if (c->left != NULL || c->right != NULL)
		{
			cout << c->key_value << " ";
		}
		if (c->left != NULL)
		{
			displayAllParents(c->left);
		}
		if (c->right != NULL)
		{
			displayAllParents(c->right);
		}
	}
}
void displayAllTerminals(node* c)
{
	if (c == NULL)
	{
		cout << "Tree is empty!\n";
	}
	else
	{
		if (c->left != NULL)
			displayAllTerminals(c->left);
		if (c->right != NULL)
		{
			displayAllTerminals(c->right);
		}
		if (c->left == NULL && c->right == NULL)
		{
			cout << c->key_value << " ";
		}
	}
}
void display(node* p)
{
	system("CLS");
	cout << "\n\n1. Preorder\n2. Inorder\n3. Postorder\n4. Display path of a node\n5. Display all parent nodes\n6. Display all terminal nodes\n7. Main Menu\n8. Exit\n\nEnter your choice:\n";
	char ch = _getch();
	switch (ch)
	{
	case '1':
	{
		system("CLS");
		preorder(p);
		goBack();
		break;
	}
	case '2':
	{
		system("CLS");
		inorder(p);
		goBack();
		break;
	}
	case  '3':
	{
		system("CLS");
		postorder(p);
		goBack();
		break;
	}
	case  '4':
	{
		system("CLS");
		displayPath(p);
		goBack();
		break;
	}
	case  '5':
	{
		system("CLS");
		displayAllParents(p);
		goBack();
		break;
	}
	case  '6':
	{
		system("CLS");
		displayAllTerminals(p);
		goBack();
		break;
	}
	case  '7':
	{
		MainMenu();
		break;
	}
	case '8':
		exit(0);
	default:
		cout << "\aWRONG ENTRY!!!";
	}
}
void findSmallest(node* r)
{
	system("CLS");

	if (r == NULL)
	{
		cout << "Tree is empty!\n";
	}

	current = r;

	while(current->left!=NULL)
	{
		current = current->left;
	}

	cout << "\nSmallest value is " << current->key_value;

	cout << "\n\nPress ESCAPE to go back to Main Menu.\n";
	char ch = _getch();
	if (ch == 27)
		MainMenu();
	else
		cout << "\n\aWrong entry!!!";
	MainMenu();
}
void findLargest(node* r)
{
	system("CLS");

	if (r == NULL)
	{
		cout << "Tree is empty!\n";
	}

	current = r;

	while (current->right != NULL)
	{
		current = current->right;
	}

	cout << "\nLargest value is " << current->key_value;

	cout << "\n\nPress ESCAPE to go back to Main Menu.\n";
	char ch = _getch();
	if (ch == 27)
		MainMenu();
	else
		cout << "\n\aWrong entry!!!";
	MainMenu();
}
void findParent(node* r)
{
	system("CLS");
	cout << "Enter node data of which you wanna find parent: ";
	int value;
	cin >> value;

	bool check = false;

	if (root == NULL)
	{
		cout << "Tree is empty!\n";
	}
	else
	{
		current = r;

		while (current != NULL)
		{
			
			if (current->key_value == value)
			{
				check = true;
				break;
			}

			pre = current;

			if (value < current->key_value)
			{
				current = current->left;
			}
			else if (value > current->key_value)
				current = current->right;
		}
	}

	if (check)
	{
		//cout << value << " is found";
		cout << "\nParent node data of " << value << " is " << pre->key_value;
	}
	else
		cout << "\n\a" << value << " is not in the Tree!";

	cout << "\n\nPress ENTER to search more parent or ESCAPE to go back to Main Menu.\n";
	char ch = _getch();
	if (ch == 13)
		findParent(root);
	else if (ch == 27)
		MainMenu();
	else
		cout << "\n\aWrong entry!!!";
	MainMenu();
}
void countNodes(node* r, int& count)
{
	if (r == NULL)
	{
		return;
	}

	countNodes(r->left, count);

	count++;

	countNodes(r->right, count);
}
int sumNodes(node* r) 
{
	if (r == NULL) 
		return 0;
	return r->key_value + sumNodes(r->left) + sumNodes(r->right);
}
void goBack()
{
	cout << "\n\nPress ENTER to go to Display Menu or ESCAPE to go back to Main Menu.\n";
	char ch = _getch();
	if (ch == 13)
		display(root);
	else if (ch == 27)
		MainMenu();
	else
		cout << "\n\aWrong entry!!!";
	display(root);
}