#ifndef print_h
#define print_h
//5-7-2012

class printscreen{

public:
			printscreen();
			void cleargrid();
			void clearscreen();
			void intro();
			//void menu();
			void map();
			void makemoveX();
			void makemoveO();
			void test3();
			void endofgame();

private:
			char grid[3][3];
			int gametype;
			int move;
			int stop;
			int cpu;
			int a, b;
};
#endif
