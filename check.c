#include<stdio.h>
#include<stdlib.h>

int parseNot (char* token, int index) {

  if (token[index] == 'N') {

    if (token[index=index+1]=='O' && token[index=index+1]=='T' && token[index=index+1]=='\0') {
      return index;
    }
    else {
      return -1;
    }
  }
  return -1;
}

int parseAnd (char* token, int index) {
  if (token[index]=='A' && token[index=index+1]=='N' && token[index=index+1]=='D' && token[index=index+1]=='\0') {
    return index;
  }
    return -1;
}

int parseOr (char* token,  int index) {
  if (token[index]=='O' && token[index=index+1]=='R' && token[index=index+1]=='\0') {
    return index;
  }
    return -1;
}

int parseTrue (char* token, int index) {
  if (token[index]=='t' && token[index=index+1]=='r' && token[index=index+1]=='u' && token[index=index+1]=='e' && token[index=index+1]=='\0') {
    return index;
  }
    return -1;

}

int parseFalse (char* token, int index) {
  if (token[index]=='f' && token[index=index+1]=='a' && token[index=index+1]=='l' && token[index=index+1]=='s'
   && token[index=index+1]=='e' && token[index=index+1]=='\0') {
     return index;
   }
     return -1;

}
int parseArithOp (char* token, int index) {
 if ((token[index]== '+' || token[index]== '-' || token[index]== '/' || token[index]== '*') && token[index=index+1]=='\0') {
   return index;
 }
 else {
   return -1;
 }
}

int parseNum (char* token, int index) {
  if (token[index] >= '0' && token[index] <= '9' && token[index=index+1]=='\0') {
    return index;
  }
  else {
    return -1;
  }
}

//figure out if not is in the right place. boolean function.
int scanNot (char* token, int* codeArray, int index, int expressionCounter) {
  if (index==0 || codeArray[index-1]==7) {
    return 1;
  }
  else {
    printf("Error: parse error in expression ");
    printf("%d", expressionCounter);
    printf(": unexpected operator  \n\"");
    printf("%s", token);
    printf("\" \n");
    return -1;
  }
}
//figure out if and is in the right place. boolean function.
int scanAndOr (char* token, char* prevToken, int* codeArray, int index, int expressionCounter) {
  if (index==0) {
    printf("Error: parse error in expression ");
    printf("%d", expressionCounter);
    printf(": unexpected operator  \n\"");
    printf("%s", token);
    printf("\" \n");
    return -1;
  }
  else if (codeArray[index-1] ==5 || codeArray[index-1] ==7) {
    return 1;
  }
  else {
    int numChecker = parseNum(prevToken, 0);
    if (numChecker!= -1 && codeArray[index-1] != 3) {
      printf("Error: parse error in expression ");
      printf("%d", expressionCounter);
      printf(": type mismatch  \n\"");
      printf("%s ", prevToken);
      printf("%s", token);
      printf("\" \n");
    }
    else {
      printf("Error: parse error in expression ");
      printf("%d", expressionCounter);
      printf(": unexpected operator  \n\"");
      printf("%s", token);
      printf("\" \n");
    }
    return -1;
  }
}
//figure out if true/false is in the right place, and if it's a leading or ending log operand
int scanTrueFalse (char* token, char* prevToken, int* codeArray, int index, int expressionCounter) {
  if (index==0 || codeArray[index-1] ==7) {
    return 5;
  }
  else if (codeArray[index-1]==4 || codeArray[index-1]==8) {
    return 6;
  }
  else {
    int arithOpChecker = parseArithOp(prevToken, 0);
    if (arithOpChecker!= -1) {
      printf("Error: parse error in expression ");
      printf("%d", expressionCounter);
      printf(": type mismatch  \n\"");
      printf("%s ", prevToken);
      printf("%s", token);
      printf("\" \n");
      return 6;
    }
    else {
    printf("Error: parse error in expression ");
    printf("%d", expressionCounter);
    printf(": unexpected operand  \n\"");
    printf("%s", token);
    printf("\" \n");
    return 5;
   }
  }
}

