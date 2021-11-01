# Lexical-Analyzer
A lexical analyzer for small programming language and a program to test it.

A parser and an interpreter to the same language will be built later on. 

The syntax definitions of a small programming language are given below using EBNF notations: 

Prog ::= PROGRAM IDENT StmtList END PROGRAM  
StmtList ::= Stmt; {Stmt;} 
Stmt ::= DeclStmt | ControlStmt  
DeclStmt ::= (INT | FLOAT | STRING) VarList  
ControlStmt ::= AssigStmt | IfStmt | WriteStmt | RepeatStmt | CompStmt 
WriteStmt ::= WRITE ExprList 
IfStmt ::= IF (LogicExpr) ControlStmt 
RepeatStmt ::= REPEAT (Var = Expr, Expr [,ICONST]) ControlStmt 
AssignStmt ::= Var = Expr 
CompStmt ::= BEGIN StmtList END 
VarList ::= Var {,Var} 
ExprList ::= Expr {, Expr} 
Expr ::= Term {(+|-) Term} 
Term ::= SFactor {( *| / | % ) SFactor}  
SFactor ::= (+ | -) Factor | Factor 
LogicExpr ::= Expr (== | >) Expr 
Var ::= IDENT 
Factor = IDENT | ICONST | RCONST | SCONST | (Expr) 

Based on the language definitions, the lexical rules of the language and the assigned tokens to 
terminals are as follows: 
 
1. The  language  has  identifiers,  referred  to  by  ident  terminal,  which  are  defined  to  be  a  letter 
followed by zero or more letters or digit.  It is defined as: 
ident := Letter {(Letter|Digit|_)} 
Letter := [a-z A-Z] 
Digit := [0-9] 
 
 The token for an identifier is IDENT. 
 
2. Integer constants, referred to by iconst terminal, are defined as one or more digits. It is defined 
as: 
iconst := [0-9]+ 
The token for an integer constant is ICONST. 
 
3. Real constants, referred to by rconst terminal, are defined as zero or more digits followed by a 
decimal point (dot) and one or more digits. It is defined as: 
Rconst := ([0-9]*)\.([0-9]+) 
The token for a real constant is RCONST. For example, real number constants such as 12.0 
and .2 are accepted, but 2. is not. 
 
4. String literals, referred to by sconst terminal, are defined as a sequence of characters delimited 
by  double  quotes,  that  should  all  appear  on  the  same  line.  The  assigned  token  for  a  string 
constant is SCONST. For example, “Hello.” is a string literal.  
 
5. The reserved words of the language are: program, end, begin, write, if, int, float, string, repeat. 
These  reserved  words  have  the  following  tokens,  respectively:  PROGRAM,  END,  BEGIN, 
WRITE, IF, INT, FLOAT, STRING and REPEAT. 
 
6. The  operators  of  the  language  are:  +,  -,  *,  /,  %,  =,  (,  ),  ==,  >.  These  operators  are  for  plus, 
subtract, multiply, divide, remainder, assignment, left parenthesis, right parenthesis, equality, 
and  greater  than  operations.  They  have  the  following  tokens,  respectively:  PLUS,  MINUS, 
MULT, DIV, REM, ASSOP, LPAREN, RPAREN, EQUAL, GTHAN. 
 
7. The  semicolon  and  comma  characters  are  terminals  with  the  following  tokens:  SEMICOL, 
COMMA. 
 
8. A comment is defined by all the characters following the pound sign “#” to the end of the line. 
A comment does not overlap one line. A recognized comment is ignored and does not have a 
token. 
 
9. White  spaces  are  skipped.  However,  white  spaces  between  tokens  are  used  to  improve 
readability and can be used as a one way to delimit tokens. 
 
10. An error will be denoted by the ERR token. 
 
11. End of file will be denoted by the DONE token.

The notations for each input flag are as follows:  
● -v  (optional):    if  present,  every  token  is  printed  when  it  is  seen  followed  by  its 
lexeme between parentheses.  
● -intconst (optional): if present, prints out all the unique integer constants in numeric 
order. 
● -fconst  (optional):  if  present,  prints  out  all  the  unique  real  constants  in  numeric 
order. 
● -strconst  (optional):  if present,  prints  out  all the  unique string constants  in 
alphabetical order  
● -ident (optional): if present, prints out all of the unique identifiers in alphabetical 
order.  
● filename argument must be passed to main function. The program will open the 
file and read from that filename. 
