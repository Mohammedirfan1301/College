#ifndef battle_h
#define battle_h
//5-22-2012

class battleship{

public:
         battleship();
			void intro();
			void print();

private:
			char playermap [8][8];
         char computmap [8][8];
};
#endif