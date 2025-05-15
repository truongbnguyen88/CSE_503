#include <iostream>
#include <string>

class Greeter {
public:
    Greeter(const std::string& name, double input1, double input2) 
        : name(name), input1(input1), input2(input2) {}
    /* Note: 
        - The usage of & is to reference: In this case, we references the original string (fast) and read-only 
        This is fast because we do not do copy and just reference
        - The usage of const is to read-only i.e., can't modify the value of name, just pass it in
    */

    void sayHello() const {
        std::cout << "Hello, " << name << "!" << std::endl;
    }
    double add() const {
        return input1 + input2;
    }

private:
    /* Set name variable to be private */
    std::string name;
    // double input1;
    // double input2;
public:
    double input1;
    double input2;
};

void demonstratePointer() {
    Greeter* greeterPtr = new Greeter("Pointer Example", 3.5, 4.5);
    greeterPtr->sayHello();
    std::cout << "Addition result using pointer: " << greeterPtr->add() << std::endl;
    delete greeterPtr; // Free the allocated memory
}

int main() {
    /* declaration */
    double result;

    /* code begins */
    Greeter greeter("World", 2.0, 2.7);
    greeter.sayHello();
    result = greeter.add();
    std::cout << result << std::endl;

    /* Pointer example */
    demonstratePointer();
    return 0;
}
