#ifndef ED_HPP
#define ED_HPP

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdexcept>      // std::out_of_range
#include <vector>
#include <SFML/System.hpp>

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

    // Debug method - just prints out what the Matrix should look like.
    void PrintMatrix();

  private:
    std::string _string_one, _string_two;

    // Large vector, which holds inside of it vectors of type integer.
    std::vector< std::vector<int> > _matrix;
};

#endif
