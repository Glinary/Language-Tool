/*
May 23-24, 2022
1. Made getString1 function, getString2 function, AddEntry function, and header file
2. Fixed data structure of entry into containing an array of language and translation
3. Made a draft of addTranslations
4. Fixed addEntry issues

May 25, 2022
1. Fixed addTranslations issues
2. added checkValidEntry which also accounts for cases of wrong data type inputs
3. finished addTranslations
4. made a function to add unique language-translation pairs to an entry
5. addEntry now only accepts unique laguage-translation pairs in the same entry

June 1, 2022
1. Drafting of displayEntry
2. Drafting of searchWord
3. Drafting of searchTranslation

June 3, 2022
1. Finished displayEntry, searchWord, and searchTranslation
2. Finished modifyEntry, deleteEntry, and deleteTranslation
3. Drafting of identifyMainLanguage

June 12, 2022
1. Fixed code to compile gcc -Wall with no errors
2. Deleted identifyMainLanguage
3. Drafting of import function

June 13, 2022
1. Finished simpleTranslation
2. Finished identifyMainLanguage but without accouting for import
3. Finished import function

June 14, 2022
1. Fixed import function
2. Implemented code to accept maximum of 10 translations per entry
3. Entries index are now shifted so user may enter 1 instead of 0
4. Improved readability
5. fixed export function
6. fixed language tools

June 15, 2022
1. Updated main menu
2. Implemented import function before language tools
3. Updated code to clear list before exit from manage data
4. Finished internal documentation
5. Improved display of searchWord
6. Fixed alignment of display functions
7. getOption functions updated to accept until 30 char errors

June 16, 2022
1. Fixed identifyMainLanguage
2. Language Tools can now display top 2 main languages
3. Updated identifyMainLanguage to only exit on user's choice
*/

/********************************************************************************************************* 
This is to certify that this project is my own work, based on my personal efforts in studying and applying 
the concepts learned. I have constructed the functions and their respective algorithms and corresponding 
code by myself. The program was run, tested, and debugged by my own efforts. I further certify that I 
have not copied in part or whole or otherwise plagiarized the work of other students and/or persons.
																Gleezell Vina A. Uy, DLSU ID# 12133663 
*********************************************************************************************************/

/*
The program consists of multiple menus in which the user may navigate through.
The program is capable of storing up to 150 entries with 10 language-translation pairs.
The program was created with features to allow the user to manage data.
Additionally, the user may import a compatible text format upon using
the program's language tools. 

As a bonus feature, the program is capable of detecting input errors from the user,
such as forcing the user to input an expected integer instead of a string
so that the program may not terminate or enter an infinite loop. 
However, the program may accept only 30 characters at most from the user.

As another bonus feature, the program is capable of automatically
disregarding exceeding translations when the content in an import file
has more than 10 translations

As another bonus feature, the program is capable of displaying
the top 2 main languages in a sentence, whether there is a tie or none.
However, the program is limited to only analyze single translated words
and not multiple words in one translation.
*/

#include "mp.h"

int
main(void)
{
	//variable declaration
	char  cOpt, //main menu navigation key
		  cOpt2, //language tools navigation key
		  cOpt3; //manage data navigation key
	entry entries[MAX_ENTRY]; 
	int	  nEntriesCnt = 0;
	int   i;
	int   nCheck;

	do {
		printf("\n");
		cOpt = getOption1(); //ask option for main menu
		switch (cOpt)
		{
			case '1': //manage data
				nCheck = 1;
				do 
				{	printf("\n");
					cOpt3 = getOption8(); //ask manage data option

					//check if there is at least one entry before 2-8 & b is valid
					if ((cOpt3 == '2' ||
			 			 cOpt3 == '3' ||
			 			 cOpt3 == '4' ||
			 			 cOpt3 == '5' ||
			 			 cOpt3 == '6' ||
			 			 cOpt3 == '7' ||
			 			 cOpt3 == '8' ||
			 			 cOpt3 == 'b') &&
			 			 nEntriesCnt == 0) 
					{		printf("\n");
							printf("**********\n");
							printf("There are currently no entries\n");
							printf("Please add entry first by choosing [1]\n");
							printf("**********\n");
							printf("\n");
							cOpt = '\0';
							nCheck = 0;
					}

					switch (cOpt3) //proceed with manage data features
					{
						case '1':
							//stops accepting entry input if entries reached 150
							if (nEntriesCnt == MAX_ENTRY)
								printf("Max number of entries have been reached\n");
							else
								addEntry(entries, 
										 &nEntriesCnt);
							break;
						case '2':
							if (nCheck) 
								addTranslations(entries, 
												nEntriesCnt);
							break;
						case '3':
							if (nCheck)
								modifyEntry(entries, 
											nEntriesCnt);
							break;
						case '4':
							if (nCheck)
								deleteEntry(entries, 
											&nEntriesCnt);
							break;
						case '5':
							if (nCheck)
								deleteTranslation(entries, 
												  &nEntriesCnt);
							break;
						case '6':
							if (nCheck)
								displayAllEntries(entries, 
												  nEntriesCnt);
							break;
						case '7':
							if (nCheck)
								searchWord(entries, 
										   nEntriesCnt);
							break;
						case '8':
							if (nCheck)
								searchTranslation(entries, 
												  nEntriesCnt);
							break;
						case 'a':
							import(entries, 
								   &nEntriesCnt);
							break;
						case 'b':
							if (nCheck)
								export(entries, 
									   nEntriesCnt);
							break;
					}
				} 
				while (cOpt3 != '0'); //return to main menu
				//clear list before returning
				for (i = 0; i < nEntriesCnt; i++) 
					entries[i].nCnt = 0;	
				nEntriesCnt = 0; 
				break;
			case '2': //language tools
				import(entries, 
					   &nEntriesCnt);
				do 
				{	cOpt2 = getOption7(); //ask language tool option

					//proceed with language tool features
					if (cOpt2 == '1')
						identifyMainLanguage(entries, 
											 nEntriesCnt);
					if (cOpt2 == '2')
						simpleTranslation(entries, 
										  nEntriesCnt);

				} 
				while (cOpt2 != '3'); // return to main menu
				//clear list before returning
				nEntriesCnt = 0; 
				for (i = 0; i < nEntriesCnt; i++) 
					entries[i].nCnt = 0;
				break;
		}
	} 
	while (cOpt != '3'); //exit program
}

/*
getOption1 returns user's option at main menu

getOption1 only accepts 1, 2, 3 and shows error
		   "Invalid key" if otherwise

@return 1 to show manage data menu
@return 2 to show language tool menu
@return 3 to return exit program

Pre-condition: User enters an input not exceeding 30 characters
*/
char
getOption1 (void)
{
	//variable declaration
	Str30 sOpt;
	int   nCheck;
	
	//show user their options
	printf("Menu:\n");
	printf("Enter [1] to manage data\n");
	printf("Enter [2] to use language tools\n");
	printf("Enter [3] to exit\n");
	
	//ask user for option input
	scanf("%s", sOpt);
	
	//ask until user enters a valid input
	nCheck = 0;
	do 
	{
		if (strlen(sOpt) != 1 ||
			(strcmp(sOpt, "1") != 0 &&
			 strcmp(sOpt, "2") != 0 &&
			 strcmp(sOpt, "3"))) 
		{		//display error message for invalid input
				printf("ERROR: Invalid key\n");
				scanf("%s", sOpt);
				nCheck = 0;
		}
		else 
			nCheck = 1;
	} 
	while (strlen(sOpt) != 1 ||
		   nCheck != 1);
			 
	//return user input
	return sOpt[0];
}

/*
getOption2 returns user's option regarding adding another translation to entry

getOption2 only accepts 1, 2 and shows error
		   "Invalid key" otherwise

@return 1 to allow user to add another translation to entry
@return 2 to return to manage data menu

Pre-condition: User enters an input not exceeding 30 characters
*/
char
getOption2 (void)
{
	//variable declaration
	Str30 sOpt;
	int   nCheck;
	
	//show user their options
	printf("..........\n");
	printf("Options:\n");
	printf("Enter [1] to add another language-translation pair\n");
	printf("Enter [2] to return to menu\n"); 
	printf("..........\n");
	
	//ask user for options input
	scanf("%s", sOpt);
	
	//ask until user enters valid input
	nCheck = 0;
	do 
	{
		if (strlen(sOpt) != 1 ||
			(strcmp(sOpt, "1") != 0 &&
			 strcmp(sOpt, "2") != 0)) 
		{		//show error message on invalid input
				printf("ERROR: Invalid key\n");
				scanf("%s", sOpt);
				nCheck = 0;
		}
		else 
			nCheck = 1;
	} 
	while (strlen(sOpt) != 1 ||
			 nCheck != 1);
	
	//return user input
	return sOpt[0];
}

