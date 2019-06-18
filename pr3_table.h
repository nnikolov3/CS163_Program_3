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


 */

// This is the hash table ADT header file 

#include<fstream>
#include"pr3_entry.h"
using namespace std ;


struct node // node for the first table with the title used as a key 
{
	node();
	node (char*atitle, char*adescription,char*atype,char*aplatform, int arating, char * arecommendations) ;//copy constructor
	~node();
	game_entry * entry ;
	node * next ;
};
struct p_node // node for the second table with the platform used as a key
{
	p_node() ;
	p_node(node*) ;//copy constructor
	~p_node();
	node * data ;
	p_node * next ;
};
class table // hash table object aka  A lot of fun
{
	public:
		table(int size=27) ; // constructor 
		~table () ;
		bool insert (char*atitle, char*adescription,char*atype,char*aplatform, int arating, char * arecommendation) ; 
		bool insert1 (char * temp);
		bool remove (char * atitle,char * aplatform) ;
		int removetable2(char* platform);
		bool display_game(char * atitle) ;
		bool display_platform(char * platform) ;
		bool retrieve(char * aplatform,char * atitle, char * arecommendation);
		int delete_all_wrapper();
		int display_all () ;
		bool write_to_file();
		bool read_from_file();
	private:
		int delete_all() ;	
		int hash_fun(char * platform ) ;
		int hash_function(char*  title) ;
		node ** hash_table ;	
		p_node ** hash_table2 ;
		int hash_table_size ;
		int hash_table2_size;
} ;


