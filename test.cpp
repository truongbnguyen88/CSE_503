#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

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
};

void swap(double x, double y){
    double temp = x;
    x = y;
    y = temp;
};

void swap_pass_by_ref(double &x, double &y){
    double temp = x;
    x = y;
    y = temp;
};

template <typename T>
T getRandomElement(const std::vector<T>& vec) {
    if (vec.empty()) {
        throw std::runtime_error("Vector is empty. Cannot select a random element.");
    }
    std::srand(std::time(nullptr)); // Seed the random number generator
    int randomIndex = std::rand() % vec.size();
    return vec[randomIndex];
}

class ResourceHandler {
public:
    // Constructor
    ResourceHandler(const std::string& resourceName) 
        : resourceName(resourceName), resource(new int(42)) {
        std::cout << "ResourceHandler for " << resourceName << " created." << std::endl;
    }

    // Destructor
    ~ResourceHandler() {
        delete resource;
        std::cout << "ResourceHandler for " << resourceName << " destroyed." << std::endl;
    }

    // Copy Constructor
    ResourceHandler(const ResourceHandler& other) 
        : resourceName(other.resourceName), resource(new int(*other.resource)) {
        std::cout << "ResourceHandler for " << resourceName << " copied." << std::endl;
    }

    // Move Constructor
    ResourceHandler(ResourceHandler&& other) noexcept 
        : resourceName(std::move(other.resourceName)), resource(other.resource) {
        other.resource = nullptr;
        std::cout << "ResourceHandler for " << resourceName << " moved." << std::endl;
    }

    // Copy Assignment Operator
    ResourceHandler& operator=(const ResourceHandler& other) {
        if (this == &other) return *this; // Handle self-assignment
        delete resource; // Free existing resource
        resourceName = other.resourceName;
        resource = new int(*other.resource);
        std::cout << "ResourceHandler for " << resourceName << " copy-assigned." << std::endl;
        return *this;
    }

    // Move Assignment Operator
    ResourceHandler& operator=(ResourceHandler&& other) noexcept {
        if (this == &other) return *this; // Handle self-assignment
        delete resource; // Free existing resource
        resourceName = std::move(other.resourceName);
        resource = other.resource;
        other.resource = nullptr;
        std::cout << "ResourceHandler for " << resourceName << " move-assigned." << std::endl;
        return *this;
    }

private:
    std::string resourceName;
    int* resource;
};

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

    /* pass-by-value vs. pass-by-reference */
    double a = 5.5;
    double b = 7.9;
    swap(a, b); // should not swap a & b because x & y are copies of a, b and swap() here only swap copies NOT a, b
    std::cout << "a=" << a << "b=" << b << std::endl;

    swap_pass_by_ref(a, b); //should swap values of a and b by using pass by reference
    std::cout << "a=" << a << "b=" << b << std::endl;

    /* std::move: To enable resource transfer instead of copying. */
    std::string str_a = "Hello! My name is Truong";
    std::string str_b = std::move(str_a);
    std::cout << "string a=" << str_a << std::endl;
    std::cout << "string b=" << str_b << std::endl;
    // After the move, a is still valid, but its contents are unspecified
    // b now owns the string — no deep copy is made

    /* copy & move constructor */
    ResourceHandler handler1("Resource1");
    ResourceHandler handler2 = handler1; // Copy constructor is called
    // Performs deep copy (custom) or shallow copy (default)
    // Copies all member variables from other into the new object

    ResourceHandler handler3 = std::move(handler1); // Move constructor is called
    // Transfers ownership of resources from other (e.g. pointers, buffers)
    // Leaves other in a valid but unspecified state

    ResourceHandler handler4("Resource4");
    handler4 = handler2; // Copy assignment operator is called
    // Deep or shallow copy of all member. May involve resource duplication

    ResourceHandler handler5("Resource5");
    handler5 = std::move(handler3); // Move assignment operator is called
    // Steals ownership of dynamic resources (like heap memory, containers. Leaves other in a valid but unspecified state

    /* Array init */
    int arr1[10];
    int n_elt = 100;
    int *arr2 = new int[n_elt];
    for (size_t i = 0; i < 10; i++) {
        arr1[i] = i;
    };
    for (size_t i = 0; i < n_elt; i++) {
        arr2[i] = i*2;
    };
    std::cout << "array arr1=" << arr1[5] << std::endl;
    std::cout << "array arr2=" << arr2[10] << std::endl;
    delete [] arr2;
    // cannot delete arr1 since it is fixed in memory but can delete arr2 because arr2 is dynamically allocated in memory

    return 0;
}
