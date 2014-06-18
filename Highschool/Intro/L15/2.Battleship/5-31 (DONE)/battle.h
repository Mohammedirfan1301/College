#ifndef battle_h
#define battle_h
//5-31-2012

class battleship{

public:
         battleship();
			void intro();
			void reset();
			void clear();
			void fill();
			void select();
			void cselect();
			void print();
			void playhit();
			void comphit();
			int whowin();
			int a, b, c, d;
			int col, row;
			char rows;
			int winner;

private:
			char playnavy [8][8];
			char compnavy [8][8];

};

#endif