/*
getOption3 returns user's option between yes or no

getOption3 only accepts n,N,y,Y and shows error
		   "Invalid key" if otherwise

@returns N or n if user chooses no
@returns Y or y if user chooses yes

Pre-condition: User enters an input not exceeding 30 characters
*/
char
getOption3 (void)
{
	//variable declaration
	Str30 sOpt;
	int   nCheck;
	
	//ask user for options input
	scanf("%s", sOpt);
	
	//ask until user enters valid input
	nCheck = 0;
	do 
	{
		if (strlen(sOpt) != 1 ||
			(strcmp(sOpt, "n") != 0 &&
			 strcmp(sOpt, "N") != 0 &&
			 strcmp(sOpt, "y") != 0 &&
			 strcmp(sOpt, "Y") != 0)) 
		{		//show error message if invalid input
				printf("ERROR: Invalid key\n");
				scanf("%s", sOpt);
				nCheck = 0;
		}
		else 
			nCheck = 1;
	} 
	while (strlen(sOpt) != 1 ||
		   nCheck != 1);
			 
	//return user input
	return sOpt[0];
}

/*
getOption4 returns option of user for displayAllEntries
		   where P displays previous entry, N displays next entry,
		   X exits display

getOption4 only accepts p,P,n,N,x,X and shows error
		   "Invalid key" if otherwise

@return P or p to display previous entry
@return N or n to display next entry
@return X or x to exit display

Pre-condition: User enters an input not exceeding 30 characters
*/
char
getOption4 (void)
{
	//variable declaration
	Str30 sOpt;
	int   nCheck;

	//ask user for options input
	scanf("%s", sOpt);

	//ask until user enters valid input
	nCheck = 0; 
	do 
	{
		if (strlen(sOpt) != 1 ||
			(strcmp(sOpt, "P") != 0 &&
			 strcmp(sOpt, "p") != 0 &&
			 strcmp(sOpt, "N") != 0 &&
			 strcmp(sOpt, "n") != 0 &&
			 strcmp(sOpt, "X") != 0 &&
			 strcmp(sOpt, "x") != 0)) {
				//show error message if invalid input
				printf("ERROR: Invalid key\n");
				scanf("%s", sOpt);
				nCheck = 0;
		}
		else
			nCheck = 1;

	} 
	while (strlen(sOpt) != 1 ||
		   nCheck != 1);

	//return user input
	return sOpt[0];
}

/*
getOption5 returns option of user between which
		   among the pair is to be modified
getOption5 only accepts 1,2 and shows error
		   "ERROR: Invalid key" if otherwise

@return 1 if language will be modified
@return 2 if translation will be modified

Pre-condition: User enters an input not exceeding 30 characters
*/
char
getOption5 (void)
{
	//variable declaration
	Str30 sOpt;
	int   nCheck;

	//show user input options
	printf("\n");
	printf("..........\n");
	printf("Options:\n");
	printf("Enter [1] to modify language\n");
	printf("Enter [2] to modify translation\n");
	printf("..........\n");
	//ask user for options input
	scanf("%s", sOpt);

	//ask until user enters valid input
	nCheck = 0; 
	do 
	{	if (strlen(sOpt) != 1 ||
			(strcmp(sOpt, "1") != 0 &&
			 strcmp(sOpt, "2") != 0)) 
		{
				printf("..........\n");
				//show error message if invalid input
				printf("ERROR: Invalid key\n");
				printf("..........\n");
				scanf("%s", sOpt);
				nCheck = 0;
		}
		else
			nCheck = 1;

	} 
	while (strlen(sOpt) != 1 ||
		   nCheck != 1);

	//return user input
	return sOpt[0];
}

/*
getOption6 returns option of user in modifyEntry function

getOption6 only accepts 1 or 2 and shows error
		   "Invalid key" if otherwise

@return 1 if user wants to continue modifying entry
@return 2 to return to manage data menu

Pre-condition: User enters an input not exceeding 30 characters
*/
char
getOption6 (void)
{
	//variable declaration
	Str30 sOpt;
	int   nCheck;

	//show user input options
	printf("\n");
	printf("..........\n");
	printf("Options:\n");
	printf("Enter [1] continue modifying entry\n");
	printf("Enter [2] to return to menu\n");
	printf("..........\n");
	//ask user for options input
	scanf("%s", sOpt);

	//ask until user enters valid input
	nCheck = 0; 
	do 
	{	if (strlen(sOpt) != 1 ||
			(strcmp(sOpt, "1") != 0 &&
			 strcmp(sOpt, "2") != 0)) 
		{		//show error message if invalid input
				printf("ERROR: Invalid key\n");
				scanf("%s", sOpt);
				nCheck = 0;
		}
		else
			nCheck = 1;

	} 
	while (strlen(sOpt) != 1 ||
		   nCheck != 1);

	printf("\n");

	//return user input
	return sOpt[0];
}

/*
getOption7 returns user's option for language tools menu

getOption7 only accepts 1,2,3 and shows error
		   "Invalid key" if otherwise

@return 1 to use identify main language feature
@return 2 to use translate feature
@return 3 to return to main menu

Pre-condition: User enters an input not exceeding 30 characters
*/
char
getOption7 (void)
{
	//variable declaration
	Str30 sOpt;
	int   nCheck;

	//show user input options
	printf("\n");
	printf("Language Tools:\n");
	printf("Enter [1] to Identify Main Language\n");
	printf("Enter [2] to Translate\n");
	printf("Enter [3] to return to main menu\n");
	
	//ask user for options input
	scanf("%s", sOpt);
	
	//ask until user enters valid input
	nCheck = 0;
	do 
	{	if (strlen(sOpt) != 1 ||
			(strcmp(sOpt, "1") != 0 &&
			 strcmp(sOpt, "2") != 0 &&
			 strcmp(sOpt, "3"))) 
		{		//show error message if invalid input
				printf("ERROR: Invalid key\n");
				scanf("%s", sOpt);
				nCheck = 0;
		}
		else 
			nCheck = 1;
	} 
	while (strlen(sOpt) != 1 ||
		   nCheck != 1);
			 
	//return user input
	return sOpt[0];
}

/*
getOption8 returns user's option at manage data menu

getOption8 only accepts 1,2,3,4,5,6,7,8,a,b,0
		   and shows error "Invalid key" if otherwise

@return 1 to use add entry feature
@return 2 to use add translations feature
@return 3 to use modify entry feature
@return 4 to use delete entry feature
@return 5 to use delete translation feature
@return 6 to to display all entries
@return 7 to use search word feature
@return 8 to use search translation feature
@return a to use import feature
@return b to use export feature
@return 0 to return to main menu

Pre-condition: User enters an input not exceeding 30 characters
Pre-condition: User does not enter an uppercase char of a valid input
*/
char
getOption8 (void)
{
	//variable declaration
	Str30 sOpt;
	int   nCheck;
	
	//show user input options
	printf("Menu:\n");
	printf("Enter [1] to Add Entry\n");
	printf("Enter [2] to Add Translations\n");
	printf("Enter [3] to Modify Entry\n");
	printf("Enter [4] to Delete Entry\n");
	printf("Enter [5] to Delete Translation\n");
	printf("Enter [6] to Display All Entries\n");
	printf("Enter [7] to Search Word\n");
	printf("Enter [8] to Search Translation\n");
    printf("Enter [a] to import\n");
	printf("Enter [b] to export\n");
	printf("Enter [0] to return to main menu\n"); 
	
	//ask user for options input
	scanf("%s", sOpt);
	
	//ask until user enters valid input
	nCheck = 0;
	do 
	{	if (strlen(sOpt) != 1 ||
			(strcmp(sOpt, "1") != 0 &&
			 strcmp(sOpt, "2") != 0 &&
			 strcmp(sOpt, "3") != 0 &&
			 strcmp(sOpt, "4") != 0 &&
			 strcmp(sOpt, "5") != 0 &&
			 strcmp(sOpt, "6") != 0 &&
			 strcmp(sOpt, "7") != 0 &&
			 strcmp(sOpt, "8") != 0 &&
			 strcmp(sOpt, "0") != 0 &&
             strcmp(sOpt, "a") != 0 &&
			 strcmp(sOpt, "b"))) 
		{		//show error message if invalid input
				printf("ERROR: Invalid key\n");
				scanf("%s", sOpt);
				nCheck = 0;
		}
		else 
			nCheck = 1;
	} 
	while (strlen(sOpt) != 1 ||
		   nCheck != 1);
			 
	//return user input
	return sOpt[0];
}

