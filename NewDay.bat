set /p Nb=Day:
set /p FileName=FileName:
set /p ClassName=ClassName:
"" > "data/adventofcode/day%Nb%_1.txt"
"" > "data/adventofcode/day%Nb%_test.txt"
echo #include "day%Nb%_%FileName%.h" > "main/adventofcode/src/day%Nb%_%FileName%.cpp"
echo namespace stuff::advent { >> "main/adventofcode/src/day%Nb%_%FileName%.cpp"
echo std::string Day%Nb%%ClassName%::FindAnswer(){} >> "main/adventofcode/src/day%Nb%_%FileName%.cpp"
echo void Day%Nb%%ClassName%::DisplayAnswer(){}}  >> "main/adventofcode/src/day%Nb%_%FileName%.cpp"

echo #pragma once > "main/adventofcode/include/day%Nb%_%FileName%.h"
echo #include ^<array^> >> "main/adventofcode/include/day%Nb%_%FileName%.h"
echo #include ^<day.h^> >> "main/adventofcode/include/day%Nb%_%FileName%.h"
echo namespace stuff::advent{ >> "main/adventofcode/include/day%Nb%_%FileName%.h"
echo class Day%Nb%%ClassName% : public Day{ >> "main/adventofcode/include/day%Nb%_%FileName%.h"
echo public: >> "main/adventofcode/include/day%Nb%_%FileName%.h"
echo 	Day%Nb%%ClassName%(stuff::Engine^& engine) : Day(engine) {} >> "main/adventofcode/include/day%Nb%_%FileName%.h"
echo 	std::string FindAnswer() override; >> "main/adventofcode/include/day%Nb%_%FileName%.h"
echo 	void DisplayAnswer() override; >> "main/adventofcode/include/day%Nb%_%FileName%.h"
echo private: 	};  } >> "main/adventofcode/include/day%Nb%_%FileName%.h"

