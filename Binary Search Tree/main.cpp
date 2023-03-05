//Skewed Tree
t.Insert(1);
t.Insert(2);
t.Insert(3);
t.Insert(4);
t.Insert(3);
t.Insert(5);
t.Insert(6);

t.PrintInOrder();
cout << endl << endl;

t.PrintTree();

cout << "Depth (4) : " << t.Depth(4) << endl << endl;

cout << "Height of BST: " << t.Heigth() << endl << endl;

cout << "Breadth of BST: " << t.Breadth() << endl << endl;

if (t.IsBalanced() == true)
	cout << "Balanced\n";
else
	cout << "Not Balanced\n";
cout << endl;

cout << "Successor of 6: " << t.Successor(6) << endl << endl;

cout << "Predecessor of 1: " << t.Predecessor(1) << endl << endl;

//Unskewed-Balanced
t.Insert(50);
t.Insert(83);
t.Insert(90);
t.Insert(89);
t.Insert(100);
t.Insert(106);
t.Insert(3);
t.Insert(5);
t.Insert(71);
t.Insert(9);
t.Insert(6);
t.Insert(56);

t.PrintInOrder();
cout << endl << endl;

t.PrintTree();

t.Erase(83);

t.PrintInOrder();
cout << endl << endl;

t.PrintTree();

cout << "Depth (56) : " << t.Depth(56) << endl << endl;

cout << "Height of BST: " << t.Heigth() << endl << endl;
	
if (t.IsBalanced() == true)
	cout << "Balanced\n";
else
	cout << "Not Balanced\n";
cout << endl;

cout << "Successor of 9: " << t.Successor(9) << endl << endl;

cout << "Predecessor of 9: " << t.Predecessor(9) << endl << endl;

//Assignment Question
t.Insert(50);
t.Insert(35);
t.Insert(70);
t.Insert(2);
t.Insert(61);
t.Insert(81);
t.Insert(55);
t.Insert(93);
t.Insert(63);

t.PrintInOrder();
cout << endl << endl;

t.PrintTree();

cout << "Depth (81) : " << t.Depth(81) << endl << endl;

cout << "Height of BST: " << t.Heigth() << endl << endl;

if (t.IsBalanced() == true)
	cout << "Balanced\n";
else
	cout << "Not Balanced\n";
cout << endl;

cout << "Successor of 63: " << t.Successor(63) << endl << endl;

cout << "Predecessor of 61: " << t.Predecessor(61) << endl << endl;

cout << "Path Sum: ";
t.PathSum();
cout << endl << endl;

//Balanced Example
t.Insert(50);
t.Insert(17);
t.Insert(72);
t.Insert(76);
t.Insert(23);
t.Insert(12);
t.Insert(19);
t.Insert(14);
t.Insert(9);
t.Insert(54);
t.Insert(67);

t.PrintInOrder();
cout << endl << endl;

t.PrintTree();

cout << "Depth (9) : " << t.Depth(9) << endl << endl;

cout << "Height of BST: " << t.Heigth() << endl << endl;

if (t.IsBalanced() == true)
	cout << "Balanced\n";
else
	cout << "Not Balanced\n";
cout << endl;

cout << "Successor of 72: " << t.Successor(72) << endl << endl;

cout << "Predecessor of 54: " << t.Predecessor(54) << endl << endl;

cout << "Path Sum: ";
t.PathSum();
cout << endl << endl;

//Balanced Example
int arr[] = { 3, 4, 5, 11, 21, 44, 71 };
bst<int>t(arr, 7);

t.PrintInOrder();
cout << endl << endl;

t.PrintTree();

cout << "Depth (3) : " << t.Depth(3) << endl << endl;

cout << "Height of BST: " << t.Heigth() << endl << endl;

cout << "Breadth of BST: " << t.Breadth() << endl << endl;

if (t.IsBalanced() == true)
	cout << "BALANCED\n";
else
	cout << "Not Balanced\n";
cout << endl;

cout << "Successor of 11: " << t.Successor(11) << endl << endl;

cout << "Predecessor of 11: " << t.Predecessor(11) << endl << endl;

cout << "Path Sum: ";
t.PathSum();
cout << endl << endl;

//Operator ==
t.Insert(50);
t.Insert(35);
t.Insert(70);
t.Insert(2);
t.Insert(61);
t.Insert(81);
t.Insert(55);
t.Insert(93);
t.Insert(63);

t.PrintInOrder();
cout << endl << endl;

t.PrintTree();

bst<int>t1;
t1.Insert(2);
t1.Insert(61);
t1.Insert(81);
t1.Insert(55);
t1.Insert(93);
t1.Insert(63);
t1.Insert(50);
t1.Insert(35);
t1.Insert(70);

t1.PrintInOrder();
cout << endl << endl;

t1.PrintTree();

if (t == t1)
	cout << "Both trees have Same Data\n";
else
	cout << "Both trees have Different Data\n";
cout << endl;

if (t1.SubTree(t) == true)
	cout << "Yes it is a Subtree\n";
else
	cout << "No it isnt a Subtree\n";
cout << endl;

//Copy Constructor
cout << "Copy Constructor\n";
bst<int>t1 = t;
t1.PrintInOrder();
cout << endl << endl;

//Assignment Operator
cout << "Assignment Operator\n";
bst<int>t2;
t2 = t1;
t2.PrintInOrder();
cout << endl << endl;