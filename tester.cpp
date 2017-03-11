#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <map>
using namespace std;

class lwc
{
public:
lwc()
{
string flag = "";
string word = "";
string line = "";
char ch = (char) 0;
int words = 0;
int lines = 0;
int chars= 0;
int totwords = 0;
int totlines = 0;
int totchars = 0;
}
lwc(string word, string line, char ch, int words, int lines, int chars, string flag)
{
setLine(line);
setWord(word);
setChar(ch);
setWords(words);
setLines(lines);
setChars(chars);
setFlag(flag);
}

lwc(string flag)
{}
void setLine(string l)
{line = l;}
void setWord(string w)
{word = w;}
void setChar(char c)
{ch = c;}
void setLines(int l)
{lines = l;}
void setWords(int w)
{words=w;}
void setChars(int c)
{chars = c;}
void addLines( int Lines)
{totlines += Lines;}
void addWords (int Words)
{totwords += Words;}
void addChars(int Chars)
{totchars += Chars;}
void setFlag(string f)
{flag = f;}


string getLine()
{return line;}
string getWord()
{return word;}
char getChar()
{return ch;}
int getLines()
{return lines;}
int getWords()
{return words;}
int getChars()
{return chars;}
int getTotWords()
{return totwords;}
int getTotLines()
{return totlines;}
int getTotChars()
{return totchars;}
string getFlag()
{return flag;}


private:
string line= "";
string word = "";
string flag = "";
char ch = (char) 0;
int lines =0;
int words =0;
int chars =0;
int totlines = 0;
int totwords = 0;
int totchars = 0;
};

void findWord(lwc *word,string File)
{
ifstream file(File);
string pal = word->getWord();
string Word;
string line;
int a=0;
int b = 0;
bool i=false;


while (!file.eof())
	{
	
	getline(file, line);
	istringstream iss(line);
	while (iss >> Word)
	{
	if(ispunct(Word[Word.length() -1]))
		Word = Word.substr(0, Word.length()-1);
		if (!Word.compare(pal))
	 	{a++;i= true;}
		//cout << Word << "  " << pal << endl;		
	 } 
	 if (i)
		 {b++; i = false; 
		 // cout << b << " " << i << endl;
		 }
	 }
 word->addWords(a);
 word->addLines(b);
 word->setWords(a);
 word->setLines(b);
 
}

void checkErr(string ish)
{

//bool y=false;
if (ish[0] == '-')
	{
	string s = ish.substr(0,9);
	 string ss = s.substr(0,9);

	 if (ss.compare("-findword") && ss.compare("-findchar"))
	 	{cerr << "Argument " << ish << " is not recognized"<< endl; exit(1);}
	string sss = s.substr(9);
	if(ish[9] != '=')
	 { cerr << "Argument " << ish << " is poorly formed" << endl; exit(1);}
	 if (!ss.compare("-findchar") && ish.length() != 11)
	 { cerr << "Argument " << ish << " is poorly formed" << endl; exit(1);}
	 if (!ss.compare("-findword") && ish.length() < 11)
	 { cerr << "Argument " << ish << " is poorly formed" << endl; exit(1);}
	 }
else
{
ifstream File(ish);
 if (!File.is_open())
 {cout << "File "<< ish<< " is not found" << endl;
 exit(1);}
 if(File.fail()) {
 cerr << "Somethin' ain't right. SeeYa! (or try again if you want)" << endl;
 exit(1);}
//y = true; //it made it this far which means if there are files, they're good
}         //so, ideally, if i check to see if there are NO files, I can
//return y; //take from cin if indeed there are no files	                 
}         // checking this by I'm guessing a loop of somekind

void findChar(lwc *CH, string File)
{
ifstream file(File);
int a=0;
int b=0;
int c=0;
string line;
bool i = false;
bool j = false;
char ch;
//while (!file.eof())
while (getline(file,line))
{

	//getline(file, line);
	for (int g=0; g<line.length(); g++)
	{	ch = line[g];
		if (ch == CH->getChar())
		{a++; i= true; j = true;}
		
		if (isspace(ch) || g == line.length()-1)
		{
			if(j)
			{c++;j=false;}
		}
	}
	if (i)
	{b++; i = false;}
	
}

CH->setWords(c);
CH->setChars(a);
CH->setLines(b);
CH->addChars(a);
CH->addLines(b);
CH->addWords(c);
//cout << CH->getChar() << endl;

}



