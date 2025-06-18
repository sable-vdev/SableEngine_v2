#include "SableEngine.hpp"
#include <memory>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	std::unique_ptr<SableEngine> engine = std::make_unique<SableEngine>();

	if (engine->Initialize())
	{
		try
		{
			while (engine->Run())
			{
			}


		}
		catch (const std::exception& ex)
		{
			//Logger::Log(ERROR, ex.what());
			return EXIT_FAILURE;
		}
	}
	engine->Shutdown();
	return EXIT_SUCCESS;
}