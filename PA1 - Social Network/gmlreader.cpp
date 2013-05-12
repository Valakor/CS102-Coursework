#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "gmlreader.h"
using namespace std;

int read_gml(const char*, vector<string>&, vector<string>&);

// GMLReader::GMLReader()
// {

// }

// // GMLReader::GMLReader(char *fn)
// // {
// //   fn_ = fn;
// // }

// GMLReader::~GMLReader()
// {

// }

bool GMLReader::read(const char *fn, vector<std::string>& nodes, vector<std::string>& edges)
{
  if(read_gml(fn, nodes, edges)){
    return false;
  }
  return true;

}


// bool GMLReader::openFile(char *fn)
// {
  
// }

// bool GMLReader::read(const char *fn, vector<std::string>& nodes, vector<std::string>& edges)
// {
//   ifstream myfile(fn);
//   if(myfile.fail()){
//     cerr << "Could not open file: " << fn << endl;
//     return false;
//   }
//   string line;
//   // will contain the raw text of nodes and edges
//   stringstream rawstream;

//   // get a line of text from the file
//   getline(myfile, line);

//   while(myfile.good()){
//     // check if its a comment '#'
//     string line_cpy = line;
//     stringstream ss(line_cpy);
//     char c;
//     ss >> c;
//     if (c != '#'){
//       rawstream << line << " ";
//     }

//     // get a line of text from the file
//     getline(myfile, line);

//   }
//   myfile.close();

//   // now strip out node and edge data
//   int level  = 0;
//   bool copyFlag = False;
//   stringstream nodeStr;
//   stringstream edgeStr;
//   string currToken;
//   rawstream >> currToken;
//   while( rawstream.good() ){
//     if(currToken == "node" || currToken == "edge"){
      
//     }
//   }

//   scope_level = 0;
  
// }
