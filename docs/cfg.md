# CFG for Pascal Interpreter

Terminals:
* NULL
* EOF
* INTEGER
* PLUS
* MINUS
* MUL
* DIV

expr   : term ((PLUS|MINUS) term)*
term   : factor ((MUL|DIV) factor)*
factor : INTEGER