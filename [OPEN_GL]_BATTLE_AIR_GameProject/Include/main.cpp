#include <iostream>
#include "testClass.h"

using namespace std;

testClass* g_test = nullptr;

int main(void)
{

	g_test = new testClass;
	
	g_test->Render();

	delete g_test;



	return 0;


}