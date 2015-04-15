#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include "lodepng.h"


using namespace std;


int main(int argc, char **argv)
{
	printf("Thank you for using Caleb's image to header converter!\n\n");

	for (int img = 1; img < argc; img++)
	{
		//==========================================================
		//    Load Image File
		//----------------------------------------------------------
		unsigned char ** data;
		unsigned int w, h;
		int error = lodepng_decode24_file(data, &w, &h, argv[img]);
		int bitdepth = 3;

		// If there's an error, display it.
		if(error != 0)
		{
			printf("Error: lodepng, %s, %s\n", argv[img], lodepng_error_text(error));
			continue;		// skip to next image
		}
		else
		printf("Image loaded: (%dx%d) %s\n", w, h, argv[img]);
		

		//==========================================================
		//    Convert data
		//----------------------------------------------------------
		vector<unsigned char> output;
		for (int y = 0; y < h; y+=8)
		{
			printf("y: %d\n", y);
			for (int x = 0; x < w/bitdepth; x++)
			{
				printf("\tx: %d\n", x);
				unsigned char vertpix = 0;
				for (int z = 0; z < 8; z++)
				{
					printf("\t\tz: %d  ", z);
					printf("data[%d][%d] == %x\n", x * bitdepth, y + z, data[0][y + z + x * bitdepth]);
					if (data[0][y + z + x * bitdepth] > 0xA0) vertpix = vertpix | (0x01 << z); 
				}
				output.push_back(vertpix);

			}
			printf("\n");
		}
		printf("\n\t... converted %d pixes\n", output.size()*8);

		//==========================================================
		//    Output Data to File
		//----------------------------------------------------------
		fstream file;
		string imgName = argv[img];
		imgName.resize(imgName.size() - 3, 0);
		string outFileName = imgName + ".h";
		file.open(outFileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);

		// pre output
		file << "\nconst char " << imgName << "[] = {\n";

		for (int scan = 0; scan < output.size(); scan++) 
		{
			file << hex << output[scan] << ", ";
			if (scan % w == w - 1) file << "\n";
		}

		// post output
		file << "\n};\n";

		file.close();

		printf("\t... output finished\n");
	}
}