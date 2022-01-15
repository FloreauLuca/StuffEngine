#pragma once
#include <utility/data_location.h>
#include <fstream>
#include <string>

#include "engine/engine.h"
#include "engine/system.h"

namespace stuff::advent
{
	class Day : public stuff::SystemInterface
	{
	public:
		Day(stuff::Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
		{
		}
		void Init() override;
		void Update(float dt) override;
		void Destroy() override;
		
		void Read(std::string path);
		void ReadFromName(std::string name);
		virtual std::string FindAnswer();
		virtual void DisplayAnswer();
	protected:
		void ParseInt();
		void ParseLineInt();
		void ParseString();
		std::ifstream myFile_;
		std::vector<int> intParsing_;
		std::vector<std::string> stringParsing_;
		
		stuff::Engine& engine_;
		stuff::Graphics& graphics_;
	};
}
