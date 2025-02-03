#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100

// List of C keywords
char *keywords[] = {"int", "float", "char", "return", "if", "else", "while"};
int num_keywords = 7;

// Function to check if a word is a keyword
int is_keyword(char *word) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1; // It's a keyword
        }
    }
    return 0; // Not a keyword
}

// Function to check if a character is an operator
int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>' ||
            c == '!' || c == '&' || c == '|' || c == '%');
}

// Function to check if a word is a valid identifier
int is_identifier(char *word) {
    if (!isalpha(word[0]) && word[0] != '_') return 0; // First character must be a letter or underscore
    for (int i = 1; i < strlen(word); i++) {
        if (!isalnum(word[i]) && word[i] != '_') return 0; // Remaining characters must be alphanumeric or underscore
    }
    return 1; // Valid identifier
}

// Function to tokenize the input text and identify keywords, operators, and identifiers
void lexical_analyzer(const char *code) {
    char ch;
    char token[MAX_TOKEN_LENGTH];
    int token_length = 0;
    int i = 0;

    while ((ch = code[i]) != '\0') {
        if (isspace(ch)) {
            i++;
            continue;
        }

        if (isalpha(ch) || ch == '_') { // Start of an identifier or keyword
            token[token_length++] = ch;
            i++;
            while (isalnum(code[i]) || code[i] == '_') {
                token[token_length++] = code[i++];
            }
            token[token_length] = '\0'; // Null-terminate the token

            if (is_keyword(token)) {
                printf("Keyword: %s\n", token);
            } else if (is_identifier(token)) {
                printf("Identifier: %s\n", token);
            }
            token_length = 0; // Reset token length for next token
        }
        else if (is_operator(ch)) { // Operator
            printf("Operator: %c\n", ch);
            i++;
        }
        else if (ch == ';' || ch == ',' || ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']') {
            // Delimiters (not required but added for completeness)
            printf("Delimiter: %c\n", ch);
            i++;
        }
        else {
            i++; // Skip unknown characters (for simplicity)
        }
    }
}

int main() {
    const char *code = "int main() { int x = 5; if (x > 0) return x; }";

    printf("Lexical analysis of code:\n");
    lexical_analyzer(code);
    
    return 0;
}
