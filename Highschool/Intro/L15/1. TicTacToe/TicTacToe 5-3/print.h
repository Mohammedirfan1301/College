#ifndef print_h
#define print_h
//5-3-2012

class printscreen{

public:
			printscreen();
			void cleargrid();
			void clearscreen();
			void intro();
			//void menu();
			void map();
			void makemove();

private:
			char grid[3][3];
			int gametype;
			int move;
			int stop;
			int cpu;
			int a, b;
};
#endif
