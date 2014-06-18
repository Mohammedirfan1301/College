#ifndef print_h
#define print_h
//5-18-2012

class printscreen{

public:
			printscreen();
			void cleargrid();
			void clearscreen();
			void intro();
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
			int a, b;
};
#endif
