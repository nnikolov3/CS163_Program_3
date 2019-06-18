/* NIkolay Nikolov 

   CS 163 Fall
Instructor:Karla Fant
Program # 3
November 4,2016
Purpose of the program :

The cope of the program is to develop an application that will make use of a Table ADT,
utilizing a hash table and using chaining as a collision resolution technique. 
Furthermore, the main purpose of the application is the client user to be able to store ,
retrieve and display information for a video game in an efficient, and fast way.
Overall, the user should be able to insert information based on a keyword, 
load information from an external data file, remove a game based on a keyword, 
add recommendations for a specific platform, retrieve information ,
and start rating for all and/or a specific platform(s), 
and lastly display all games for a particular platform 
or display all games for all platforms without any particular order.

 */

// This is the implementation of the ADT 

#include"pr3_table.h"
#include<cmath>

ofstream mygames;

using namespace std ;

//----------------------------------node starts here // This node is for the first hash table where the key is the name 

node :: node () // constructor for the node
{
	next = NULL;
	entry = NULL;

}
node :: node (char*atitle, char*adescription,char*atype,char*aplatform, int arating, char * arecommendation)// copy constructor 
{
	next = NULL ;
	entry = new game_entry (atitle, adescription,atype,aplatform, arating,  arecommendation) ; // passing the object of data into the node 

}
node :: ~node() // destructor for the node. Needs to be revised 
{
	if (entry)
		entry->delete_entry();
	entry = NULL;
}
//-------------------------------------node ends here
// This is the second node with key the platform. 
// Rather pointing to coppied data to the first table , both of the nodes point to the same data, and nothing is really being saved in them . 

p_node ::p_node () // constructor for the node
{
	next = NULL;
	data = NULL; 
}
p_node :: p_node (node * temp) 
{
	next = NULL ;
	data = temp ;
}
p_node :: ~p_node() // destructor for the node. Needs to be revised 
{
	next = NULL ;
	if (data)
		delete data ;
	data = NULL;
}
// p_node----------ends here ----------------------------------------------------


//-------------------------------------class starts here
table :: table (int size)// constructor for the class 
{
	// table 1 for the key with the " title" 
	hash_table = new node*[size]; // allocates dynamically memory for the hash table 
	for(int i=0;i<size;++i)
		hash_table[i] = NULL;
	hash_table_size=size;
	// table 2 for the key with the " platform " 
	hash_table2 = new p_node*[size];
	for (int i=0; i<size; ++i)
		hash_table2[i] = NULL ;
	hash_table2_size =size  ;
}

table :: ~table () // destructor for the class
{
	delete_all_wrapper() ;
	delete [] hash_table2; // delete any leftovers from the table and set to NULL 
	hash_table2 = NULL ;

	delete  [] hash_table;
	hash_table = NULL;
}
int table :: delete_all_wrapper()
{
	delete_all();
}
int table :: delete_all() // the function to delete all , also used in the destructor above // 
{

	if (!hash_table && !hash_table2) // 1st case if the is no hash tables at all otherwise
		return 0;                  // it will check for each table and delete all

	for (int i = 0;i <hash_table2_size;++i) // First to delete the second table that is derived from the first one 
	{
		p_node * current2 =hash_table2[i]; // make instance of current
		p_node * temp2 = current2 ;
		while (current2) // traverse and delete
		{
			temp2 = current2 -> next ;
			current2 ->data = NULL ;
			delete current2 ;
			current2 = NULL;
			current2=temp2 ;
		}
		hash_table2[i] = NULL;
	}

	for (int i = 0;i <hash_table_size ; ++i) // delete for the 1st table 
	{
		node * temp;
		while(hash_table[i])
		{
			temp = hash_table[i] -> next ;
			delete hash_table[i];
			hash_table[i] = temp ;	
		}
		hash_table[i] = NULL;
	}

	delete[] hash_table ;
		hash_table = NULL ;
	delete[] hash_table2;
		hash_table2 = NULL ;

	return 0;
}	