/*
getString1 allows user to enter a string input

getString1 ensures that the program will not enter an infinite loop
		   upon asking for string inputs from user

@param sString - the address where the input string will be placed

Pre-condition: User enters an input not exceeding 30 characters
Pre-condition: User only enters one word so it can be analyzed in language tools
*/
void
getString1 (char *sString)
{
	//variable declaration
	int  i;
	char ch, 
		 nl;
	
	//catch whitespace if detected
	scanf(" %c", &nl);
	if (nl == '\n')
		i = 0;
	else 
	{ //if its not a newline, copy scanned char to sString
		sString[0] = nl;
		i = 1;
	}
	
	//append to sString each character until newline is detected
	do 
	{
		scanf("%c", &ch);
		if (ch != '\n') 
		{	sString[i] = ch;
			i++;
		}
	} 
	while (ch != '\n');
	sString[i] = '\0'; //assign null character to last char of string
	
}

/*
getDigit allows user to input a number with an instruction message
		 dedicated to support functions asking for entry number

getDigit ensures that the program does not enter an infinite loop
		 in case a character is inputted instead of a number

@return a number to be used by other functions
*/

int
getDigit(void)
{
	//variable declaration
	int nValid,
		nDigit;

	//ask until user enters a valid input
	printf("\n");
	do 
	{
		printf("Enter entry #\n");
		nValid = scanf("%d", &nDigit);

		//if user did not enter an integer
		if (nValid != 1) 
			scanf("%*s"); //ignore string

	} 
	while (nValid != 1);

	printf("\n");
	//return user input
	return nDigit;
}

/*
getDigit2 allows user to input a number with an instruction message
		  dedicated to support functions asking for the index 
		  of a language-translation pair

@return a number to be used by other functions
*/
int
getDigit2(void) 
{
	//variable declaration
	int nValid,
		nDigit;

	//ask until user enters a valid input
	do 
	{	printf("Enter language-translation pair #\n");
		nValid = scanf("%d", &nDigit);

	//if user did not enter an integer
		if (nValid != 1) 
			scanf("%*s"); //ignore string

	} 
	while (nValid != 1);

	printf("\n");

	//return user input
	return nDigit;
}

/*
displayExistingEntry displays single entry without sorting

displayExistingEntry supports addEntry function

@param entries - array of data structures containing all entries in manage data
@param n - the index of entries[] to be displayed
*/
void
displayExistingEntry (entry entries[], int n)
{
	//variable declaration
	int   j;
	Str30 a = "Language";
	Str30 b = "Translation";
	
	printf("Entry %d\n", n+1);
	printf("%-40s %s\n", a, b);
	
	for (j = 0; j < entries[n].nCnt; j++) 
	{	printf("%-40s ", entries[n].sLanguage[j]);
		printf("%s\n", entries[n].sTranslation[j]); 
	}
	
	printf("\n");
}

/*
checkExistingEntry checks if there is an existing entry with the 
				   inputted language translation pair

@param entries - array of data structure containing all entries in manage data
@param language - the address containing string language to search for
@param translation - the address containing the string translation to search for
@param n - is the number of existing entries
@param pMatch - the address containing the number of matching entries
@param nIndexMatch - array containing the indexes of entries to be matched to user input

@return 1 if there is existing entry with language translation pair
@return 0 if there is no existing entry with language translation pair
*/
int
checkExistingEntry (entry entries[], 
					char *language, 
					char *translation, 
					int n, int *pMatch, 
					int nIndexMatch[])
{
	//variable declaration
	int nCheck = 0;
	int i,
		j;
	
	//nCheck becomes 1 if both language and translation exists in an entry
	for (i = 0; i < n; i++) 
	{ 	for (j = 0; j < entries[i].nCnt; j++) 
		{	if (strcmp(entries[i].sLanguage[j], language) == 0 &&
				strcmp(entries[i].sTranslation[j], translation) == 0) 
			{		nCheck = 1;		
					nIndexMatch[*pMatch] = i; //store index of matching entry
					(*pMatch)++;	
					displayExistingEntry(entries, i);
			}
		}			
	}

	//return 1 or 0 as a result of checking existing entry
	return nCheck;
}

/*
addUniqueTranslation lets user add a unique translation in one entry

@param entries - contains all entries of user in manage data
@param nOpt - contains user's chosen index in entry
@param n - number of language-translation pairs in current entry
*/
void
addUniqueTranslation (entry entries[], 
					  int nOpt)
{
	//variable declaration
	int   i,
		  j;
	Str30 sTempLanguage,
		  sTempTranslation;
	int   nUnique;	  
		  
		  
	//store in j the amount of language-translation pairs in chosen entry
	j = entries[nOpt].nCnt; 
			
	//add unique language-translation pair to chosen entry
	do 
	{	printf("Enter unique language: ");
		getString1(sTempLanguage);
		printf("Enter unique translation: ");
		getString1(sTempTranslation);
		printf("\n");
				
		nUnique = 0; //reset value
				
		for (i = 0; i < j; i++) 
		{	//scan if inputted same language is found in entry chosen
			//show error message and update nUnique variable to 1
			if (strcmp(entries[nOpt].sLanguage[i], sTempLanguage) == 0) 
			{		printf("ERROR: A similar language is already in the entry\n");
					printf("Please input a unique language-translation pair\n");
					printf("\n");
					nUnique = 1;
					
			}
		}
				
		//store unique language-translation pair to chosen entry and update count
		if (nUnique == 0) 
		{	strcpy(entries[nOpt].sLanguage[j], sTempLanguage);
			strcpy(entries[nOpt].sTranslation[j], sTempTranslation);
			entries[nOpt].nCnt++;
			printf("new translation added\n\n");
			nUnique = 0; //ensure to end loop
		}
	} 
	while (nUnique == 1);
}

/*
addEntry lets user add entries for manage data

addEntry accepts valid translations input where they are unique from each other

@param entries - array of data structures containing list of entries in manage data
@param pEntriesCnt - address containing the number of entries with content
*/
void
addEntry (entry entries[], 
		  int *pEntriesCnt)
{
	//variable declaration
	Str30 sTempLanguage,
		  sTempTranslation;
	int   nMatchDump;
	int   nMatchDump2[1];
	char  cOpt,
		  cOpt2;
		
		//ask user for language and translation input
		//store inputs in entries
		printf("\n**********\n");
		printf("You chose to add an entry\n");
			
		//ask until inputs for language and translation is at least 1 character
		do 
		{	printf("Enter the language: ");
			getString1(sTempLanguage);
		} 
		while (strlen(sTempLanguage) < 1);
		do 
		{	printf("Enter the translation: ");
			getString1(sTempTranslation);
		} 
		while (strlen(sTempTranslation) < 1);
		printf("\n");
		
		/*	condition displays existing entry if language and translation is located in an entry
		  	condition automatically adds language-translation pair to new entry if not located
			condition adds new entry and updates number of entries if Y/y is entered
			condition does not add new entry and does not update number of entries if N/n is entered
		*/
		nMatchDump = 0; //give a value so the function below does not access an unwanted memory as a dump
		if (checkExistingEntry(entries, 
							   sTempLanguage, 
							   sTempTranslation, 
							   *pEntriesCnt, 
							   &nMatchDump, 
							   nMatchDump2) == 1) 
		{	printf("----------\n");
			printf("Is this a new entry?\n");
			printf("Enter [Y/y] if yes or [N/n] if no\n");
			printf("----------\n");
			
			cOpt = getOption3();
			printf("\n");
			
			if (cOpt == 'Y' ||
				cOpt == 'y') 
			{		strcpy(entries[*pEntriesCnt].sLanguage[0], 
						   sTempLanguage);
					strcpy(entries[*pEntriesCnt].sTranslation[0], 
						   sTempTranslation);
					entries[*pEntriesCnt].nCnt++; //updates number of pairs in this entry
					(*pEntriesCnt)++; //updates number of entries 
					printf("New entry has been added\n");
			}
			else
				printf("No new entry was added\n");
			
		}
		else 
		{	printf("new entry added\n");
			strcpy(entries[*pEntriesCnt].sLanguage[0], 
				   sTempLanguage);
			strcpy(entries[*pEntriesCnt].sTranslation[0], 
				   sTempTranslation);
			entries[*pEntriesCnt].nCnt++; //updates number of pairs in this entry
			(*pEntriesCnt)++; //updates number of entries 
		}
		
		printf("\n");
		
	/*	ask user to continue adding entry with navigation key
		getOption2() returns 1 to continue adding language-translation pair
		getOption2() returns 2 to return to menu
	*/		
	do 
	{	cOpt2 = getOption2();
		printf("\n");
		
		if (cOpt2 == '1') 
			//call function to add unique translation to current entry
			addUniqueTranslation(entries, 
								 *pEntriesCnt - 1);
		
		if (entries[*pEntriesCnt-1].nCnt == MAX_PAIR)
			printf("You have reached the maximum allowable translations for entry #%d\n", *pEntriesCnt-1);
	} 
	while (cOpt2 != '2' &&
		   entries[*pEntriesCnt-1].nCnt < MAX_PAIR);
	
	printf("**********\n\n");
}

