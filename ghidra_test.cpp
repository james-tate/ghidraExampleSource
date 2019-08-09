#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <iostream>


void init (void) __attribute__ ((constructor));

class Nest{
public:
    uint32_t nestVar;
    const char* flagPtr;
    char* s1;
    char* s2;
    char* flag;

    Nest(){
      s1 = (char*)malloc(32*sizeof(char));
      s2 = (char*)malloc(32*sizeof(char));
      printf("Creating Nest Object\n");
      nestVar = 0x1337;
      flagPtr = "8689d701c21f91c4085f08d9a411c029";
      char* s1_cp = s1;
      char* s2_cp = s2;
      int i = 0;
      while(*flagPtr){
        *s1_cp++ = *flagPtr++;
        if(i++%2)
          *s2_cp++ = *flagPtr;
      }
    }
    virtual void Test(){
      printf("This is only a test\n");
    }

    ~Nest(){
      free(s1);
      free(s2);
    }

    virtual void hello(void){
      printf("Hello from Nest\n");
    }
};

class Base{
public:
    virtual void count(int16_t incNumber) = 0;
    virtual uint16_t getu16() = 0;
    virtual uint32_t getu32() = 0;
    virtual void testCase(uint16_t c) = 0;
};

class Derived_Example1:Base{
public:
    const char *s_charPointer;
    uint16_t u16_counter; 
    uint32_t u32_counter;  
    Nest *nest;

    Derived_Example1(){
      s_charPointer = "Hello from Derived\n";
      u16_counter = 0;
      u32_counter = 0;
      nest = new Nest();
    }

    virtual ~Derived_Example1(){
      delete(nest);
      return;
    }
    
    virtual void count(int16_t incNumber){
      printf("counting\n");
      int16_t i = 0;
      do{
        this->u16_counter++;
        this->u32_counter = u16_counter * i;
        i++;
      }while(i < incNumber);
    }

    virtual uint16_t getu16(){
      return this->u16_counter;
    }

    virtual uint32_t getu32(){
      return this->u32_counter;
    }

    virtual void testCase(uint16_t c){
      uint8_t caseChoose = c % 3;
      switch (caseChoose){
        case 0:
          printf("Case 0\n");
          return;
        case 1:
          printf("Case 1\n");
          return;
        case 2:
          printf("Case 2\n");
          return;
        case 3:
          printf("Case3\n");
          return;
      }
      return;
    }
};

class Derived_Example2:Base{
public:
    const char *s_charPointer;
    uint16_t u16_counter; 
    uint32_t u32_counter;  
    Nest *nest;

    Derived_Example2(){
      s_charPointer = "Hello from Derived\n";
      u16_counter = 0x42;
      u32_counter = 0xDEADBEEF;
      nest = new Nest();
    }

    virtual ~Derived_Example2(){
      delete(nest);
      return;
    }
    
    virtual void count(int16_t incNumber){
      this->u16_counter++;
    }

    virtual uint16_t getu16(){
      return this->u16_counter;
    }

    virtual uint32_t getu32(){
      return this->u32_counter;
    }

    virtual void testCase(uint16_t c){
      uint8_t caseChoose = c % 3;
      switch (caseChoose){
        case 0:
          printf("Case 0\n");
          return;
        case 1:
          printf("Case 1\n");
          return;
        case 2:
          printf("Case 2\n");
          return;
        case 3:
          printf("Case3\n");
          return;
      }
      return;
    }
};

typedef struct{
    const char* c_str;
    int8_t i_8;
    int16_t i_16;
    int32_t i_32;
    long long l_long;
} myStruct;

myStruct s_myStruct;
Derived_Example1 global_d;
int32_t myArray[3] = {0x1111, 0x2222, 0x3333};

void init (void){    
  printf ("Init call before main()\n");   
  global_d = Derived_Example1();
};

void setupStruct(void){
    s_myStruct.c_str = "Hello from a struct";
    s_myStruct.i_8 = 0x7F;
    s_myStruct.i_16 = 0x6789;
    s_myStruct.i_32 = 0xDEADBEEF;
}

void printStruct(myStruct& s_strCpy){
    while(*s_strCpy.c_str){
      printf("%c", *s_strCpy.c_str);
      s_strCpy.c_str++;
    }
    printf("\nstruct i_8, 0X%2X\n", s_strCpy.i_8);
    printf("struct i_16, 0X%4X\n", s_strCpy.i_16);
    printf("struct i_32, 0X%8X\n", s_strCpy.i_32);
}

void printArray(int32_t array[], uint8_t size){
    for(int i=0; i < size; i++){
      printf("Array index Value %4X\n", array[i]);
    }
}

void pointer_class(int ran){
    // pointer object
    std::cout << "========Pointer==============\n";

    Derived_Example1 *Derived1;
    Derived1 = new Derived_Example1();
    Derived1->count(ran);
    Derived1->testCase(ran);
    printf("U16 = %d\n", Derived1->getu16());
    printf("U32 = %d\n", Derived1->getu32());
    printf("Nest32 = 0x%4X\n", Derived1->nest->nestVar);
    Derived1->nest->hello();
    Derived1->nest->Test();

    const char* cp = Derived1->s_charPointer;

    while (*cp){
      printf("%c", *cp);
      *cp++;
    }
    std::cout << std::endl;

    char* s1 = Derived1->nest->s1;

    printf("{%s}\n", s1);

    Derived_Example2 *Derived2;
    Derived2 = new Derived_Example2();
    Derived2->count(ran);
    Derived2->testCase(ran);
    printf("U16 = %d\n", Derived2->getu16());
    printf("U32 = %d\n", Derived2->getu32());
    printf("Nest32 = 0x%4X\n", Derived2->nest->nestVar);
    Derived2->nest->hello();
    Derived2->nest->Test();

    const char* cp1 = Derived2->s_charPointer;

    while (*cp1){
      printf("%c", *cp1);
      *cp1++;
    }
    std::cout << std::endl;

    char* s2 = Derived2->nest->s1;

    printf("{%s}\n", s2);

    delete Derived1;
    delete Derived2;
}

void stack_class(int ran){
    // stack object
    std::cout << "========Stack==============\n";

    Derived_Example1 stack_d;
    stack_d.count(ran);
    stack_d.testCase(ran);
    printf("U16 = %d\n", stack_d.getu16());
    printf("U32 = %d\n", stack_d.getu32());
    printf("Nest32 = 0x%4X\n", stack_d.nest->nestVar);
    stack_d.nest->hello();
    stack_d.nest->Test();

    const char* p = stack_d.s_charPointer;

    while (*p){
      printf("%c", *p);
      *p++;
    }
    std::cout << std::endl;

    char* s2 = stack_d.nest->s1;

    printf("{%s}\n", s2);
}

void global_class(int ran){
    // global object
    std::cout << "========Global==============\n";
    global_d.count(ran);
    global_d.testCase(ran);
    printf("U16 = %d\n", global_d.getu16());
    printf("U32 = %d\n", global_d.getu32());
    printf("Nest32 = 0x%4X\n", global_d.nest->nestVar);
    global_d.nest->hello();
    global_d.nest->Test();

    const char* p1 = global_d.s_charPointer;

    while (*p1){
      printf("%c", *p1);
      *p1++;
    }
    std::cout << std::endl;

    char* s3 = global_d.nest->s1;

    printf("{%s}\n", s3);
}

int main(void){
    setupStruct();
    printStruct(s_myStruct);
    printArray(myArray, 3);
    srand(time(0));
    int i = rand();
    pointer_class(i);
    stack_class(i);
    global_class(i);
    return 0;
}