bool table :: remove(char * atitle,char * aplatform) // The function to remove a game 
{
	int index = hash_function(atitle);	
	char * title = NULL;

	if (!hash_table) // no table at all 
		return 0 ;

	else if (!hash_table [ index ]) // if the is not an index that matches
		return 0;

	node*current = hash_table[index]; // temporary pointer
	if (current -> next != NULL && (strcmp(current->entry->retrieve(), atitle)==0)) // if the index and the title match what is stored 
	{
		node* newhead = current->next;
		current->entry -> delete_entry() ;// delete the data
		delete current; // deleter the node
		current = NULL ;
		hash_table[index] = newhead;
		return true;
	}
	if(current)
	{
		node * temp = current; // second temporaty pointer
		while (current)
		{	
			if (strcmp(current->entry->retrieve(), atitle)==0 ) // if the index and the stored index match as well as the title and the platform , otherwise it would delete everything with the same name, for all platforms 
			{
				temp = current -> next;
				current -> entry -> delete_entry();; // delete entry
				delete current ;
				current = NULL ;
				current = temp;
				return true;
			}
			current = current -> next ; // traverse
		}
	}

	removetable2(aplatform);


	return 0;
}

int table::removetable2( char* aplatform)
{

	int index2 = hash_fun(aplatform);	

	if (!hash_table) // no table at all 
		return 0 ;

	if (!hash_table [ index2 ]) // if the is not an index that matches
		return 0;

	p_node*current2 = hash_table2[index2]; // temporary pointer
	if (current2 -> next != NULL && (strcmp(current2->data->entry->retrieve_platform(), aplatform)==0)) // if the index and the title match what is stored 
	{
		p_node* newhead2 = current2->next;
		delete current2 ->data ;
		current2->data = NULL ;// delete the data
		delete current2; // deleter the node
		current2 = NULL ;
		hash_table2[index2] = newhead2;
		return true;
	}
	p_node * temp2 = current2; // second temporaty pointer
	while (current2)
	{	
		if (strcmp(current2 ->data->entry->retrieve_platform(), aplatform)==0 ) // if the index and the stored index match as well as the title and the platform , otherwise it would delete everything with the same name, for all platforms 
		{
			temp2 = current2 -> next;
			delete current2 ->data ;
			current2 -> data = NULL; // delete entry
			delete current2 ;
			current2 = NULL ;
			current2 = temp2;
			return true;
		}
		current2 = current2 -> next ; // traverse
	}




	return 0;

}

bool table :: insert (char*atitle, char*adescription,char*atype,char*aplatform, int arating, char * arecommendation)  // inserting into the 1st table for the title
{

	int index = hash_function(atitle) ;//catching the index 
	node * temp  = new node (atitle, adescription,atype,aplatform, arating, arecommendation); // create a new node where the object entry is passed 
	temp -> next = hash_table[index]; 
	hash_table[index] = temp ; // inserting into the new node



	int index2 = hash_fun(aplatform) ;//catching the index 
	p_node * temp2  = new p_node (temp);// creating a new node 
	temp2 -> next = hash_table2[index2];
	hash_table2[index2] = temp2 ;

	return true;

}
bool table :: retrieve (char * aplatform,char * atitle, char * arecommendation)
{
	if (!hash_table)
		return false;
	int index =hash_function(atitle ) ;

	node * current =hash_table [index];
	while (current)
	{
		if ( (strcmp (current ->entry-> retrieve(),atitle) == 0) && (strcmp (current ->entry -> retrieve_platform (),aplatform) == 0))
		{
			cout << "\t\t\t We have a match at index   :" << index <<  endl ;
			current -> entry -> change_reco(arecommendation);
			cout <<"Succesfully added !I will upodate the file too ! " << endl ;
		}

		current = current -> next;
	}
	return false ;
}