/*
checkValidEntry asks user for input until a matching index is entered

@param nIndexMatch - array containing the indexes of entries to be matched with user input
@param n - number of indexes in nIndexMatch[]

@return index of a valid entry from user's input
*/
int
checkValidEntry(int nIndexMatch[], 
				int n)
{
	//variable declaration
	int nValid, //checks for successful run of scanf
		nCheck, //checks if input is a match in nIndexMatch[]
		nOpt; //contains user's input
	int i;
	
	nCheck = 0;
	do 
	{	//check if the data type of input is valid in scanf
		nValid = scanf("%d", &nOpt);
		nOpt--; //adjust index
		if (nValid != 1) 
			scanf("%*s"); //ignore string
		
		//check if input can be found in array of index matches
		for (i = 0; i < n; i++) 
		{	if (nOpt == nIndexMatch[i])
				nCheck = 1;
		}	
		
		//display error message if there is an invalid input
		if (nCheck == 0 || nValid != 1)
			printf("Please enter a valid entry #\n");
		
	} 
	while (nCheck != 1 || nValid != 1);
	
	//return user's input
	return nOpt;
}

/*	
addTranslations lets user add translations as a manage data feature

addTranslations checks if there are duplicate translations being added

addTranslations lets user keep adding translations for a located translation pair
				while accounting for the maximum number of translations in an entry

@param entries - array containing a list of entries in manage data
@param n - number of entries with content
*/

void
addTranslations (entry entries[], 
				 int n)
{
	//variable declaration
	Str30 sTempLanguage,
		  sTempTranslation;
	int   nMatch = 0;
	int   nIndexMatch[n]; //array stores index of matching entries
	int   j;
	int   nOpt;
	char  sOpt;
	int   nValid;

	//show user instructions and ask for needed input
	printf("\n**********\n");
	printf("You chose to add translations\n");
	printf("Enter existing Language-Translation pair\n");
	printf("language: ");
	getString1(sTempLanguage);
	printf("translation: ");
	getString1(sTempTranslation);

	//if there are existing entries, store their indexes in nIndexMatch and run the following
	printf("\n");
	if (checkExistingEntry(entries, 
						   sTempLanguage, 
						   sTempTranslation, 
						   n, 
						   &nMatch, 
						   nIndexMatch) == 1) 
	{	//ask user to choose which entry to add the language-translation pair to
		//if matching entries is more than 1
		if (nMatch > 1) 
		{	printf("Enter entry # to add translation to:\n");
			
			//accept only index matches as valid input
			nOpt = checkValidEntry(nIndexMatch, nMatch);
			printf("\n");

			//ensure that user's choice does not add translation to a full entry
			nValid = 1;
			if (entries[nOpt].nCnt == MAX_PAIR) 
			{	nValid = 0;
				printf("You have reached maximum allowable translations for entry #%d\n", nOpt+1);
			}
		
			if (nValid) 
			{	//ask user if they want to enter another language-translation pair to same entry
				//accepts only Y/y/N/n as input
				do 
				{	//store in j the current amount of language-translation pairs in chosen entry
					j = entries[nOpt].nCnt; 
					//repeat until language-translation pair count is increased by 1
					do 
					{	//add unique language-translation pair to chosen entry
						addUniqueTranslation(entries, nOpt);	
					} 
					while (entries[nOpt].nCnt != j + 1);

					//inform user if they have exceeded the capacity of chosen entry
					if (entries[nOpt].nCnt == MAX_PAIR)
						printf("You have reached the maximum allowable translations for entry #%d\n", nOpt+1);
					else 
					{	printf("..........\n");
						printf("Do you want to add another language-translation pair to entry #%d?\n", nOpt+1);
						printf("Enter [Y/y] if yes\n");
						printf("Enter [N/n] if no\n");
						printf("..........\n");
				
						sOpt = getOption3(); //ask user option input
						printf("\n");
					}	
				}
				while (sOpt != 'n' &&
					   sOpt != 'N' && 
					   entries[nOpt].nCnt < MAX_PAIR);

				printf("\n**********\n");
				printf("\n");
			}
		}
		else 
		{ //if matching entries is only one, automatically add to it
			nOpt = nIndexMatch[0]; //user's option is automatically the only index

			//ensure that user's choice does not add translation to a full entry
			nValid = 1;
			if (entries[nOpt].nCnt == MAX_PAIR) 
			{	nValid = 0;
				printf("You have reached maximum allowable translations for entry #%d\n", nOpt+1);
			}

			if (nValid) 
			{	//ask user if they want to enter another language-translation pair to same entry
				//accepts only Y/y/N/n as input
				do 
				{	//store in j the current amount of language-translation pairs in chosen entry
					j = entries[nOpt].nCnt; 
					//repeat until language-translation pair count is increased by 1
					do 
					{	//add unique language-translation pair to chosen entry
						addUniqueTranslation(entries, nOpt);	
					} 
					while (entries[nOpt].nCnt != j + 1);

				//inform user if they have exceeded the capacity of the current entry
					if (entries[nOpt].nCnt == MAX_PAIR)
						printf("You have reached maximum allowable translations for entry #%d\n", nOpt+1);
					else 
					{	printf("..........\n");
						printf("Do you want to add another language-translation pair to entry #%d?\n", nOpt+1);
						printf("Enter [Y/y] if yes\n");
						printf("Enter [N/n] if no\n");
						printf("..........\n");
				
						sOpt = getOption3(); //ask user for option input
					}
				} 
				while (sOpt != 'n' &&
					   sOpt != 'N' &&
					   entries[nOpt].nCnt < MAX_PAIR);

				printf("\n**********\n");
				printf("\n");
			}
		}	
	}
	else 
	{ 	//show error message if user entered an invalid entry input
		printf("ERROR: Entry does not exist\n");
		printf("Please choose [1] to Add Entry first\n");
		printf("**********\n");
		printf("\n");
	}
}

/*
displayEntry displays all language-translation pairs
			 inside one entry and sorts them based on language ascii

@param entries - array containing all the entries in manage data
@param n - index of the entry to be displayed
*/
void
displayEntry(entry entries[], 
			 int n)
{
	//variable declaration
	int   i,
		  j;
	int   min;
	Str30 sTempLanguage,
		  sTempTranslation;
	Str30 a = "Language";
	Str30 b = "Translation";

	//sort the language-translation pairs inside entry by selection sort algorithm
	for (i = 0; i < entries[n].nCnt-1; i++) 
	{	min = i;

		//store the index with least ascii value
		for (j = i + 1; j < entries[n].nCnt; j++) 
		{	if (strcmp(entries[n].sLanguage[min], 
				entries[n].sLanguage[j]) < 0)
					min = j;
		}

		if (i != min) 
		{ 	//swap
			strcpy(sTempLanguage, entries[n].sLanguage[min]);
			strcpy(entries[n].sLanguage[min], entries[n].sLanguage[i]);
			strcpy(entries[n].sLanguage[i], sTempLanguage);

			strcpy(sTempTranslation, entries[n].sTranslation[min]);
			strcpy(entries[n].sTranslation[min], entries[n].sTranslation[i]);
			strcpy(entries[n].sTranslation[i], sTempTranslation);
		}
	}

	//display results
	printf("    Entry #%d\n", n+1);
	printf("    %-40s %s\n", a, b);

	for (i = 0; i < entries[n].nCnt; i++) 
	{	printf("#%d  ", i+1);
		printf("%-43s ", entries[n].sLanguage[i]);
		printf("%s\n", entries[n].sTranslation[i]);
	}
}

/*
displayAllEntries displays all the entries with an input

displayAllEntries displays the entries one by one using navigation key
				  where P displays previous entry, N for next entry, 
				  and X to return to menu

@param entries - array containing all entries in manage data
@param n - number of entries with an input
*/

void
displayAllEntries(entry entries[], 
				  int n)
{
	//variable declaration
	int i;
	char cOpt;

	i = 0; //index of entry being displayed
	do 
	{	printf("----------\n");
		displayEntry(entries, i);
		printf("----------\n");

		printf("..........\n");
		printf("Options:\n");
		printf("Enter [P/p] to display previous entry\n");
		printf("Enter [N/n] to display next entry\n");
		printf("Enter [X/x] to exit display\n");
		printf("..........\n");
		cOpt = getOption4(); //ask for user's option

		if (cOpt == 'p' || cOpt == 'P') 
		{	if (i == 0) 
			{	printf("\n");
				printf("..........\n");
				printf("You are displaying the first entry\n");
				printf("..........\n");
				printf("\n");
			}
			else
				i--;
		}
		if (cOpt == 'n' || cOpt == 'N') 
		{	if (i == n-1) 
			{
				printf("\n");
				printf("..........\n");
				printf("You are already at the last entry\n");
				printf("..........\n");
				printf("\n");
			}
			else
				i++;
		}

	} 
	while (cOpt != 'x' && cOpt != 'X');
}

