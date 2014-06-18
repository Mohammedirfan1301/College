#ifndef print_h
#define print_h
//5-11-2012

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
			int test3();
			void endofgame();
			int stop;

private:
			char grid[3][3];
			int gametype;
			int move;
			//int cpu;
			int a, b;
};
#endif
