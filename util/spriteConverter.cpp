#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "lodepng.h"


using namespace std;


int main(int argc, char **argv)
{
	printf("Thank you for using Caleb's image to header converter!\n\n");

	//==========================================================
	//    Open output file
	//----------------------------------------------------------
	FILE *file;
	string outFileName = "sprites.h";
	file = fopen(outFileName.c_str(), "w");
	if (file == NULL)
	{
		printf("Error: cannot open output file %s\n", outFileName.c_str());
		return 1;
	}


	for (int img = 1; img < argc; img++)
	{
		//==========================================================
		//    Load Image File
		//----------------------------------------------------------
		unsigned char * data;
		unsigned int w, h;
		int error = lodepng_decode24_file(&data, &w, &h, argv[img]);
		int bitdepth = 3;

		// If there's an error, display it.
		if(error != 0)
		{
			printf("Error: lodepng, %s, %s\n", argv[img], lodepng_error_text(error));
			continue;		// skip to next image
		}
		else
		printf("Image loaded: (%d x %d) %s\n", w, h, argv[img]);
		

		//==========================================================
		//    Convert data
		//----------------------------------------------------------
		unsigned char *output = (unsigned char*)malloc(w * h / 8);
		for (int y = 0; y < h/8; y++)
		{
			for (int x = 0; x < w; x++)
			{
				unsigned char vertpix = 0;
				for (int z = 0; z < 8; z++)
				{
					int xx = x * bitdepth;
					int yy = y * 8 + z;
					int uv = xx + yy * (w * bitdepth);
					if (data[uv] > 0xA0) vertpix = vertpix | (0x01 << z); 
				}
				output[x + y * w] = vertpix;

			}
		}
		printf("\t... converted %d pixes\n", w * h);
		free(data);

		//==========================================================
		//    Output Data to File
		//----------------------------------------------------------
		string imgName = argv[img];
		imgName = imgName.substr(imgName.find_last_of('\\') + 1, imgName.find_first_of('.') - imgName.find_last_of('\\') - 1);
		
		// pre output
		fprintf(file, "\nconst char %s[] = \n{\n", imgName.c_str());

		for (int scan = 0; scan < w * h / 8; scan++) 
		{
			if (scan % w == 0) fprintf(file, "\t");
			fprintf(file, "0x%02x, ", output[scan]);
			if (scan % w == w - 1) fprintf(file, "\n");
		}

		// post output
		fprintf(file, "};\n");
		printf("\t... output finished\n");
		free(output);
	}
	fclose(file);
}