//figure out if arith op is in the right place. boolean function
int scanArithOp (char* token, char* prevToken, int* codeArray, int index, int expressionCounter) {
  if (index==0) {
    printf("Error: parse error in expression ");
    printf("%d", expressionCounter);
    printf(": unexpected operator  \n\"");
    printf("%s", token);
    printf("\" \n");
    return -1;
  }
  else if (codeArray[index-1]==2) {
    return 1;
  }
  else {
    int trueChecker = parseTrue(prevToken, 0);
    int falseChecker = parseFalse(prevToken, 0);
    if ((trueChecker!= -1 || falseChecker != -1) && codeArray[index-1]!=6) {
      printf("Error: parse error in expression ");
      printf("%d", expressionCounter);
      printf(": type mismatch  \n\"");
      printf("%s ", prevToken);
      printf("%s", token);
      printf("\" \n");
    }
    else {
      printf("Error: parse error in expression ");
      printf("%d", expressionCounter);
      printf(": unexpected operator  \n\"");
      printf("%s", token);
      printf("\" \n");
    }
    return -1;
  }
}
//figure out if numbers are in the right place and if they're leading or ending numbers
int scanNumbers (char* token, char* prevToken, int* codeArray, int index, int expressionCounter) {
  if (index==0 || codeArray[index-1] ==7) {
    return 2;
  }
  else if (codeArray[index-1]==1) {
    return 3;
  }
  else {
    int andChecker = parseAnd(prevToken, 0);
    int orChecker = parseOr(prevToken, 0);
    int notChecker = parseNot(prevToken, 0);
    if (andChecker!= -1 || orChecker != -1 || notChecker != -1) {
      printf("Error: parse error in expression ");
      printf("%d", expressionCounter);
      printf(": type mismatch  \n\"");
      printf("%s ", prevToken);
      printf("%s", token);
      printf("\" \n");
      return 3;
    }
    else {
      printf("Error: parse error in expression ");
      printf("%d", expressionCounter);
      printf(": unexpected operand  \n\"");
      printf("%s", token);
      printf("\" \n");
      return 2;
    }
  }
}
//figure out what something unknown is supposed to be
int scanUnknown (char* token, int* codeArray, int index, int expressionCounter) {
  if (index==0) {
    printf("Error: parse error in expression ");
    printf("%d", expressionCounter);
    printf(": unknown identifier  \n\"");
    printf("%s", token);
    printf("\" \n");
    return 7;
  }
  if (codeArray[index-1]==1) {
    printf("Error: parse error in expression ");
    printf("%d", expressionCounter);
    printf(": unknown operand  \n\"");
    printf("%s", token);
    printf("\" \n");
    return 3;
  }
  else if (codeArray[index-1]==2) {
    printf("Error: parse error in expression ");
    printf("%d", expressionCounter);
    printf(": unknown operator  \n\"");
    printf("%s", token);
    printf("\" \n");
    return 1;

  }
  else if (codeArray[index-1]==4 || codeArray[index-1]==8) {
    printf("Error: parse error in expression ");
    printf("%d", expressionCounter);
    printf(": unknown operand  \n\"");
    printf("%s", token);
    printf("\" \n");
    return 6;

  }
  else if (codeArray[index-1]==5) {
    printf("Error: parse error in expression ");
    printf("%d", expressionCounter);
    printf(": unknown operator  \n\"");
    printf("%s", token);
    printf("\" \n");
    return 4;
  }
  else {
    printf("Error: parse error in expression ");
    printf("%d", expressionCounter);
    printf(": unknown identifier  \n\"");
    printf("%s", token);
    printf("\" \n");
    return 7;
  }
}


