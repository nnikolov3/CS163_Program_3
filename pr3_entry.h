/* Nikolay Nikolov 
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
:wa



 */

// This is the header file for the object "entry" that is responsible for gathering the data 


#include<iostream>
#include<cctype>
#include<cstring> 

using namespace std ;
#ifndef DATA
#define DATA 

class game_entry
{
	public:
		game_entry(); // constructor	
		game_entry(char*atitle, char*adescription,char*atype,char*aplatform, int arating, char * arecommendations) ; // copy constructor 
		~game_entry () ;
		char * retrieve_rec(char * recommendation);
		int copy (char*atitle, char*adescription,char*atype,char*aplatform, int arating, char * arecommendations) ; // copy constructor 
		char * retrieve () ; // fetch the title 
		char * retrieve_platform();// to fetch the platform 
		bool change_reco(char * t_reco);
		int display (); // display evertyhing in  the object
		bool delete_entry (); // delete and reset the members in the object
		int write_to_file(ofstream & mygames); // write to a file 
	private :
		char * title;
		char * description ;
		char * type ;
		char * platform ;
		int rating ;
		char * recommendation ;
};

#endif


