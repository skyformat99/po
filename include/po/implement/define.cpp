#include "define.h"
#include <unordered_map>
#include <fstream>




namespace PO
{
	
	bool time_calculator::tick(time_point tp, duration& dua)
	{
		dua = std::chrono::duration_cast<duration>(tp - record_point);
		if (dua >= require_duration)
		{
			record_point = tp;
			return true;
		}
		return false;
	}


	/*
	bool binary::load_file(std::u16string path)
	{
		ptr.reset();
		std::ifstream file(utf16_to_asc(path), std::ios::binary | std::ios::in);
		if (file.good())
		{
			file.seekg(0, std::ios::end);
			auto end_poi = file.tellg();
			file.seekg(0, std::ios::beg);
			auto sta_poi = file.tellg();
			alloc(static_cast<size_t>(end_poi - sta_poi));
			file.read(*this, end_poi - sta_poi);
			update();
			return true;
		}
		return false;
	}
	*/

	
}