int main(int argc, char** argv){

//make sure number of arguments is correct
 if (argc != 2) {
  printf("Error: wrong amount of inputs \n");
  return 0;
 }

//copy command line argument into an array
char expressions[100000];
int x;
int y=0;
 for (x=1; x<argc; x++) {
   char* input_str = argv[x];
   char * t;
   for (t = input_str; *t != 0; t++) {
   expressions[y] = *t;
   y++;
   }
 }
expressions[y] = '\0';

//keeps track of where you are in the line
int start_idx=0;

int expressionCounter= 0;

int logicalCounter=0;
int arithmeticCounter=0;

//terminate once you reach the null character
//every time this loop runs, the current expression is loaded into a string array
//then another, inner loop is run on every token in that array
while (expressions[start_idx] != '\0') {
//  ++expressionCounter;
  int expressionFound=-1;
  int missingExpression = -1;

  if (expressionCounter!=0 && expressions[start_idx] != ' ') {
    printf("Error: parse error in expression ");
    printf("%d", expressionCounter);
    printf(": incomplete expression \n");
    missingExpression=1;
  }
  else if (expressionCounter != 0) {
    ++start_idx;
  }

//2D array that changes every iteration of code: always holds the tokens in the current expression
  char words[200][1000];

//load all the tokens from the current expression into an array
int num_words = 0;
int char_ctr = 0;
int i;
for (i = start_idx; expressions[i] != ';' && expressions[i] != '\0'; ++i) {
  if (expressions[i] == ' ') {
    words[num_words][char_ctr] = '\0';
    ++num_words;
    char_ctr = 0;
  } else {
    words[num_words][char_ctr] = expressions[i];
    ++char_ctr;
  }
}
words[num_words][char_ctr] = '\0';
++num_words;
//DON'T TOUCH THIS VARIABLE FOR THE REST OF THE LOOP. Holds the position of the start of the next expression
start_idx=i+1;

//int array to hold what kind of expression each token is
int codeArray[num_words];

//THIS IS THE MAIN LOOP WHERE EVERYTHING HAPPENS
int curr_word;
for (curr_word=0; curr_word< num_words; curr_word++) {

    if (curr_word==0 && num_words==1 && words[curr_word][0]=='\0') {
      printf("Error: parse error in expression ");
      printf("%d", expressionCounter);
      printf(": missing expression \n");
      missingExpression=1;
      continue;
    }

    int notChecker = parseNot(words[curr_word], 0);
    int andChecker = parseAnd (words[curr_word], 0);
    int orChecker = parseOr (words[curr_word], 0);
    int falseChecker = parseFalse (words[curr_word], 0);
    int trueChecker = parseTrue (words[curr_word], 0);
    int arithOpChecker = parseArithOp (words[curr_word], 0);
    int numChecker = parseNum (words[curr_word], 0);


    if (notChecker != -1) {
      scanNot(words[curr_word], codeArray, curr_word, expressionCounter);
      codeArray[curr_word] = 8;
      if (expressionFound == -1) {
        expressionFound=1;
        ++logicalCounter;
      }
    }
    else if (andChecker != -1) {
      scanAndOr(words[curr_word], words[curr_word-1], codeArray, curr_word, expressionCounter);
      codeArray[curr_word] = 4;
      if (expressionFound == -1) {
        expressionFound=1;
        ++logicalCounter;
      }
    }
    else if (orChecker != -1) {
      scanAndOr(words[curr_word], words[curr_word-1], codeArray, curr_word, expressionCounter);
      codeArray[curr_word] = 4;
      if (expressionFound == -1) {
        expressionFound=1;
        ++logicalCounter;
      }
    }
    else if (falseChecker != -1) {
      int firstSecond = scanTrueFalse(words[curr_word], words[curr_word-1], codeArray, curr_word, expressionCounter);
      codeArray[curr_word] = firstSecond;
    }
    else if (trueChecker != -1) {
      int firstSecond = scanTrueFalse(words[curr_word], words[curr_word-1], codeArray, curr_word, expressionCounter);
      codeArray[curr_word] = firstSecond;
    }
    else if (arithOpChecker != -1) {
      scanArithOp(words[curr_word], words[curr_word-1], codeArray, curr_word, expressionCounter);
      codeArray[curr_word] = 1;
      if (expressionFound == -1) {
        expressionFound=1;
        ++arithmeticCounter;
      }
    }
    else if (numChecker != -1) {
      int firstSecond = scanNumbers(words[curr_word], words[curr_word-1], codeArray, curr_word, expressionCounter);
      codeArray[curr_word] = firstSecond;
    }
    else {
      int unknown = scanUnknown(words[curr_word], codeArray, curr_word, expressionCounter);
      codeArray[curr_word] = unknown;
    }
  }

  int operatorFinder=-1;
  int operandFinder=0;
  int valid=0;
  int foundEnd=-1;
  int unaryExpression=-1;

  int f;
  for (f=0; f<num_words; f++) {

    if ((codeArray[f]==3 || codeArray[f]==6) && foundEnd == -1) {
      foundEnd = f;
    }
    if (codeArray[f]==2 || codeArray[f]==3 || codeArray[f]==5 || codeArray[f]==6) {
      operandFinder++;
    }
    if ((codeArray[f]==1 || codeArray[f]==4 || codeArray[f]==8) && operatorFinder==-1) {
      operatorFinder=codeArray[f];
    }
    if (!(codeArray[f]==7)) {
      valid++;
    }
    if (f < num_words-1 && codeArray[f]==8 && codeArray[f+1]==6) {
      unaryExpression=1;
    }
  }


  if (num_words < 3) {
      if ((codeArray[0]==2 || codeArray[0]==5)) {
        if (num_words==1) {
        printf("Error: scan error in expression ");
        printf("%d", expressionCounter);
        printf(": missing operator \n");
      }
       else if (((codeArray[1]==4 || codeArray[1]==8) && codeArray[0]==5) || (codeArray[1]==1 && codeArray[0]==2)) {
        printf("Error: scan error in expression ");
        printf("%d", expressionCounter);
        printf(": missing operand \n");
      }
    }
    else if (num_words==1 && codeArray[0]==8) {
      printf("Error: scan error in expression ");
      printf("%d", expressionCounter);
      printf(": missing operand \n");
    }
  }
  //if there are no valid tokens, it's an incomplete expressions

  if (valid == 0) {
    printf("Error: scan error in expression ");
    printf("%d", expressionCounter);
    printf(": incomplete expression \n");
  }
  //if the end of the expression isn't the last thing in the array, it went on too long
  else if (words[0][0] != '\0' && foundEnd != -1 && foundEnd != num_words-1) {
     printf("Error: parse error in expression ");
     printf("%d", expressionCounter);
     printf(": expression not ended \n\"");
     printf("%s", words[foundEnd]);
     printf(" %s\"\n", words[foundEnd+1]);
   }
  ++expressionCounter;

}

//if the expression ends with a semicolon, that means the last expression is an empty one
 if (expressions[start_idx -1]==';') {
   printf("Error: parse error in expression ");
   printf("%d", expressionCounter++);
   printf(": missing expression \n");

 }
 printf("Found %d expressions: %d logical and %d arithmetic \n", expressionCounter, logicalCounter, arithmeticCounter);

}
