#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

using namespace std;

bool isPunctuator(char ch)
{
    return ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
        ch == '&' || ch == '|';
}

bool isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '>' || ch == '<' ||
        ch == '=' || ch == '&' || ch == '|';
}

bool isKeyword(char* str)
{
    const char* keywords[] = {
        "if", "else", "while", "do", "break", "continue", "int", "double",
        "float", "return", "char", "case", "long", "short", "typedef",
        "switch", "unsigned", "void", "static", "struct", "sizeof",
        "volatile", "enum", "const", "union", "extern", "bool"
    };

    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < numKeywords; ++i)
    {
        if (!strcmp(str, keywords[i]))
            return true;
    }
    return false;
}

bool validIdentifier(char* str)
{
    if (!str || !str[0]) return false;

    if (isdigit(str[0]) || isPunctuator(str[0]))
        return false;

    for (int i = 1; str[i]; ++i)
    {
        if (isPunctuator(str[i]))
            return false;
    }
    return true;
}

bool isNumber(char* str)
{
    if (!str || !str[0]) return false;

    int numOfDecimal = 0;
    for (int i = 0; str[i]; ++i)
    {
        if (str[i] == '.')
        {
            numOfDecimal++;
            if (numOfDecimal > 1)
                return false;
        }
        else if (!isdigit(str[i]) && !(i == 0 && str[i] == '-'))
        {
            return false;
        }
    }
    return true;
}

char* subString(char* realStr, int l, int r)
{
    int len = r - l + 1;
    char* str = (char*)malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; ++i)
    {
        str[i] = realStr[l + i];
    }
    str[len] = '\0';
    return str;
}

void parse(char* str)
{
    int left = 0, right = 0;
    int len = strlen(str);

    while (right <= len && left <= right)
    {
        if (!isPunctuator(str[right]))
        {
            right++;
        }

        if ((isPunctuator(str[right]) && left == right))
        {
            char ch = str[right];

            if (isOperator(ch))
            {
                cout << ch << " IS AN OPERATOR\n";
                cout << "<op, " << ch << ">\n";
            }
            else if (ch == '(' || ch == '[')
            {
                cout << "<LPAREN, " << ch << ">\n";
            }
            else if (ch == ')' || ch == ']')
            {
                cout << "<RPAREN, " << ch << ">\n";
            }
            else if (ch == '{')
            {
                cout << "<LBRACE, " << ch << ">\n";
            }
            else if (ch == '}')
            {
                cout << "<RBRACE, " << ch << ">\n";
            }
            else if (ch == ';' || ch == ',')
            {
                cout << "<separator, " << ch << ">\n";
            }

            right++;
            left = right;
        }
        else if ((isPunctuator(str[right]) && left != right) || (right == len && left != right))
        {
            char* sub = subString(str, left, right - 1);

            if (isKeyword(sub))
            {
                cout << "<keyword, " << sub << ">\n";
            }
            else if (isNumber(sub))
            {
                cout << "<number, " << sub << ">\n";
            }
            else if (validIdentifier(sub))
            {
                cout << "<identifier, " << sub << ">\n";
            }
            else
            {
                cout << "<not an identifier, " << sub << ">\n";
            }

            free(sub);
            left = right;
        }
    }
}

int main()
{
    cout << "---- TOKENIZATION ----\n\n";
    char c[100] = "if(a=b*8+5)";
    parse(c);
    cout << endl;
}
