#include "fsplay.h"
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

void fsplay()
{
	puts("\n === C++17 <FILESYSTEM> working example...");
	puts("---------------------");

	//fs::path curdir = fs::current_path();
	fs::path mypath = ".";
	mypath /= "sss.py";

	printf("\ncur-path: %s\n", mypath.string().c_str());

	fs::path fullpath = fs::absolute(mypath);
	auto native = fullpath.string();
	auto generic = fullpath.generic_string();


	printf("\nnative abs-path: %s\n", native.c_str());

	printf("root-name: %s\n", fullpath.root_name().string().c_str());
	printf("root-dir: %s\n", fullpath.root_directory().string().c_str());
	printf("root-path: %s\n", fullpath.root_path().string().c_str());
	printf("relative-path: %s\n", fullpath.relative_path().string().c_str());

	printf("\ngeneric abs-path: %s\n", generic.c_str());

	printf("root-name: %s\n", fullpath.root_name().generic_string().c_str());
	printf("root-dir: %s\n", fullpath.root_directory().generic_string().c_str());
	printf("root-path: %s\n", fullpath.root_path().generic_string().c_str());
	printf("relative-path: %s\n", fullpath.relative_path().generic_string().c_str());


}
