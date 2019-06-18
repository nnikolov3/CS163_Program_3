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
#include"pr3_entry.h"
#include<fstream>

using namespace std ;
const int SIZE = 500;
int main(){		
	game_entry entry;
	table mytable;

	char  atitle[SIZE] ;
	char  adescription[SIZE];
	char atype[SIZE];
	char aplatform[SIZE] ;
	int arating= 0 ;
	char arecommendation[SIZE];
	char t_reco[SIZE];
	int var=0;
	bool done =false ;

	while (!done){ // Menu is here
		cout<<"Hello!" << endl;
		cout<<"Please press 1 to add a new game. " << endl ;
		cout<<"Please press 2 to display all games from the file. " << endl ;
		cout<<"Please press 3 to remove a game." << endl ;
		cout<<"Please press 4 to add recommendation given a particular platform."<< endl ;
		cout<<"Please press 5 to display all games for all platform." << endl ;
		cout<<"Please press 6 to dispaly for a particular game ." << endl ;
		cout<<"Please press 7 to display for a platform." << endl;
		cout<<"Please press 8 to delete all" << endl;
		cout<<"Please press 9 to quit . Type here --->";
		cin >> var ;
		cin.clear () ;
		cin.ignore (SIZE,'\n') ;


		switch(var){

			case 1: // Enqueue

				cout <<"Howdy! " << endl ;

				cout <<"Please enter the title  of the game." <<endl ;
				cin.get(atitle,SIZE);
				cin.clear();
				cin.ignore(SIZE, '\n') ;

				cout <<"Please enter description of the game."<< endl ;	
				cin.get(adescription,SIZE);
				cin.clear();
				cin.ignore(SIZE, '\n') ;

				cout <<"Please enter the type of the game ." << endl ;
				cin.get(atype,SIZE);
				cin.clear();
				cin.ignore(SIZE, '\n') ;

				cout <<"Please enter the platform of the game ." << endl ;
				cin.get(aplatform,SIZE);
				cin.clear();
				cin.ignore(SIZE, '\n') ;

				cout <<"Please enter the rating of the game. " << endl ;	
				cin >> arating  ;cin.ignore(100,'\n') ;

				cout <<"Please enter a comment for the game." << endl ;
				cin.get(arecommendation,SIZE);cin.clear() ;cin.ignore(100,'\n') ;

				cout <<"Alrighty lets save everything ! " << endl ;	

				mytable.insert(atitle,adescription,atype, aplatform,arating,arecommendation);
				mytable.write_to_file() ;	
				break ;

			case 2: // Display everything
				cout <<"Let's display the games stored in the file! " << endl ;
				mytable.read_from_file() ;
				mytable.display_all();

				break ;

			case 3: // 

				cout << "Lets remove a game !"<< endl;
				cout<<"Which game would you like to remove? " << endl;
				cin.get(atitle,SIZE);cin.clear();cin.ignore(SIZE,'\n') ;
				cout<<"For which platform " << endl;
				cin.get(aplatform,SIZE);cin.clear();cin.ignore(SIZE,'\n');
				mytable.remove(atitle,aplatform);

				break ;

			case 4: // add a recomendation for a platform 
				cout<<"For which platform would you like to add a recommendation?" << endl ;	
				cin.get(aplatform,SIZE);cin.clear();cin.ignore(SIZE,'\n');

				cout<<"Also add the title"<< endl ;
				cout<<"Enter the title " << endl ;	
				cin.get(atitle,SIZE);
				cin.clear();
				cin.ignore(SIZE, '\n') ;	


				cout<<"Add the new comment ." << endl ;
				cin.get(t_reco,SIZE);cin.clear () ;cin.ignore(SIZE,'\n');
				mytable.retrieve(aplatform, atitle,t_reco);

				break ;

			case 5:// Display all

				cout<<"\t\t\t These are all the games !"  << endl ;
				mytable.display_all();

				break ;

			case 6: // Display for a game
				cout <<"Which game you would like to search? " << endl;
				cin.get(atitle,SIZE);cin.clear();cin.ignore(SIZE,'\n');
				mytable.display_game(atitle);

				break ;

			case 7: // Display for a platform

				cout<<"Please type the platform you would like to display all the games. " << endl ;
				cin.get(aplatform,SIZE);cin.clear();cin.ignore(SIZE,'\n');
				mytable.display_platform(aplatform);

				break;

			case 8:
				cout<<"Delete all !" << endl ;
				mytable.delete_all_wrapper();

				break;


			case 9: // Quit
				cout<<"Live long and prosper! "<< endl; 

				done = true ;
				break ;
			default :

				break ;
		}	



	}



	return 0 ;

}