/*
searchWord asks user for a word to search for in entries

searchWord displays all matching entries with a navigation key where
		   P displays previous entry, N for next entry, and X to return to menu

@param entries - array containing all entries in manage data
@param n - number of entries with input
*/
void
searchWord(entry entries[], 
		   int n) {
	//variable declaration
	int   i,
		  j;
	int   nFoundCnt = 0;
	Str30 sKey;
	char  cOpt;
	int   nIndexMatch[n];

	//show instruction and ask for word to search for
	printf("\n**********\n");
	printf("Enter word to search: ");
	getString1(sKey);
	printf("\n");

	//store matching indexes in nIndexMatch array
	for (i = 0; i < n; i++) 
	{	for (j = 0; j < entries[i].nCnt; j++) 
		{	//store index in temp array if key is found
			if (strcmp(entries[i].sTranslation[j], sKey) == 0) 
			{	nIndexMatch[nFoundCnt] = i;
				nFoundCnt++;
			}
		}
	}

	//if word has been located in at least one entry, display
	if (nFoundCnt > 0) 
	{	printf("%s has been located\n\n", sKey);
		i = 0;
		do 
		{	displayEntry(entries, nIndexMatch[i]);
			printf("\n");

			printf("..........\n");
			printf("Options:\n");
			printf("Enter [P/p] to display previous entry\n");
			printf("Enter [N/n] to display next entry\n");
			printf("Enter [X/x] to return to menu\n");
			printf("..........\n");
			cOpt = getOption4();

			if (cOpt == 'p' || cOpt == 'P') 
			{	if (i == nIndexMatch[0]) 
				{	printf("\n");
					printf("..........\n");
					printf("You are displaying the first entry\n");
					printf("..........\n");
					printf("\n");
				}
				else
					i--;
			}
			if (cOpt == 'n' || cOpt == 'N') 
			{	if (i == nIndexMatch[nFoundCnt-1]) 
				{	printf("\n");
					printf("..........\n");
					printf("You are already at the last entry\n");
					printf("..........\n");
					printf("\n");
				}
				else
					i++;
			}
		} 
		while (cOpt != 'x' && cOpt != 'X');

		printf("\n**********\n\n");
	}
	else 
	{ 	//inform user word was not found
		printf("\n");
		printf("Word not found\n");
		printf("**********\n");
		printf("\n");
	}
	
}

/*
searchTranslation asks for translation to search for

searchWord displays all matching entries with a navigation key where
		   P displays previous entry, N for next entry, and X to return to menu

@param entries - array of data structures containing entries in manage data
@param n - number of entries with input
*/
void
searchTranslation(entry entries[], 
				  int n)
{
	//variable declaration
	int   i,
		  j;
	int   nFoundCnt = 0;
	Str30 sLanguageKey,
		  sTranslationKey;
	char  cOpt; 
	int   nIndexMatch[n];

	printf("\n**********\n\n");
	//show instruction and ask for language-translation pair
	printf("Enter language-translation pair to search\n");
	printf("language: ");
	getString1(sLanguageKey);
	printf("translation: ");
	getString1(sTranslationKey);
	printf("\n");

	//store indexes of matching entries in nIndexMatch array
	for (i = 0; i < n; i++) 
	{	for (j = 0; j < entries[i].nCnt; j++) 
		{	if (strcmp(entries[i].sLanguage[j], sLanguageKey) == 0 &&
				strcmp(entries[i].sTranslation[j], sTranslationKey) == 0) 
			{		nIndexMatch[nFoundCnt] = i;
					nFoundCnt++;
			}
		}
	}

	//if at least one entry contains translation, display
	if (nFoundCnt > 0) 
	{	printf("Translation has been located\n\n");
		i = 0;
		do 
		{	displayEntry(entries, nIndexMatch[i]);
			printf("\n");
			printf("..........\n");
			printf("Options:\n");
			printf("Enter [P/p] to display previous entry\n");
			printf("Enter [N/n] to display next entry\n");
			printf("Enter [X/x] to return to menu\n");
			printf("..........\n");
			cOpt = getOption4();

			if (cOpt == 'p' || cOpt == 'P') 
			{	if (i == 0) {
					printf("\n");
					printf("..........\n");
					printf("You are displaying the first entry\n");
					printf("..........\n");
					printf("\n");
				}
				else
					i--;
			}
			if (cOpt == 'n' || cOpt == 'N') 
			{		if (i == nFoundCnt-1) {
					printf("\n");
					printf("..........\n");
					printf("You are already at the last entry\n");
					printf("..........\n");
					printf("\n");
				}
				else
					i++;
			}
		} 
		while (cOpt != 'x' && cOpt != 'X');

		printf("\n**********\n\n");
	}
	else 
	{	printf("\n");
		printf("Translation does not exist\n");
		printf("**********\n");
		printf("\n");
	}

}

/*
modifyEntry displays lists of entries in manage data and allows
			user to choose among them

modifyEntry disregards modifications that will modify an entry to have
			duplicate translations

@param entries - array of data structures containing entries in manage data
@param n - number of entries with input
*/
void
modifyEntry(entry entries[], 
		    int n)
{
	//variable declaration
	int   nIndexMatch[n], //contains index of entries with content
		  nIndexMatch2[MAX_PAIR]; //contains index of language-translation pair
	int   i;
	int   nOpt;
	int   nCheck, //becomes 1 if user chose existing entry
		  nValid; //becomes 1 if there is no duplicate language in entry
	int   nPair;
	char  cChoice,
		  cChoice2;
	Str30 sLanguage,
		  sTranslation;

	printf("\n**********\n");
	printf("You chose to modify an entry\n");

	printf("Current entries will now be displayed\n");
	printf("\n");
	displayAllEntries(entries, n);

	//store in nIndexMatch[] values to be accepted
	i = 0;
	do 
	{	nIndexMatch[i] = i;
		i++;
	} while (i < n);

	printf("\n..........\n");
	printf("Which do you want to modify?\n");
	printf("..........\n");
	//get entry # to be modified
	nOpt = getDigit();
	nOpt--; //adjust entry

	nCheck = 0;
	for (i = 0; i < n; i++) 
	{	if (nIndexMatch[i] == nOpt)
			nCheck = 1;
	}
	
	if (nCheck == 1) 
	{	//store in nIndexMatch[] values to be accepted
		i = 0;
		do 
		{	nIndexMatch2[i] = i;
			i++;
		} 
		while (i < entries[nOpt].nCnt);

		do 
		{	printf("You chose to modify:\n");
			displayEntry(entries, nOpt);
			
			//get index of language-translation pair
			nCheck = 0;
			do 
			{	nPair = getDigit2();
				nPair--; //adjust index of pair
				for (i = 0; i < entries[nOpt].nCnt; i++) 
				{	if (nIndexMatch2[i] == nPair)
						nCheck = 1;
				}
				if (nCheck == 0) 
				{	printf("..........\n");
					printf("ERROR: Invalid number detected\n");
					printf("..........\n");
				}	
			} 
			while (nCheck == 0);
			printf("You chose to modify\n");
			printf("#%d   %-43s %s\n", nPair+1, 
									   entries[nOpt].sLanguage[nPair], 
									   entries[nOpt].sTranslation[nPair]);

			//ask if user wants to modify language or translation
			do 
			{
				cChoice = getOption5();
			} 
			while (cChoice != '1' && cChoice != '2');

			if (cChoice == '1') 
			{
				printf("new language: ");
				getString1(sLanguage);

				//only add if there is no duplicate language in current entry
				nValid = 1;
				for (i = 0; i < entries[nOpt].nCnt; i++) 
				{	if (strcmp(sLanguage, entries[nOpt].sLanguage[i]) == 0)
						nValid = 0;
				}
				if (nValid)
					strcpy(entries[nOpt].sLanguage[nPair], sLanguage);
				else
					printf("ERROR: Duplicate language has been detected\n");
			}
			else 
			{	printf("new translation: ");
				getString1(sTranslation);
				strcpy(entries[nOpt].sTranslation[nPair], sTranslation);
			}

			cChoice2 = getOption6();
			//user enters 1 to keep modifying the entry
			//user enters 2 to return to menu;
		} 
		while (cChoice2 != '2');

		printf("\n**********\n");
	}
	else 
	{ //display error message if input is invalid entry #
		printf("\n");
		printf("**********\n");
		printf("You did not enter a valid number\n");
		printf("**********\n");
		printf("\n");
	}
}

