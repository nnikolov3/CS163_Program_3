/* Nikolay Nikolov 
   CS 163 Fall
Instructor:Karla Fant
Program # 3
November 4,2016
Purpose of the program :


The scope of the program is to develop an application that will make use of a Table ADT,
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

// This the .cpp file for the implementation of the object entry 

#include"pr3_entry.h"

#include<fstream>

game_entry :: game_entry () // constructor for the data object 
{
	title = NULL ;
	description = NULL ;
	type = NULL ;
	platform = NULL;
	rating = 0;
	recommendation = NULL ;
} 
game_entry :: game_entry(char*atitle, char*adescription,char*atype,char*aplatform, int arating, char * arecommendation) // copy constructor 
{

	title = NULL ;
	description = NULL ;
	type = NULL ;
	platform = NULL;
	rating = 0;
	recommendation = NULL ;

	copy(atitle, adescription,atype,aplatform , arating , arecommendation);

}
int game_entry :: copy(char*atitle, char*adescription,char*atype,char*aplatform, int arating, char * arecommendation) // copy constructor 
{
	if(title){
		delete[]title;
		title = NULL ;
	}
	title = new char [strlen(atitle)+1];
	strcpy (title,atitle) ;
	//--------------------------------------------

	if(description){
		delete[]description;
		description = NULL ;
	}
	description = new char [strlen(adescription)+1];
	strcpy (description,adescription) ;
	//---------------------------------------------
	if(type){
		delete[]type;
		type = NULL ;
	}
	type = new char [strlen(atype)+1];
	strcpy (type,atype) ;

	//----------------------------------------------
	if(platform){
		delete[]platform;
		platform = NULL ;
	}
	platform  = new char [strlen(aplatform)+1];
	strcpy (platform,aplatform) ;

	//---------------------------------------------

	//------------------------------------------------
	if(recommendation){
		delete[]recommendation;
		recommendation = NULL ;
	}
	recommendation = new char [strlen(arecommendation)+1];
	strcpy (recommendation,arecommendation) ;

	rating = arating;

	return 0 ;
}


game_entry :: ~game_entry () // destructor 
{
	delete_entry() ;
}
bool game_entry :: delete_entry () // function to delete the members of the class
{
	if(title)
	{	
		delete[]title;
		title = NULL ;
	}

	if (description){
		delete[]description;	
ni		description = NULL ;
	}

	if (type)
	{
		delete[]type;
		type = NULL ;
	}

	if (platform)
	{
		delete[]platform;
		platform = NULL ;
	}

	if(recommendation)
	{
		delete[]recommendation;
		recommendation = NULL ;
	}
	rating = 0;

}

char * game_entry :: retrieve_rec(char *recommendation)
{
	return recommendation;
}
char * game_entry :: retrieve() // Function to fetch the title in a node
{
	return title;
}
char * game_entry :: retrieve_platform()// function to fetch the platform in the object 
{
	return platform ;
}

bool game_entry ::  change_reco(char * t_reco )
{	

	char * temp  = new char[strlen(t_reco) + strlen(recommendation) + 3] ;
	strcpy(temp , recommendation );
	strcat(temp ,", "  );
	strcat(temp , t_reco) ;



	if(recommendation)
	{
		delete [] recommendation;
		recommendation = NULL;
	}
	recommendation  = temp ;

	return true;
}

int game_entry :: display ()// the display function to display everything inside the object data 
{
	cout<<"\t\t|"<<"------------------------------------------------------------------"<< endl;
	cout<<"\t\t|"<<"The title is         :" << title 	        << endl;
	cout << endl;
	cout<<"\t\t|"<<"The desscription is  :" << description        << endl;
	cout << endl;
	cout<<"\t\t|"<<"The type is          :" << type                << endl;
	cout << endl;
	cout<<"\t\t|"<<"The platform is      :" << platform            << endl;
	cout << endl;
	cout<<"\t\t|"<<"The rating is        :" << rating             << endl;
	cout << endl;
	cout<<"\t\t|"<<"The comment is       :" << recommendation      << endl;	
	cout << endl;
	cout<<"\t\t|------------------------------------------------------------------"<< endl;
}

int game_entry :: write_to_file(ofstream &  mygames) // write to a file 
{
	mygames << title << "]"<< description <<"]"<< type <<"]" << platform <<"]" <<rating <<"]"<< recommendation << endl ;
}


y
