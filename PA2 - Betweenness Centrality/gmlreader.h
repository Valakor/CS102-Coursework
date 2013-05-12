#ifndef GMLREADER_H
#define GMLREADER_H
#include <vector>
#include <string>

class GMLReader
{
 public:
  static bool read(const char *fn, std::vector<std::string>& nodes, std::vector<std::string>& edges);
  
 private:



};

#endif