/*
deleteEntry allows user to delete an entire entry from manage data
			and updates count of entries with content

@param entries - array of data structures containing entries in manage data
@param pEntriesCnt - address containing the number of entries with content
*/
void
deleteEntry(entry entries[], 
			int *pEntriesCnt)
{
	//variable declaration
	int nIndexMatch[*pEntriesCnt]; //contains index of entries with content;
	int i,
		nOpt;
	int nCheck;

	//display all entries before asking user which to delete
	printf("\n**********\n");
	printf("You chose to delete entry\n");
	printf("Current entries will now be displayed\n");
	displayAllEntries(entries, *pEntriesCnt);

	i = 0;
	//initialize contents of nIndexMatch
	do 
	{
		nIndexMatch[i] = i;
		i++;
	} while (i < *pEntriesCnt);

	//ask for entry # to delete
	nCheck = 0;
	do 
	{
		nOpt = getDigit();
		nOpt--; //adjust index of entry

		for (i = 0; i < *pEntriesCnt; i++) 
		{	if (nIndexMatch[i] == nOpt)
				nCheck = 1;
		}
	} 
	while (nCheck != 1);

	//inform user of their chosen entry
	printf("You chose to delete\n");
	displayEntry(entries, nOpt);

	//delete chosen entry #
	for (i = nOpt; i < (*pEntriesCnt)-1; i++)
		entries[i] = entries[i + 1];
	(*pEntriesCnt)--;

	printf("**********\n");
	printf("\n");
}

/*
deleteTranslation allows user to delete translation chosen entry

deleteTranslation updates count of entries with content in manage data
				  when it does not contain any translations

@param entries - array of data structures containing entries in manage data
@param pCnt - address containing count of entries with content in manage data
*/
void 
deleteTranslation(entry entries[], 
				  int *pCnt)
{
	//variable declaration
	int nIndexMatch[*pCnt]; //contains index of entries with content
	int nIndexMatch2[MAX_PAIR]; //contains index of language-pairs in entry
	int i;
	int nOpt,
		nOpt2;
	int nCheck;
	char cChoice;

	//initialize contents of nIndexMatch[]
	i = 0;
	do 
	{	nIndexMatch[i] = i;
		i++;
	} 
	while (i < *pCnt);

	printf("You chose to delete translation\n");

	displayAllEntries(entries, *pCnt);

	//get valid index of entries with content
	//store to nOpt
	nCheck = 0;
	do 
	{	nOpt = getDigit();
		nOpt--; //adjust index of entry

		for (i = 0; i < *pCnt; i++) 
		{	if (nIndexMatch[i] == nOpt)
				nCheck = 1;
		}
	} 
	while (nCheck != 1);

	do 
	{	//display chosen entry
		displayEntry(entries, nOpt);
		printf("\n");

		//initialize contents of nIndexMatch2[]
		i = 0;
		do 
		{	nIndexMatch2[i] = i;
			i++;
		} while (i < entries[nOpt].nCnt);

		//get valid index of pairs with content in chosen entry
		nCheck = 0;
		printf("What language-translation pair do you want delete?\n");
		do 
		{	nOpt2 = getDigit2();
			nOpt2--; //adjust index of pair
			for (i = 0; i < entries[nOpt].nCnt; i++) 
			{	if (nIndexMatch2[i] == nOpt2)
					nCheck = 1;
			}
		} 
		while (nCheck != 1);

		//show user what they chose to delete
		printf("\n");
		printf("..........\n");
		printf("You chose to delete\n");
		printf("#%d   %-43s %s\n", nOpt2 + 1, 
		   					   	   entries[nOpt].sLanguage[nOpt2], 
							   	   entries[nOpt].sTranslation[nOpt2]);
		printf("..........\n");
		printf("\n");

		//delete chosen language-translation pair
		for (i = nOpt2; i < entries[nOpt].nCnt-1; i++) 
		{	strcpy(entries[nOpt].sLanguage[i], 
				   entries[nOpt].sLanguage[i+1]);
			strcpy(entries[nOpt].sTranslation[i], 
				   entries[nOpt].sTranslation[i+1]);
		}
		entries[nOpt].nCnt--;

		//delete entry if entire content is deleted
		if (entries[nOpt].nCnt == 0) 
		{	for (i = nOpt; i < (*pCnt)-1; i++) 
			{
				entries[i] = entries[i + 1];
			}
			(*pCnt)--;
		}

		

		if (entries[nOpt].nCnt != 0) 
		{	printf("..........\n");
			printf("Do you want to delete another language-translation pair?\n");
			printf("Enter [Y/y] if yes\n");
			printf("Enter [N/n] if no\n");
			printf("..........\n");

			cChoice = getOption3();
		}
		else
			cChoice = 'n';

		printf("\n");
	} 
	while (cChoice == 'y' ||
		   cChoice == 'Y');
	
	printf("**********\n");	
}

