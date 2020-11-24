#include<iostream>
#include "AVLTrees.h"
using namespace std;

int main() {

	
	AVL stdTree;
	stdTree.insert(14);
	stdTree.insert(17);
	stdTree.insert(11);
	stdTree.insert(7);
	stdTree.insert(53);
	stdTree.insert(4);
	stdTree.insert(13);
	stdTree.Printintreeform();
	stdTree.insert(12);
	cout << endl << endl;
	stdTree.Printintreeform();
	stdTree.insert(8);

	cout << endl << endl;
	stdTree.Printintreeform();

	stdTree.deletedata(53);
	cout <<endl <<endl <<"Tree after Deletion :"<<endl;
	stdTree.Printintreeform();
	
	stdTree.deletedata(11);
	cout << endl << endl << "Tree after Deletion :" << endl;
	stdTree.Printintreeform();

	stdTree.deletedata(8);
	cout << endl << endl << "Tree after Deletion :" << endl;
	stdTree.Printintreeform();
	cout << endl << "No of nodes : ";
	cout<< stdTree.NoofNodes(); //returns 6
	cout << endl << endl;
	cout<< "is found : "<<stdTree.search(17); //returns true;
	stdTree.flipClockwise();
	cout <<endl<<endl<<"Tree after flipping :"<<endl;
	stdTree.Printintreeform();
}