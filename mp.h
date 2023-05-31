#include <stdio.h>
#include <string.h>

#define MAX_PAIR	10
#define MAX_ENTRY	150

typedef char Str30[31]; //for translation, language, and navigation key
typedef char Str150[151]; //for language tool input

typedef struct entryTag {
	Str30 sLanguage[MAX_PAIR],
		  sTranslation[MAX_PAIR];
	int   nCnt; //number of pairs in entry
} entry;

char getOption1 			(void);
char getOption2 			(void);
char getOption3 			(void);
char getOption4 			(void);
char getOption5             (void);
char getOption6             (void);
char getOption7 			(void);
char getOption8 			(void);
void getString1 			(char *sString);
int  getDigit               (void);
int  getDigit2              (void); 
void displayExistingEntry 	(entry entries[], int n);
int  checkExistingEntry 	(entry entries[], char *language, char *translation, int n, int *pMatch, int nIndexMatch[]);
void addUniqueTranslation	(entry entries[], int nOpt);
void addEntry				(entry entries[], int *pEntriesCnt);
int  checkValidEntry		(int nIndexMatch[], int n);
void addTranslations 		(entry entries[], int n);
void displayEntry			(entry entries[], int n);
void displayAllEntries		(entry entries[], int n);
void searchWord				(entry entries[], int n);
void searchTranslation		(entry entries[], int n);
void modifyEntry            (entry entries[], int n);
void deleteEntry            (entry entries[], int *pEntriesCnt);
void deleteTranslation		(entry entries[], int *pCnt);
void import					(entry entries[], int *n);
void export					(entry entries[], int n);
void identifyMainLanguage	(entry entries2[], int n);
void simpleTranslation		(entry entries2[], int n);