/*
import lets user import entries to be used in manage data from a text file

import disregards exceeding entries from 150 if the file
	   being imported exceeds what is expected then shows
	   an error message

import disregards exceeding language-translation pairs from 10
	   in an entry if the file being imported exceeds what is
	   expected then shows an error message

@param entries - array of data structures containing entries in manage data
@param n - address containing number of entries in manage data
*/
void
import(entry entries[], 
	   int *n)
{
	//variable declaration
	Str30 sName,
		  sTemp1,
		  sShort;
	FILE  *fp;
	char  ch1,
		  ch2,
		  cOpt;
	entry tempEntry;
	int   nCheck = 1, //becomes false when error is detected
		  nValid = 1; //such as duplicate entries or languages in an entry
	int   nExist;
	int   i,
		  j = 0, //for pair indexes
		  k;
	int   min;
	Str30 sTempLanguage,
		  sTempTranslation,
		  sTempLanguage2; //for checking unique language
	int   nCnt1,
		  nCnt2;
	Str30 a = "Language";
	Str30 b = "Translation";

	tempEntry.nCnt = 0;

	/*nExist is 1 if there are existing entries prior to running import
	  and 0 if there are none
	*/
	if (*n > 0)
		nExist = 1;
	else
		nExist = 0;

	//ask user for file name to import
	printf("\n**********\n");
	printf("Enter filename of file to be imported: ");
	getString1(sName);

	fp = fopen(sName, "r");

	if (fp == NULL)
		printf("File does not exist\n");
	else 
	{	//scanning continues until end of file or if entries reached max
		while (nCheck) 
		{	if (*n >= MAX_ENTRY || feof(fp)) 
			{	nCheck = 0;

				if (*n >= MAX_ENTRY) 
				{	printf("Maximum number of entries have been reached\n");
					printf("Exceeding entries will be disregarded\n");
				}
			}
			else 
			{ 	//scan one line
				fscanf(fp, "%c%s", &ch1, sTemp1);
				
				//if char is not a newline, keep storing in tempEntry
				if (ch1 != '\n') 
				{	sShort[0] = ch1;
					sShort[1] = '\0';
					strcat(sShort, sTemp1);

					//remove colon by replacing with null
					sShort[strlen(sShort)-1] = '\0';
				
					//store in tempEntry the language-translation pair
					strcpy(tempEntry.sLanguage[j], sShort);
					fscanf(fp, "%s%c", tempEntry.sTranslation[j], &ch2);

					//update number of pairs in tempEntry
					tempEntry.nCnt++;
					j++; //variable is equal to tempEntry.Cnt for now to shorten
				}
				//if char is newline and there are existing entries
				if (ch1 == '\n' && nExist) 
				{	//exceeding translations more than 10 will be disregarded
					if (tempEntry.nCnt > MAX_PAIR) 
					{	printf("ERROR: Entry has reached more than 10 translations\n");
						printf("Exceeding translations will be disregarded for entry #%d\n", *n);
						tempEntry.nCnt = MAX_PAIR;
					}
					
					//sort tempEntry
					for (i = 0; i < tempEntry.nCnt-1; i++) 
					{	min = i;

						for (j = i + 1; j < tempEntry.nCnt; j++) 
						{	if (strcmp(tempEntry.sLanguage[min], 
									   tempEntry.sLanguage[j]) > 0) 
							{
								min = j;
							}
								
						}

						if (i != min) 
						{	strcpy(sTempLanguage, 
								   tempEntry.sLanguage[min]);
							strcpy(tempEntry.sLanguage[min], 
								   tempEntry.sLanguage[i]);
							strcpy(tempEntry.sLanguage[i], 
								   sTempLanguage);

							strcpy(sTempTranslation, 
								   tempEntry.sTranslation[min]);
							strcpy(tempEntry.sTranslation[min], 
								   tempEntry.sTranslation[i]);
							strcpy(tempEntry.sTranslation[i], 
								   sTempTranslation);
						}
					}

					//display contents of tempEntry
					printf("Do you want to add this entry?\n\n");
					printf("    %-40s %s\n", a, b);
					for (i = 0; i < tempEntry.nCnt; i++) 
					{	printf("#%d   %-43s %s\n", i, 
												   tempEntry.sLanguage[i], 
												   tempEntry.sTranslation[i]);
					}

					//ask user if tempEntry contents will be added
					printf("\n..........\n");
					printf("Options:\n");
					printf("Enter [y/Y] if yes\n");
					printf("Enter [n/N] if no\n");
					printf("..........\n");
					cOpt = getOption3();

					if (cOpt == 'Y' || cOpt == 'y') 
					{	/*do not add and inform user if tempEntry contents
						  are already in one existing entry and
						  check for duplicate entries
						*/
						for (i = 0; i < *n; i++) 
						{	for (j = 0; j < tempEntry.nCnt; j++) 
							{	if (strcmp(tempEntry.sLanguage[j], 
										   entries[i].sLanguage[j]) == 0 &&
									strcmp(tempEntry.sTranslation[j], 
										   entries[i].sTranslation[j]) == 0)
								{
									nValid = 0;
								}			
								else
									nValid = 1;
							}
						}

						//delete duplicate language content in entry
						for (i = 0; i < tempEntry.nCnt; i++) 
						{	strcpy(sTempLanguage2, 
								   tempEntry.sLanguage[i]);
							for (j = 0; j < tempEntry.nCnt; j++) 
							{	if (strcmp(sTempLanguage2, 
										   tempEntry.sLanguage[j]) == 0 &&
									i != j) 
								{	printf("ERROR: a duplicate language has been located\n");

										for (k = i; k < tempEntry.nCnt-1; k++) 
										{	strcpy(tempEntry.sLanguage[i], 
												   tempEntry.sLanguage[i + 1]);
											strcpy(tempEntry.sTranslation[i], 
												   tempEntry.sTranslation[i+1]);
										}
										tempEntry.nCnt--;

										printf("Duplicate language has been automatically deleted\n");
								}
							}
						}

						//check for duplicate entries
						for (i = 0; i < *n; i++) 
						{	nCnt1 = entries[i].nCnt;
							nCnt2 = 0;

							for (j = 0; j < tempEntry.nCnt; j++) 
							{	if (strcmp(tempEntry.sLanguage[j], 
										   entries[i].sLanguage[j]) == 0 &&
									strcmp(tempEntry.sTranslation[j],
										   entries[i].sTranslation[j]) == 0)
								{
										nCnt2++;
								}
										
							}
							//if tempEntry contents matches with at least one entry, 
							//it is no longer valid
							if (nCnt1 == nCnt2)
								nValid = 0;	
						}

						//if user said yes and entry contents are unique, add to entries
						if (nValid) 
						{	for (i = 0; i < tempEntry.nCnt; i++) 
							{	strcpy(entries[*n].sLanguage[i], 
									   tempEntry.sLanguage[i]);
								strcpy(entries[*n].sTranslation[i], 
									   tempEntry.sTranslation[i]);
								entries[*n].nCnt++;
							}
						}
						else 
						{	printf("ERROR: A duplicate entry has been located\n");
							printf("Adding of this entry will be skipped\n");
						}
					}
					
					//update values
					j = 0;
					nValid = 1;
					tempEntry.nCnt = 0;
					(*n)++;

					//store to tempEntry sLanguage scanned value in sTemp1
					//but replace colon in sTemp1 with null first
					sTemp1[(strlen(sTemp1)-1)] = '\0';
					strcpy(tempEntry.sLanguage[j], sTemp1);
					//store to tempEntry sTranslation the other pair
					fscanf(fp, "%s%c", tempEntry.sTranslation[j], &ch2);

					//update values
					j++;
					tempEntry.nCnt++;

				}
				//if char is newline and there are no existing entries
				//automatically add all read content to entries
				else if (ch1 == '\n' && !nExist) 
				{	//exceeding translations more than 10 will be disregarded
					if (tempEntry.nCnt > MAX_PAIR) 
					{	printf("ERROR: Entry has reached more than 10 translations\n");
						printf("Exceeding translations will be disregarded for entry #%d\n", *n);
						tempEntry.nCnt = MAX_PAIR;
					}
				
					//sort tempEntry
					for (i = 0; i < tempEntry.nCnt-1; i++) 
					{	min = i;

						for (j = i + 1; j < tempEntry.nCnt; j++) 
						{	if (strcmp(tempEntry.sLanguage[min], 
									   tempEntry.sLanguage[j]) > 0) 
							{
								min = j;
							}	
						}

						if (i != min) 
						{	strcpy(sTempLanguage, 
								   tempEntry.sLanguage[min]);
							strcpy(tempEntry.sLanguage[min], 
								   tempEntry.sLanguage[i]);
							strcpy(tempEntry.sLanguage[i], 
								   sTempLanguage);

							strcpy(sTempTranslation, 
								   tempEntry.sTranslation[min]);
							strcpy(tempEntry.sTranslation[min], 
								   tempEntry.sTranslation[i]);
							strcpy(tempEntry.sTranslation[i], 
								   sTempTranslation);
						}
					}

					//delete duplicate language content in entry
					for (i = 0; i < tempEntry.nCnt; i++) 
					{	strcpy(sTempLanguage2, 
							   tempEntry.sLanguage[i]);
						for (j = 0; j < tempEntry.nCnt; j++) 
						{	if (strcmp(sTempLanguage2, tempEntry.sLanguage[j]) == 0 &&
								i != j) 
							{	printf("ERROR: a duplicate language has been located\n");

								for (k = i; k < tempEntry.nCnt-1; k++) 
								{	strcpy(tempEntry.sLanguage[i], 
										   tempEntry.sLanguage[i + 1]);
									strcpy(tempEntry.sTranslation[i], 
										   tempEntry.sTranslation[i+1]);
								}
								tempEntry.nCnt--;

								printf("Duplicate language has been automatically deleted\n");
							}
						}	
					}

					//check for duplicate entries
					for (i = 0; i < *n; i++) 
					{	nCnt1 = entries[i].nCnt;
						nCnt2 = 0;

						for (j = 0; j < tempEntry.nCnt; j++) 
						{	if (strcmp(tempEntry.sLanguage[j], entries[i].sLanguage[j]) == 0 &&
								strcmp(tempEntry.sTranslation[j], entries[i].sTranslation[j]) == 0)
									nCnt2++;
						}
						//if tempEntry contents matches with at least one entry, 
						//it is no longer valid
						if (nCnt1 == nCnt2)
							nValid = 0; 
					}
					//add only unique entries
					if(nValid) 
					{	for (i = 0; i < tempEntry.nCnt; i++) 
						{	strcpy(entries[*n].sLanguage[i], 
								   tempEntry.sLanguage[i]);
							strcpy(entries[*n].sTranslation[i], 
								   tempEntry.sTranslation[i]);
							entries[*n].nCnt++;
						}

						//update values
						j = 0;
						tempEntry.nCnt = 0;
						(*n)++;
					}
					else 
					{	printf("ERROR: A duplicate entry has been located\n");
						printf("Adding of this entry will be skipped\n");
					}

					//update values
					nValid = 1;

					//store to tempEntry sLanguage scanned value in sTemp1
					//but replace colon in sTemp1 with null first
					sTemp1[(strlen(sTemp1)-1)] = '\0';
					strcpy(tempEntry.sLanguage[j], sTemp1);
					//store to tempEntry sTranslation the other pair
					fscanf(fp, "%s%c", tempEntry.sTranslation[j], &ch2);

					//update values
					j++;
					tempEntry.nCnt++;
				}		
			}
		}
		
		fclose(fp);
	}
	
	printf("Done\n");
	printf("\n**********\n");
}

/*
export allows user to export content of entries to a text file

@param entries - array of data structures containing entries in manage data
@param n - contains amount of entries with content in manage data
*/

void
export(entry entries[], 
	   int n)
{
	Str30 sName;
	FILE *fp;
	int i,
		j;

	printf("\n**********\n\n");
	printf("You chose to export\n");
	printf("Enter filename: ");
	scanf("%s", sName);

	fp = fopen(sName, "w");

	for (i = 0; i < n; i++) 
	{	for (j = 0; j < entries[i].nCnt; j++) 
		{	fprintf(fp, "%s: %s\n", entries[i].sLanguage[j],
									entries[i].sTranslation[j]);
		}

		fprintf(fp, "\n");
	}

	fclose(fp);

	printf("Successfully exported to %s\n", sName);
	printf("**********\n\n");
}

