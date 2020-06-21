#include <iostream>

int main()
{
    std::cout << "hello world" << std::endl;

    bool arr[10]{};

    for (bool &i : arr)
        std::cout << i << ' ';
    std::cout << std::endl;

    return 0;
}