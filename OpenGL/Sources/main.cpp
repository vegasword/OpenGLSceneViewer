#include <crtdbg.h>
#include <App.h>

using namespace std;
using namespace Core;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// _CrtSetBreakAlloc(770);

	App app(4, 5, false);
	app.Run();
	return 0;
}