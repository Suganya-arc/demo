#include <iostream>
#include <map>
#include <functional>

typedef bool (*FnPtr)();
	std::map<std::string, FnPtr> myMap;

//volatile nsTestCase::nsTestCase* m_TestCaseInstance = NULL;

bool NS_T2()
{
    std::cout<<"inside NS_T2\n";
    return false;
}

bool NS_T3()
{
    std::cout<<"inside NS_T3\n";
    return true;
}

bool NS_G1()
{
    std::cout<<"inside NS_G1\n";
    return true;
}

int main() {
    // initialization:


	myMap["NS_T2"] = NS_T2;
	myMap["NS_T3"] = NS_T3;
	myMap["NS_G1"] = NS_G1;
	
    //~ // usage:
    std::string s("NS_T2");
    bool res = myMap[s]();
    std::cout << res;
}
