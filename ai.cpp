#include <sstream>
#include <fstream>
#include <cstdlib>
#include "bintree.cpp"

//simple ai
class ai
{
public:
	//default constructor
	ai();
	//loads binary tree from file
	void loadFromFile(std::string FileName);

	//creates basic binary tree
	void constructBasic();

	//starts learning process
	void LearningProcess();

	//exports binary tree to file
	void exportToFile();

	//gets user input
	std::string getUserInput();

	//handles routing between comands
	void commandRouter();

	//terminates/exits program
	void Exit();
private:
	enum Commands : const char
	{
		BASIC = 'a', LOAD = 'b', LEARN = 'c', EXPORT = 'd', EXIT = 'e'
	};

	//our binary tree
	bintree<std::string> tree;
};

void ai::loadFromFile(std::string FileName)
{
	std::string line;
	std::ifstream file;
	file.open(FileName);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			tree.StoreData(line);
		}
		file.close();
		std::cout << "AI: rozhodovaci strom nacitany." << std::endl;
	}
}

void ai::constructBasic()
{
	tree.BuildRoot("Ma to dve nohy?");
	tree.push_left("kon");
	tree.push_right("vtal");
	std::cout << "AI: zakladny rozhodavci strom vytvoreny." << std::endl;
}

void ai::exportToFile()
{
	if (tree.size() == 0)
	{
		constructBasic();
	}
	std::ofstream file;
	file.open("out");
	if (file.is_open())
	{
		for (bintree<std::string>::Iterator it = tree.begin(); it != tree.end(); ++it)
		{
			file << *it << ",";
			if (it->IsLeaf())
			{
				file << "-1,";
			}
		}
		file.close();
		std::cout << "AI: rozhodovaci strom exportovany" << std::endl;
	}
}

void ai::Exit()
{
	exit(0);
}

void ai::commandRouter()
{
	std::string line;
	while (true)
	{
		line = getUserInput();

		switch (line[0])
		{
		case BASIC:
			constructBasic();
			break;
		case LOAD:
			loadFromFile(line.substr(1,line.length()));
			break;
		case LEARN:
			LearningProcess();
			break;
		case EXPORT:
			exportToFile();
			break;
		case EXIT:
			Exit();
			break;
		}
	}
}

std::string ai::getUserInput()
{
	std::string line;

	std::cout << "USER: ";
	getline(std::cin, line);
	std::cout << std::endl;

	// Clear the input buffer otherwise doesnt prompt user input and throws exception 
	//(/ n, end of the line character stays in buffer)
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return line;
}

void ai::LearningProcess()
{
	std::string line;
	std::cout << "AI: myslite na nejaky objekt. odpovedajte na moje otazky." << std::endl;

	bintree<std::string>::Iterator it = tree.begin();
	do
	{
		std::cout << "AI: " << *it << "(y/n)" << std::endl;
		line = getUserInput();
		if (line[0] == 'n')
		{
			it.move_left();
		}
		else
		{
			it.move_right();
		}
	}while (!it->IsLeaf());

	std::cout << "AI: mysleli ste na objekt " << *it << "?" << std::endl;
	line = getUserInput();

	if (line[0] == 'n')
	{
		std::cout << "AI: na aky objekt ste mysleli?" << std::endl;
		std::string answer = getUserInput();

		std::cout << "AI: prosim zadajte otazku, na ktoru odpoviete ano pre vas objekt a nie pre moj objekt" << std::endl;
		std::string question = getUserInput();

		tree.InsertBefore(it, question, answer);
		std::cout << "AI: ucenie dokoncene" << std::endl;
	}
	else
	{
		std::cout << "AI: SOM INTELIGENTNY." << std::endl;
	}
}

ai::ai()
{
	commandRouter();
}

int main()
{
	ai simpleAI;

	return 0;
}