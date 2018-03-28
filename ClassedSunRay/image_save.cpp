#include "image_save.h"
#include "global_constant.h"
#include <iomanip>

void ImageSaver::savetxt(const string filename, int w, int h, float *h_data, int precision)
{
	ofstream out(filename.c_str());

	int address = 0;
	for (int r = 0; r < h; ++r)
	{
		for (int c = 0; c < w; ++c)
		{
			address = (h - 1 - r)*w + c;

			if (h_data[address] < Epsilon)
				out << 0 << ',';
			else
				out << fixed << setprecision(precision)<< h_data[address] << ',';
		}
		out << endl;
	}
	out.close();
}