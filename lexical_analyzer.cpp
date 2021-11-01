#include <iostream>
#include <fstream>
#include <string>
#include "lex.h"
#include "lex.cpp"
#include <map>
#include <list>
#include <bits/stdc++.h>
using namespace std;

map<string, Token> tokenDir =
{{"PROGRAM",PROGRAM},{"END",END},{"BEGIN",BEGIN},{"WRITE",WRITE},
{"IF",IF},{"INT",INT},{"FLOAT",FLOAT},{"STRING",STRING},{"REPEAT",REPEAT}};

map<Token, string> tokenPrint = // map to print out string value of enumerated token
{{IDENT,"IDENT"},{PLUS,"PLUS"},{MINUS,"MINUS"},{MULT,"MULT"},{DIV,"DIV"},{REM,"REM"},{ASSOP,"ASSOP"},{LPAREN,"LPAREN"},
{RPAREN,"RPAREN"},{EQUAL,"EQUAL"},{GTHAN,"GTHAN"},{PROGRAM,"PROGRAM"},{END,"END"},{BEGIN,"BEGIN"},
{WRITE,"WRITE"},{IF,"IF"},{INT,"INT"},{FLOAT,"FLOAT"},{STRING,"STRING"},{REPEAT,"REPEAT"},{SEMICOL,"SEMICOL"},
{COMMA,"COMMA"},{ICONST,"ICONST"},{RCONST,"RCONST"},{SCONST,"SCONST"},{ERR,"ERR"},{DONE,"DONE"}};


int main(int argc, char *argv[])
{
    int lineNumber = 1;
    LexItem tok;

    bool v = false;
    bool iconst = false;
    bool fconst = false;
    bool strconst = false;
    bool ident = false;

    ifstream file;

    bool hasFile = false;

    for (int i = 1; i < argc; i++)
    {
        string var = argv[i];
        if (var == "-v")
        {
            v = !v;
        }
        else if (var == "-iconst")
        {
            iconst = !iconst;
        }
        else if (var == "-fconst")
        {
            fconst = !fconst;
        }
        else if (var == "-strconst")
        {
            strconst = !strconst;
        }
        else if (var == "-ident")
        {
            ident = !ident;
        }
        else if (var[0] == '-')
        {
            cerr << "UNRECOGNIZED FLAG " << argv[i] << endl;
            return -1;
        }
        else
        {
            if (hasFile) 
            {
                cerr << "ONLY ONE FILE NAME ALLOWED" << endl;
                return -1;
            }
            else
            {
                hasFile = true;
                file.open(argv[i]);
                if (!file)
                {
                    cerr << "CANNOT OPEN the File " << argv[i] << endl;
                    return -1;
                }
            }
        }
    }

    if (!hasFile)
    {
        cerr << "NO SPECIFIED INPUT FILE NAME." << endl;
        return -1;
    }
    
    list<string> idents;
    list<string> strconsts;
    list<double> fconsts;
    list<int> intconsts;
    int countToken = 0;

    while ((tok = getNextToken(file, lineNumber)) != DONE && tok != ERR)
    {
        countToken++;
        if (v)
        {
            Token t = tok.GetToken();
            string upperLexeme = tok.GetLexeme();
            transform(upperLexeme.begin(), upperLexeme.end(), upperLexeme.begin(), ::toupper);
            if(t==IDENT||t==ICONST||t==RCONST||t==SCONST) 
            {
                cout <<tokenPrint[t]<<"("<<upperLexeme<<")" << endl; 
            }
            else
            {
                cout << tokenPrint[t] << endl;
            }
        }
        if (tok.GetToken() == IDENT)
        {
            string upperLexeme = tok.GetLexeme();
            transform(upperLexeme.begin(), upperLexeme.end(), upperLexeme.begin(), ::toupper);
            idents.push_back(upperLexeme);
        }
        if (tok.GetToken() == SCONST) {
            strconsts.push_back(tok.GetLexeme());
        }
        if (tok.GetToken() == ICONST) {
            intconsts.push_back(stoi(tok.GetLexeme()));
        }
        if (tok.GetToken() == RCONST) {
            fconsts.push_back(stod(tok.GetLexeme()));
        }
    }

    if (tok.GetToken() == Token::ERR)
        {
            cout << "Error in line " << tok.GetLinenum() << " (" << tok.GetLexeme() << ")" << endl;
            return -1;
        }
        else
        {
            cout << "Lines: " << lineNumber-1 << endl;
            if (countToken >= 1)
            {
                cout << "Tokens: " << countToken << endl;
            }
        }

    if (strconst)
    {
        if (strconsts.size()>0)
        {
            strconsts.unique();
            strconsts.sort();

            cout << "STRINGS:" << endl;
            for (string n : strconsts)
            {
                cout << "\""<< n << "\"" << endl;
            }
        }
    }

    if (iconst) 
    {
        if (intconsts.size() > 0) 
        {
            intconsts.sort();
            intconsts.unique();

            cout << "INTEGERS:" << endl;
            for (int n : intconsts) {
                cout << n << endl;
            }
        }
    }
    
    if (fconst) 
    {
        if (fconsts.size() > 0) 
        {
            fconsts.sort();
            fconsts.unique();

            cout << "REALS:" << endl;
            for (double n : fconsts) 
            {
                cout << n << endl;
            }
        }
    }

    if (ident) 
    {
        if (idents.size() > 0) 
        {
            idents.sort();
            idents.unique();

            cout << "IDENTIFIERS:" << endl;
            for (string n : idents) 
            {
                cout << n;
                if (n.compare(idents.back())) 
                {
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }
    return 0;
}

LexItem id_or_kw(const string& lexeme, int linenum)
{
    map<string, Token>::iterator it; // creating iterator for the map
    it = tokenDir.find(lexeme); // search the map for the string of lexeme
    if (it != tokenDir.end()) // if it is in the map
    {
        return LexItem(it->second, lexeme, linenum); // lexeme found, return the Lex item containing the keyword token
    }
    return LexItem(IDENT, lexeme, linenum); // lexeme not found, return Lex item with identifier token IDENT
}


ostream& operator<<(ostream& out, const LexItem& tok)
{
    Token t = tok.GetToken(); // get the token from the LexItem object 
    out<<tokenPrint[t]; // print out the string value of the enumerated token
    if(t==IDENT||t==ICONST||t==RCONST||t==SCONST||t==ERR) // if the token is one of these token
    {
        out<<" ("<<tok.GetLexeme()<<")"; // print the token followed by its lexeme between parentheses
    }
    return out; // return out object
}