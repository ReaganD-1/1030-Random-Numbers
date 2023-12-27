/*Authors: 		Reid McCalpin: rmm0378, DJ Trammel: djt0163, Reagan Duke: rmd0171
  Date:			2//2023
  Instructor:	Dr.Shrestha
  Description:	A small code for a game where the user attempts to guess multiple numbers in a generated range.
				The game has a points system and a series of rounds or turns where the plater can decide
				to make a variety of decisions. The game is devised and written with the knowledge of a
				week 4 CSE1030 student. 
*/
#include<iostream>
#include<cstring>
#include<string>
using namespace std;

//DJ Trammel EUID:djt0163
/*
 Function: genShowMatrix
Parameters: integer matrix 
return: a matrix with all numbers -1
Description: This is the place holder for the actual matrix
*/
void genShowMatrix(int dispMatrix[][5])
{
	for( int i =0; i < 5; ++i)
	{
		for(int j = 0; j < 5; ++j)
		{
			dispMatrix[i][j] = -1;
			cout<<dispMatrix[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<< endl;
}

/*
 Function: genHideMatrix
Parameters:integer matrix	integer random number	integer random number
return: a matrix with multiple random numbers
Description: This is the matrix with the actual numbers that the user guesses
*/
void genHideMatrix(int hideMatrix[][5], int NumL, int NumR)
{
	srand(time(NULL));
	for( int i =0; i < 5; ++i)
	{
		for(int j = 0; j < 5; ++j)
		{
			hideMatrix[i][j] = (rand() % (NumR - NumL + 1)) + NumL;
		}
	}
}

/*
 Function: setDisplayLeft
Parameters:reference integer display numbers	reference integer display number 	
			integer random number	 integer random number
return: displays the left number for user
Description: changes the left display number when promted
*/
void setDisplayLeft(int& displayNumL, int displayNumR, int NumL, int NumR)//changes the left display number (displayNumR) when prompted
{
	if(displayNumR > -1)
	{
		cout << "You cannot display both bounds" << endl;
	}
	else
	{
		displayNumL = NumL;
		cout << "Your correct guesses will now net you 1 point and incorrect guesses will subtract 10 from your total" << endl;
	}
}

/*
 Function: setDisplayRight
Parameters:reference integer display numbers	reference integer display number 	
			integer random number	 integer random number
return: displays the right number for user
Description: changes the right display number when promted
*/
void setDisplayRight(int& displayNumR, int displayNumL, int NumR, int NumL)//changes the right display number (displayNumR) when prompted
{
	if(displayNumL > -1)
	{
		cout << "You cannot display both bounds" << endl;
	}
	else
	{
		displayNumR = NumR;
		cout << "Your correct guesses will now net you 1 point and incorrect guesses will subtract 10 from your total" << endl;
	}
}

/*
 Function: showMatrix
Parameters:integer matrix
return: displays the actual matrix
Description: shows the display matrix when the user asks
*/
void showMatrix(int dispMatrix[][5])//shows the display matrix when necessary
{
	for( int i =0; i < 5; ++i)
	{
		for(int j = 0; j < 5; ++j)
		{
			cout << dispMatrix[i][j] << "\t";
		}
		cout << endl;
	}
}

/*
 Function: getName
Parameters:none
return:users name
Description: gets the user's name then makes the user's name to look like this Reagan Duke instead of reagan duke
*/
string getName()
{

	bool Is_Alpha_Or_Whitespace;
	bool Is_All_Alpha_Or_Whitespace;
	string userName;

	//this loop runs initially, prompting the user for a username, then after the interior loop has finished runs again if Is_All_Alpha_Or_Whitespace is false
	do{
		cout<<"Username: ";
		getline (cin, userName);
		
		//this loop checks each index of userName. If an index returns as neither alpha or space
		//it sets Is_All_Alpha_Or_Whitespace to false and terminates.
		//if all indexes of userName are acceptable, the loop ends with Is_All_Alpha_Or_Whitespace = true
		for(int i=0; i<(userName.size()); ++i){		
			Is_Alpha_Or_Whitespace = ((isalpha(userName.at(i)))||(isspace(userName.at(i))));		
			
			if(!(Is_Alpha_Or_Whitespace)){
				cout<<"Error! Please enter a username including only letters and spaces"<<endl;
				i = (userName.size());
				Is_All_Alpha_Or_Whitespace = false;
			}
			
			else{
				Is_All_Alpha_Or_Whitespace = true;
			}
		}
	}while(!(Is_All_Alpha_Or_Whitespace));
	
	//additional variable declaration for initial capitalizing loop
	int wsSize = userName.size();
	int ticker;
	bool NextChar = true;
	string stringCache;
	
	//for loop that runs once for each character in the username
	for(ticker = 0; (ticker < wsSize); ++ticker){
		char charCache = userName.at(ticker);
		
		//if-else block that captalizes initials and changes other chars to lowercase
		if((isalpha(charCache))&&(NextChar == true)){			//if block executed on the first loop and anytime the previous char was whitspace
			charCache = toupper(charCache);	
			stringCache += charCache;
			userName.replace(ticker, 1, stringCache);
			NextChar = false;
		}
		
		else if((isalpha(charCache))&&(NextChar == false)){		//else if block executed on each loop between capital initial and next whitespace
			charCache = tolower(charCache);
			stringCache += charCache;
			userName.replace(ticker, 1, stringCache);
		}
		
		else if(isspace(charCache)){							//else if block executed if whitespace detected, primes the next loop to capitalize the next char
			NextChar = true;
		}
		
		stringCache = "";			//clears cache before next loop. prevents stringCache from containing more than one char
		
	}
		
		return userName;
}


////Reid McCalpin: rmm0378 
/*
 Function: elimate
Parameters:integer guessRow integer guessCol integer hideMatrix integer disMatirx
return: matrix without the number guessed
Description: makes the number guessed have a 0 so that the function guess can operate
*/
int eliminate(int guessRow, int guessCol, int hideMatrix[][5],int dispMatrix[][5]){
	
	for(int r=0;r<5;++r){
		for(int c=0;c<5;++c){
			if((r==guessRow)||(c==guessCol)){
				hideMatrix[r][c] = 0;
				dispMatrix[r][c] = 0;
			}
			cout<<dispMatrix[r][c]<<"\t";
		}
		cout<<endl;
	}
	
	return 0;
}

/*
 Function: guess
Parameters:integer points integer hideMatrix integer dispMatrix integer display number integer display number
return: matrix with the number guessed 
Description: changes the matrix so that the guessed number is displayed
*/
void funcGuess(int& points, int hideMatrix[][5], int dispMatrix[][5], int displayNumL, int displayNumR){
	
	int userGuess;
	bool CORRECT = false;
	
	showMatrix(dispMatrix);//initializes the display matrix
	
	cout<<"Please enter your guess: ";
	cin>>userGuess;
	
	for(int r=0;r<5;++r){
		for(int c=0;c<5;++c){
			if(((hideMatrix[r][c])==userGuess)&&(CORRECT==false)){
				cout<<"That is a match!"<<endl;
				CORRECT = true;
				eliminate(r,c, hideMatrix, dispMatrix);
				if((displayNumL > -1)||(displayNumR > -1)){
					points = points + 1; //FIX ME
					cout<<"Points: "<<points<<endl;
				}
				else{
					points = points + 5; //FIX ME
					cout<<"Points: "<<points<<endl;
				}
			}
		}
	}
	
	if(CORRECT==false){
		if((displayNumL > -1)||(displayNumR > -1)){
			points = points -10;
			cout<<"That is not a match!"<<endl;
			cout<<"Points: "<<points<<endl;
		}
		else{
			cout<<"That is not a match!"<<endl;
			points = points -5;
			cout<<"Points: "<<points<<endl;
		}
	}
	
	return;
}

/*
 Function: allZeros
Parameters:integer anyMatrix
return:checks the matrix for any 0s
Description: helps to see if the user guessed all numbers correctly
*/
int allZeros(int dispMatrix[][5]){
	int intCorrect=0;

	for(int r=0;r<5;++r){
		for(int c=0;c<5;++c){
			if(dispMatrix[r][c]!=0){
				intCorrect = 1;
			}
		}
	}
	
	return intCorrect;
}

//Reagan Duke EUID:rmd0171
/*
 Function: initalize
Parameters: integer random number integer random number
return:gets the two random number
Description: makes the two bounds for the guessing numbers random numbers
*/
void Initialize(int hideMatrix[][5],int dispMatrix[][5],int& NumL, int& NumR)
{
    srand(time(NULL)); 
    NumL = rand() % 100 + 100; 
    NumR = rand() % 200 + 100;//Generates two seeded random numbers from 200-300 inclusive

    do {
	    NumL = rand() % 100 + 100;
     }while(NumL >= NumR); //Runs the left int through generation til it is less than the right
	 
	
	 genShowMatrix(dispMatrix);//initializes the display matrix
	 genHideMatrix(hideMatrix, NumL, NumR);//initializes the hidden matrix using upper and lower bounds
}

int main()
{
	
//Reagan Duke EUID:rmd0171
//declaring variables that are used for the "-1    -1" and the random numbers
	int dispMatrix[5][5];
	int hideMatrix[5][5];
	int displayNumL = -1;
    int displayNumR = -1;
    int NumL;
    int NumR;
	int numPoints = 100;
	int choice;
	int allCorrect;
	string userName;
	
	
	//displays the welcome and asks for username
	cout << "+-------------------------------------------------+ " << endl;
	cout << "|         Computer Science and Engineering        | " << endl;
	cout << "|          CSCE 1030 - Computer Science I         | " << endl;
	cout << "|    Reagan Duke rmd0171 reaganduke@my.unt.edu    | " << endl; 
	cout << "+-------------------------------------------------+ " << endl;
	cout<<"Welcome! Please enter a username"<<endl;
	
	////DJ Trammel EUID:djt0163
	userName = getName();
	cout << "Hello " << userName << "!" << endl;

	Initialize(hideMatrix,dispMatrix,NumL,NumR);
	
	enum MenuSelect {displayLeft = 1, displayRight = 2, guess = 3, reset = 4, exit = 5};
	
	//variable declaration for ending the loop
	 bool uExit = true;
	
	do{ //starts the loop until user exits or points=o
	
	cout << displayNumL << "     " << displayNumR << endl;
     cout << "1. Display left number" << endl;
     cout << "2. Display right number" << endl;
     cout << "3. Guess a number in between" << endl;
     cout << "4. Generate new numbers" << endl;
     cout << "5. Exit" << endl;
	 cout << "What would you like to do? (1-5)" << endl;
	 
	 //gets menu choice from the user
	 cin >> choice;
	 
	 //changes the choice to where it can be read as an enum
	 MenuSelect my_Select = static_cast<MenuSelect>(choice);
	 
	 //starts the if user choices this then this happens
	 switch(my_Select)
	 {
		case displayLeft:
			setDisplayLeft(displayNumL,displayNumR,NumL,NumR);
		break;
		
		case displayRight:
			setDisplayRight(displayNumR,displayNumL,NumR,NumL);
		break;
		
		case guess:
			
			funcGuess(numPoints, hideMatrix, dispMatrix, displayNumL, displayNumR);
			allCorrect = allZeros(dispMatrix);
			char newGame;
			bool newGB;
			if (allCorrect == 1)
			{
				break;
			}
			else if (allCorrect == 0)
			{
				cout<<"You have won your game! Would you like to play another game? (y/n)"<<endl;
				cin >> newGame;
				
				do{
				if (newGame == 'y')
				{
					Initialize(hideMatrix,dispMatrix,NumL,NumR);
					newGB = true;
				}
				else if (newGame == 'n')
				{
					newGB = true;
					return 0;
				}
				else 
				{
					cout<< "Error: Please enter again."<<endl;
					cin>> newGame;
					newGB = false;
				}
				} while (newGB == false);
			}
			
		break;
			
		case reset:  //changes the bounds to create a different game
			Initialize(hideMatrix,dispMatrix,NumL,NumR);
			
			numPoints -= 1;
			cout << "Your points:" << numPoints << endl;
			
			displayNumL = -1;
			displayNumR = -1;
			
		break;
			
		case exit:  //exits the game
		uExit = false;
			cout << "Your final points:" << numPoints << endl;
			cout << "Goodbye " << userName <<endl;
		break;
		
		default:   //if none of the menu choices are chosen then this runs
		cout << "Error: Please enter menu choice" <<endl;
		
		break;
	 }
}while(numPoints > -1 && uExit == true);
	
	if (numPoints <= -1) //adds an output for when the user falls below 0 points
	{
		cout<< "Sorry you are out of points."<<endl;
		cout << "Goodbye " << userName <<endl;
	}
	
	return 0;
}