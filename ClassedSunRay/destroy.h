#pragma once
#include <vector>
using namespace std;

namespace free
{
	template <typename T>
	inline void cpu_free(T *t)
	{
		if (t != nullptr)
		{
			delete t;
			t = nullptr;
		}
	}

	template <typename T>
	inline void cpu_free(vector<T *> Tarray)
	{
		if (Tarray.size() > 0)
		{
			for (int i = 0; i < Tarray.size(); ++i)
			{
				if (Tarray[i] != nullptr)
				{
					delete Tarray[i];
					Tarray[i] = nullptr;
				}
			}
		}
	}

	template <typename T>
	inline void gpu_free(vector<T *> Tarray)
	{
		if (Tarray.size() > 0)
		{
			for (int i = 0; i < Tarray.size(); ++i)
			{
				if (Tarray[i] != nullptr)				
					Tarray->CClear();				
			}
		}
	}

	template <typename T>
	inline void gpu_free(T * t)
	{
		if (t != nullptr)
			t->CClear();
	}
}