bool table :: write_to_file () // write to a file 
{
	mygames.open("CS163_games.txt",ios::out|ios::app);
	if (!hash_table) // if the is not anything to write 
		return 0;
	if (mygames)
	{
		for (int i =0 ;i<hash_table_size;++i)
		{
			node*current = hash_table[i];
			while (current)
			{
				current->entry->write_to_file(mygames);
				current=current->next;
			}
		}
		mygames.close();
		mygames.clear();
	}
	return false ;
}				
bool table :: read_from_file() // read from the file 
{
	int SIZE=500;
	// initializing the veriables into the scope of the function 
	char  atitle[SIZE] ;
	char  adescription[SIZE];
	char atype[SIZE];
	char aplatform[SIZE] ;
	int arating =0;
	char arecommendation[SIZE];

	ifstream mygames; // creating a class ifstream object 
	// the data is passed instantly to both of the tables through pointers 
	mygames.open("CS163_games.txt",ios::out);
	mygames.peek();
	while (!mygames.eof())
	{// geting the veriables from the file 
		mygames.get(atitle,SIZE,']');
		mygames.ignore(SIZE,']');
		mygames.clear();		

		mygames.get(adescription,SIZE,']');
		mygames.ignore(SIZE,']');	
		mygames.clear();		


		mygames.get(atype,SIZE,']');
		mygames.ignore(SIZE,']');
		mygames.clear();		

		mygames.get(aplatform,SIZE,']');
		mygames.ignore(SIZE,']');
		mygames.clear();		


		mygames >> arating ;
		mygames.ignore(2,']');
		mygames.clear();

		mygames.get(arecommendation,SIZE,'\n');
		mygames.ignore(SIZE,'\n');
		mygames.clear();		

		insert(atitle, adescription,atype,aplatform,arating,arecommendation); // insert into table 
		mygames.peek();
	}
	mygames.close();
	mygames.clear();

}
bool table :: display_game(char * atitle) // display all the information for a specific title 
{
	int index = hash_function(atitle);
	node * current =hash_table[index];
	if (!hash_table)
		return 0; 
	while (current)
	{	
		if( strcmp (atitle, current -> entry -> retrieve())==0)	// as long as  there is a match the display
			current ->entry -> display();	

		current=current -> next;
	}
	return false ;
}


int table :: display_all() // The function to display  for all games and platforms 
{
	if (!hash_table)// if there are no entries 
		return 0 ;

	for (int i =0; i<hash_table_size;++i)
	{
		node*current =hash_table[i];
		while (current)
		{
			cout << "\t\t\t Index "<<  i << endl; // display the index of the hash table 
			current ->entry ->display();
			current = current -> next;	
		}
	}
}


int table ::  hash_function(char * title )//hash function for the "title" .This function creates an index when the user inputs the data.
{
	int sum =0;
	int length = strlen(title) ;
	int l=(length*2)/3 ; // I used 2/3 of the length because it provides better indeces 
	for (int i = 0;i < l ;++i)
	{
		sum  = sum + title[i];
	}
	int hash_key =(sum * 1367)  % 27 ;// here is the hash_key

	return hash_key;
}
int table :: hash_fun(char * aplatform) // second hash_key function for the "platform" . This function creates an index when the user inputs the data 

{
	int sum =0 ;
	int length = strlen(aplatform) ; // since the length of the platform title is not too length I just used the entire length

	for (int i = 0;i < length;++i)
	{
		sum = sum + aplatform [i];
	}
	int hash_key=(sum * 1367) % 27 ;

	return hash_key ;
}
/*
   bool table :: insert1 (char * aplatform, char * atitle , char*adescription,char*atype ,   int arating, char * arecommendation)  
// this function creates a node instance where it points to entry object where the data is stored
{

int index = hash_fun(aplatform) ;//catching the index 
p_node * temp  = new p_node (atitle, adescription,atype,aplatform, arating, arecommendation);// creating a new node 
temp -> next = hash_table2[index];
hash_table2[index] = temp ;

return true;

}
 */
bool table :: display_platform(char * aplatform) // display all for a particular platform 
{
	int index = hash_fun(aplatform) ; // catching the index for the platform variable 
	if (!hash_table2 || !hash_table2 [index])
		return 0;

	p_node * current = hash_table2[index] ;
	while (current)
	{
		if (strcmp(aplatform ,current ->data-> entry -> retrieve_platform())==0)
		{
			cout<<"\t\t\t The index is " << index << endl;
			current -> data -> entry ->display() ;
		}

		if(strcmp(aplatform ,current ->data-> entry -> retrieve_platform())!=0)
			return 0;

		current = current -> next;
	}
	return false ;
}


//----------------------------------------class ends here