/*
simpleTranslation allows user to translate words in a sentence
				  to the user's chosen language provided
				  that the information is in an entry
@param entries2 - array of data structures containing entries in language tool
@param n - number of entries with content in language tool

Pre-condition: User enters a sentence without leading or trailing spaces
*/
void
simpleTranslation(entry entries2[], 
				  int n)
{
	//variable declaration
	Str150 sSentence;
	int    i,
		   j,
		   k,
		   l,
		   m;
	Str30  sWords[MAX_ENTRY];
	Str30  sSource,
		   sResult;
	char   cOpt;
	
	printf("\n**********\n\n");

	//show user instruction and ask for languages and sentence
	printf("What language do you want to translate from?\n");
	getString1(sSource);
	printf("Enter sentence: ");
	getString1(sSentence);
	printf("What language do you want it to be translated to?\n");
	getString1(sResult);

	//remove special characters
	for (i = 0; i < strlen(sSentence); i++) 
	{	if (sSentence[i] == ',' ||
			sSentence[i] == '.' ||
			sSentence[i] == '!' ||
			sSentence[i] == '?') 
		{	for (j = i; j < strlen(sSentence); j++) 
			{
				sSentence[j] = sSentence[j + 1]; 
			}
		}
	}
	
	//tokenization of words
	j = 0; //for words
	l = 0; //for letters
	for (i = 0; i < strlen(sSentence); i++) 
	{	if (sSentence[i] == ' ') 
		{	sWords[j][l] = '\0';
			j++; //new word
			i++; //next character 
			l = 0; //reset letters for new word
		}

		sWords[j][l] = sSentence[i];
		l++;
	}
	sWords[j][l] = '\0';
	j++;

	for (l = 0; l < j; l++) 
	{ //loop all words
		for (i = 0; i < n; i++) 
		{ //scan all entries
			for (m = 0; m < entries2[i].nCnt; m++) 
			{ //scan all pairs
				if (strcmp(sWords[l], entries2[i].sTranslation[m]) == 0 && //if word is found
					strcmp(sSource, entries2[i].sLanguage[m]) == 0) //if language is also matching
				{ 	for (k = 0; k < entries2[i].nCnt; k++) 
					{	//if desired translation is found in same entry
						if (strcmp(entries2[i].sLanguage[k], sResult) == 0) 
							strcpy(sWords[l], entries2[i].sTranslation[k]);
					}	
				}
			}
		}
	}

	printf("\n");
	printf("Translation:\n");
	for (i = 0; i < j; i++)
		printf("%s ", sWords[i]);


	//ask the user for another text with same source and output language
	do 
	{	printf("\n\n..........\n");
		printf("Do you want to translate another text?\n");
		printf("Enter [Y/y] if yes\n");
		printf("Enter [N/y] if no\n");
		printf("..........\n");

		cOpt = getOption3();

		if (cOpt == 'Y' ||
			cOpt == 'y') {
				printf("\n");
				printf("Enter sentence:\n");
				getString1(sSentence);

			//remove special characters
			for (i = 0; i < strlen(sSentence); i++) 
			{	if (sSentence[i] == ',' ||
					sSentence[i] == '.' ||
					sSentence[i] == '!' ||
					sSentence[i] == '?') {
						for (j = i; j < strlen(sSentence); j++) 
						{
							sSentence[j] = sSentence[j + 1]; 
						}
				}
			}
	
			//tokenization of words
			j = 0; //for words
			l = 0; //for letters
			for (i = 0; i < strlen(sSentence); i++) 
			{	if (sSentence[i] == ' ') 
				{	sWords[j][l] = '\0';
					j++; //new word
					i++; //next character 
					l = 0; //reset letters for new word
				}

				sWords[j][l] = sSentence[i];
				l++;
			}
			sWords[j][l] = '\0';
			j++;

			for (l = 0; l < j; l++) 
			{ //loop all words
				for (i = 0; i < n; i++) 
				{ //scan all entries
					for (m = 0; m < entries2[i].nCnt; m++) 
					{ //scan all pairs
						if (strcmp(sWords[l], entries2[i].sTranslation[m]) == 0 && //if word is found
							strcmp(sSource, entries2[i].sLanguage[m]) == 0) //if language is also matching
						{ 	for (k = 0; k < entries2[i].nCnt; k++) {
								//if desired translation is found in same entry
								if (strcmp(entries2[i].sLanguage[k], sResult) == 0) 
									strcpy(sWords[l], entries2[i].sTranslation[k]);
							}	
						}
					}
				}
			}

			printf("Translation:\n");
			for (i = 0; i < j; i++)
				printf("%s ", sWords[i]);

		}

	} 
	while (cOpt != 'n' &&
		   cOpt != 'N');

	printf("\n**********\n");
	printf("\n");
}

/*
identifyMainLanguage allows user to identify the main language
					 in a sentence based on the data in entries
@param entries2 - array of data structures containing entries in language tool
@param n - amount of entries with content in language tool

Pre-condition: User enters a sentence without leading or trailing spaces
*/
void
identifyMainLanguage(entry entries2[], 
					 int n)
{
	Str150 sSentence;
	int    i,
		   j,
		   k,
		   l,
		   m = 0, //for languages and frequencies
		   p; 
	Str30  sWords[MAX_ENTRY]; //there can be 150 words at most in 150 characters;
	Str30  sLanguages[MAX_ENTRY];
	int    nPts[MAX_ENTRY];
	int    nCheck = -1;
	int    high, //for swapping
		   nTemp; 
	Str30  sTemp;
	int    r, //for looping through previously scanned entries
	       s;
	int    nValid; //checks if language-translation pair was already scanned

	//show user instruction and ask for sentence
	printf("\n**********\n\n");
	printf("You chose to identify main language\n");

	
	printf("Enter sentence: ");
	getString1(sSentence);

	//remove special characters
	for (i = 0; i < strlen(sSentence); i++) 
	{	if (sSentence[i] == ',' ||
			sSentence[i] == '.' ||
			sSentence[i] == '!' ||
			sSentence[i] == '?') {
				for (j = i; j < strlen(sSentence); j++) 
				{
					sSentence[j] = sSentence[j + 1]; 
				}
		}
	}
	
	//tokenization of words
	j = 0; //for words
	l = 0; //for letters
	for (i = 0; i < strlen(sSentence); i++) 
	{	if (sSentence[i] == ' ') 
		{	sWords[j][l] = '\0';
			j++; //new word
			i++; //next character 
			l = 0; //reset letters for new word
		}

		sWords[j][l] = sSentence[i];
		l++;
	}
	sWords[j][l] = '\0';
	j++;

	m = 0;
	//store all matching languages in sentence and store their frequencies
	for (i = 0; i < n; i++) 
	{ //scan all entries
		for (k = 0; k < j; k++) 
		{ //scan all words in sentence
			for (l = 0; l < entries2[i].nCnt; l++) 
			{ //scan all pairs
				if (strcmp(entries2[i].sTranslation[l], sWords[k]) == 0) 
				{	//check if language-translation pair was already scanned before
					nValid = 1;
					for (r = 0; r < i; r++) 
					{	for (s = 0; s < entries2[r].nCnt; s++) 
						{	if (strcmp(entries2[r].sLanguage[s], entries2[i].sLanguage[l]) == 0 &&
								strcmp(entries2[r].sTranslation[s], sWords[k]) == 0)
									nValid = 0;
						}
					}
					if (nValid) 
					{	nCheck = -1;
						//check all current sLanguages and only add if unique
						for (p = 0; p < m; p++) 
						{	if (strcmp(sLanguages[p], entries2[i].sLanguage[l]) == 0)
								nCheck = p; //store index of existing language
						}

						if (nCheck != -1)
							nPts[nCheck]++;
						else 
						{
							strcpy(sLanguages[m], 
								   entries2[i].sLanguage[l]);
							nPts[m]++;
							m++;
						}
					}
				}
			}
		}
	}

	//sort languages according to frequency
	for (i = 0; i < m - 1; i++) 
	{	high = i;

		for (j = i + 1; j < m; j++) 
		{	if (nPts[high] < nPts[j])
				high = j;
		}

		if (i != high) 
		{	strcpy(sTemp, 
				   sLanguages[i]);
			strcpy(sLanguages[i], 
				   sLanguages[high]);
			strcpy(sLanguages[high], 
				   sTemp);

			nTemp = nPts[i];
			nPts[i] = nPts[high];
			nPts[high] = nTemp;
		}
	}

	if (m > 0) 
	{	printf("Top 1 main language: %s\n", sLanguages[0]);
		
		if (strlen(sLanguages[1]) > 0)
			printf("Top 2 main language: %s\n", sLanguages[1]);
	}
	else
		printf("Main language cannot be identified\n");

	//reset points to 0
	for (i = 0; i < m; i++)
		nPts[i] = 0;


	printf("\n**********\n\n");

}