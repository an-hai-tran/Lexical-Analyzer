#include <iostream>
#include <map>
#include "lex.h"
#include <bits/stdc++.h>

using namespace std;

LexItem getNextToken (istream& in, int& linenumber)
{
    enum TokState {START, INID, INSTRING, ININT, INREAL,INCOMMENT} lexstate = START; // define possible states of token, set initial state to START
    string lexeme; char ch; // declare variables

    while (in.get(ch))
    {
        switch (lexstate)
        {
            case START:
                if (ch == '\n') // check for new line
                    linenumber++;
                if (isspace(ch))
                {
                    if (in.peek() == '_')
                    {
                        lexeme = "_";
                        return LexItem(ERR,lexeme,linenumber);
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
                if (ch == '#') // check for comment
                {
                    lexstate = INCOMMENT;
                    continue;
                }

                lexeme = ch;

                if (isalpha(ch) || ch == '_') // check for identifiers (IDENT)
                {
                    lexstate = INID;
                    continue;
                }

                if (ch == '"' || ch == '\'') // check for string literals (SCONST)
                {
                    lexstate = INSTRING;
                    continue;
                }

                if (isdigit(ch)) // check for integers (ICONST)
                {
                    lexstate = ININT;
                    continue;
                }

                if (ch == '.') // check for real constants (RCONST)
                {
                    lexstate = INREAL;
                    continue;
                }

                if (ch == '+')
                    return LexItem(PLUS, lexeme, linenumber);

                if (ch == '-')
                    return LexItem(MINUS, lexeme, linenumber);

                if (ch == '*')
                    return LexItem(MULT, lexeme, linenumber);

                if (ch == '/')
                    return LexItem(DIV, lexeme, linenumber);

                if (ch == '%')
                    return LexItem(REM, lexeme, linenumber);

                if (ch == '=')
                {
                    if (in.peek() == '=')
                    {
                        char c;
                        in.get(c);
                        return LexItem(EQUAL, lexeme + c, linenumber);
                    }
                    return LexItem(ASSOP, lexeme, linenumber);
                }

                if (ch == '(')
                    return LexItem(LPAREN, lexeme, linenumber);
                
                if (ch == ')')
                    return LexItem(RPAREN, lexeme, linenumber);

                if (ch == '>')
                    return LexItem(GTHAN, lexeme, linenumber);
                
                if (ch == ';')
                    return LexItem(SEMICOL, lexeme, linenumber);
                
                if (ch == ',')
                    return LexItem(COMMA, lexeme, linenumber);

                return LexItem(ERR, lexeme, linenumber);

        case INID:
            if (isalpha(ch) || isdigit(ch) || ch == '_')
            {
                lexeme += ch;
                continue;
            }
            else
            {
                lexstate = START;
                in.putback(ch);
                string upperLexeme = lexeme;
                transform(upperLexeme.begin(), upperLexeme.end(), upperLexeme.begin(), ::toupper);

                if (upperLexeme == "PROGRAM")
                    return LexItem(PROGRAM, lexeme, linenumber);
                if (upperLexeme == "END")
                    return LexItem(END, lexeme, linenumber);
                if (upperLexeme == "BEGIN")
                    return LexItem(BEGIN, lexeme, linenumber);
                if (upperLexeme == "WRITE")
                    return LexItem(WRITE, lexeme, linenumber);
                if (upperLexeme == "IF")
                    return LexItem(IF, lexeme, linenumber);
                if (upperLexeme == "INT")
                    return LexItem(INT, lexeme, linenumber);
                if (upperLexeme == "FLOAT")
                    return LexItem(FLOAT, lexeme, linenumber);
                if (upperLexeme == "STRING")
                    return LexItem(STRING, lexeme, linenumber);
                if (upperLexeme == "REPEAT")
                    return LexItem(REPEAT, lexeme, linenumber);

                return LexItem(IDENT, lexeme, linenumber);
            }
            break;
        case INSTRING:
            if (ch == '\n')
            {
                linenumber++;
                return LexItem(ERR, lexeme, linenumber-1);
            }
            else if ((ch == '"' && lexeme[0] == '"') || (ch == '\'' && lexeme[0] == '\''))
            {
                lexeme.erase(0,1);
                return LexItem(SCONST, lexeme, linenumber);
            }
            else
            {
                lexeme += ch;
            }
            break;

        case ININT:
            if (isdigit(ch))
                lexeme += ch;
            else if (ch == '.')
            {
                lexeme += ch;
                lexstate = INREAL;
            }
            else
            {
                lexstate = START;
                in.putback(ch);
                return LexItem(ICONST, lexeme, linenumber);
            }
            break;

        case INREAL:
            if (isdigit(ch))
            {
                lexeme += ch;
                if (in.peek() == '+' || in.peek() == '-' || in.peek() == '*' || in.peek() == '/' || in.peek() == ' ' || in.peek() == '\n' || in.peek() == ')')
                    return LexItem(RCONST, lexeme, linenumber);
            }
            else
            {
                if(ch == ' ')
                {
                    return LexItem(ERR, lexeme, linenumber);
                }
                else
                {
                    lexeme += ch;
                    return LexItem(ERR, lexeme, linenumber);
                }
            }
            break;

        case INCOMMENT:
            if (ch == '\n')
            {
                linenumber++;
                lexstate = START;
            }
            break;
        }
    }
    return LexItem(DONE, "", linenumber);
}