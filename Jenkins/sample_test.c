#include <stdio.h>
#include <string.h>

# define NDEBUG // The program runs fine if NDEBUG is defined even if assert fails
# include <assert.h>

# include "sample.c"
// char* sayHello() {
//    // Sample program to try out Jenkins
//    return "hello";
// }
  
void sayHelloTest() 
{ 
    char str[50] = "";
    strcpy(str, sayHello());
    assert(strcmp(str, "hello") == 0);
    
    int x = 7;
    //assert (x==5); // basic
    //assert(("message", x==5)); // message method 1
    //assert(x==5 /* message */); // message method 2
    assert(x==5 && "Variable 'x' should be 5"); // message method 3
}

int main() {
    sayHelloTest();
    printf("Test Done!");
}