#pragma once

namespace big {
	class custom_text {
	public:
		void add_label_overwrite(std::string label, std::string text)
		{
			custom_text_map.insert({ label, text });
		}

		void add_label_overwrites(std::map<std::string, std::string> map)
		{
			for (auto const& [key, val] : map)
				custom_text_map.insert({ key, val });
		}

		void remove_label_overwrite(std::string label)
		{
			custom_text_map.erase(label);
		}

		void remove_label_overwrites(std::vector<std::string> labels)
		{
			for (auto label : labels)
				custom_text_map.erase(label);
		}

		void change_label_overwrite(std::string label, std::string new_text)
		{
			if (custom_text_map.find(label) != custom_text_map.end())
				custom_text_map.find(label)->second = new_text;
		}

		const char* get_label_overwrite(std::string label)
		{
			if (custom_text_map.find(label) != custom_text_map.end())
				return custom_text_map.find(label)->second.c_str();
			else
				return nullptr;
		}
	private:
		std::map<std::string, std::string> custom_text_map;
	};

	inline custom_text g_custom_text;
}
