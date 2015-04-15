#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include "lodepng.h"



int main(char *argv[], argc)
{
	system("cls");
	printf("Thank you for using Caleb's image->header converter!\n\n");

	for (int img = 0; img < argc; img++)
	{
		//==========================================================
		//    Load Image File
		//----------------------------------------------------------
		vector<unsigned char> data;
		int w, h;
		int error = lodepng::decode(data, w, h, argv[img]);

		// If there's an error, display it.
		if(error != 0)
		{
			printf("Error: lodepng, %s, %s\n", filename.c_str(), lodepng_error_text(error));
			return 1;
		}
		printf("Image loaded: (%dx%d) %s", w, h, argv[img]);


		//==========================================================
		//    Output Data to File
		//----------------------------------------------------------
		fstream file;
		char * imgName;
		int dot = strchr(argv[img], '.');
		strncpy(imgName, argv[img], dot);
		file.open(strcat(imgName, ".h"), std::fstream::in | std::fstream::out | std::fstream::app);

		// pre data
		file << "\nconst char " << imgName << "[] = {\n";

		///////////////  DATA HERE

		// post data
		file << "};\n";

		file.close();
	}
}