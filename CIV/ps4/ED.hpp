#ifndef ED_HPP
#define ED_HPP

#include <iostream>
#include <string>
#include <vector>

class ED
{
  public:
    ED();
    ED(std::string string_one, std::string string_two);
    ~ED();
    int penalty(char a, char b);
    int min(int a, int b, int c);
    int OptDistance();
    std::string Alignment();

    // Debug methods
    void PrintMatrix();

  private:
    std::string _string_one, _string_two;
    std::vector< std::vector<std::string> > _matrix;
};

#endif
