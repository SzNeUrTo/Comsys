#include <iostream>
#include <fstream>
int main(int argc, char * argv[])
{
    std::fstream myfile("example.txt", std::ios_base::in);

    int a;
    while (myfile >> a)
    {
        printf("%d\n", a);
    }


    return 0;
}