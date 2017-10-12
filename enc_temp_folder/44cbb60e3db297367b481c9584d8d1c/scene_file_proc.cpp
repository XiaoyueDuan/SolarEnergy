#include "scene_file_proc.h"

SceneFileProc::SceneFileProc() {
	string_value_read_map["ground"] = StringValue::ground;
	string_value_read_map["Recv"] = StringValue::receiver;
	string_value_read_map["Grid"] = StringValue::grid;
}


bool SceneFileProc::SceneFileRead(SolarScene *solarscene, std::string filepath) {
	solarScene_ = solarscene;
	std::string str_line;
	std::ifstream scene_file;
	// ensure ifstream objects can throw exceptions:
	scene_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		//openfile
		scene_file.open(filepath);
		stringstream scene_stream;
		// read file's buffer contents into streams
		scene_stream << scene_file.rdbuf();
		//close the file handlers
		scene_file.close();
		while (getline(scene_stream, str_line)) {
			if (str_line[0] == '#' || str_line == "") { continue; }
#ifdef _DEBUG
			std::cout << str_line << std::endl;
#endif
			//get the
			std::stringstream line_stream;
			line_stream << str_line;  
			//get the line flag
			std::string line_head;
			line_stream >> line_head;
			if (string_value_read_map.count(line_head) == 0) {
				//std::cout << "illegal input" << std::endl;
				continue;
			}
			switch (string_value_read_map[line_head]) 
			{
				case StringValue::ground:
#ifdef _DEBUG
					std::cout << "get ground parameter" << std::endl;
#endif
					break;
				case StringValue::receiver:
#ifdef _DEBUG
					std::cout << "get receiver parameter" << std::endl;
#endif // DEBUG
					break;
				case StringValue::grid:
#ifdef _DEBUG
					std::cout << "get grid parameter" << std::endl;
#endif
					break;

			}
		}

	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		return false;
	}

	return true;
}