int main (int argc, char *argv[])
{

//for loop to find out how many classes i need in array
//and see if there are files
//use bool to decide whether or not to take from cin
int arraySize =0;
bool areThereFiles = false;
for(int i=1; i<argc; i++)
{
string s = argv[i];
checkErr(s);
if (s[0] == '-')
	arraySize++;
}
lwc lwcArray[arraySize];
//done figuring it out
if (arraySize !=0)
{
	 //a lineWordChar class for each flag (in theory)
	int c=0;
	for (int i =1; i<argc; i++)	
	{ string s =argv[i];
	  if (s[0] == '-')
		{lwcArray[c].setFlag(argv[i]); c++;}
	}		//set set flag names to array
}




//ok now to go through args again to total everything(file stuff) up!

int totfwords=0, totflines=0, totfchars=0, fcount=0;
for (int i=1; i<argc; i++)
{
 if (argv[i][0] == '-')
 	{continue;}
 string fword;

 char fch;
 int fwords =0, flines= 0, fchars=0;
 fcount++;
 ifstream fileA(argv[i]);
 while (fileA >> fword)
 {++fwords;}
 fileA.clear();
 fileA.seekg(0,fileA.beg);
 fch = fileA.get();
 while (fch != EOF)
 {
 	 if( fch == '\n')
	{ flines++;
	  fchars++;
	}
	 else if (isspace(fch))
	 {
	  fchars++;
	 }
	  else
	  fchars++;
	  fch= fileA.get();

} 
 totfwords += fwords;
 totflines += flines;
 totfchars += fchars;
 cout << setw(12) << flines << setw(12) << fwords << setw(12) << fchars << " " << argv[i] << endl;
	


}
if(fcount > 1)
{
cout << setw(12) << totflines << setw(12) << totfwords << setw(12) << totfchars << " totals" << endl;
}
/*
for (int i=1; i<argc; i++)
{ 
  string q = argv[i];
  if (q[0] == '-')
  	{continue;}
	for (int v=0;v<arraySize; v++)
		{
		 string d = lwcArray[v].getFlag();
		 lwcArray[v].setWord(d.substr(10));
		 lwcArray[v].setChar(d[11]);
		 if (!d.compare("word"))
			{
			findWord(lwcArray[v], q);

			}
		 	
		}
}
*/

for (int v=0;v<arraySize; v++)
{
 string d = lwcArray[v].getFlag();
 if (d.substr(0,9) == "-findword")
 {lwcArray[v].setWord(d.substr(10));}
 else
 {lwcArray[v].setChar(d[10]);}
bool u = false;
for (int m= 0; m < v; m++)
{ 
string k = lwcArray[v].getFlag();
	if (!k.compare(lwcArray[m].getFlag()))
		u = true;
if (u)
continue;

}
	if (u)
	continue;



	for (int e=1; e<argc; e++)
		{
		 if (argv[e][0] =='-')
		 	{continue;}
		 string b = argv[e];
		 if(d.substr(0,9) == "-findword")
		 	{
		 	 findWord(&lwcArray[v], b);
			cout << d.substr(10) << ':'<< setw(12) <<  lwcArray[v].getLines() << setw(12) << lwcArray[v].getWords() << " " << argv[e] << endl;

		 	}
		 else 
		 {
		  findChar(&lwcArray[v], b);
		  cout << d[10] << ':' << setw(12) << lwcArray[v].getLines()  << setw(12) << lwcArray[v].getWords() << setw(12) << lwcArray[v].getChars() << " " << argv[e] << endl;
		 }
		}	
		if (fcount > 1)
		{
			if(d.substr(0,9) == "-findword")
			{ cout << d.substr(10) << ':' << setw(12) << lwcArray[v].getTotLines() << setw(12) << lwcArray[v].getTotWords() <<  " totals" << endl;}
			else
			{ cout << d[10] << ':' << setw(12) << lwcArray[v].getTotLines() << setw(12) << lwcArray[v].getWords() << setw(12) << lwcArray[v].getTotChars() << " totals" << endl;}
		}

}
if (fcount == 0)
{
string omg;


while ( getline (cin, omg))
	{
	 totfchars += omg.length();
	 totflines ++;
	 totfchars ++;
	 istringstream iss (omg);
	 while (iss >> omg)
	 {totfwords++;}
	}
cout << setw(12) << totflines << setw(12) << totfwords << setw(12) << totfchars << endl;
 
}





return 0;
}
