#include <iostream>
#include <vector> 
#include <string>
#include <fstream>
#include "calculator.h"
using namespace std;

int main()
{  
    Calculator *calculator = new Calculator();

    calculator->interpret_content();
    return 0;
}
