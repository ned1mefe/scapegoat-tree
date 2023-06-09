#include <iostream>

#include "TreeMap.h"

int main() {

    TreeMap<std::string, int> treeMap;

    treeMap.print();

    treeMap.update("tokyo", 37468000);
    treeMap.update("delhi", 28514000);
    treeMap.update("shangai", 25582000);
    treeMap.update("sao paulo", 21650000);
    treeMap.update("mexico city", 21581000);
    treeMap.update("cairo", 20076000);
    treeMap.update("mumbai", 19980000);
    treeMap.update("beijing", 19618000);
    treeMap.update("dhaka", 19578000);
    treeMap.update("osaka", 19281000);

    treeMap.print();

    std::cout<<std::endl;
    std::cout<<std::endl;

    std::cout<<treeMap.subMap("c","n")[0]<<std::endl;
    std::cout<<treeMap.subMap("c","n")[1]<<std::endl;
    std::cout<<treeMap.subMap("c","n")[2]<<std::endl;
    std::cout<<treeMap.subMap("c","n")[3]<<std::endl;
    std::cout<<treeMap.subMap("c","n")[4]<<std::endl;
    std::cout<<treeMap.subMap("c","n")[5]<<std::endl;

    std::cout<<std::endl;

    return 0;
}
