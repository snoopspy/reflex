#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <string>
#include <libxml/parser.h>

namespace school {
  class XmlParser
  {
  public:
    XmlParser();
    ~XmlParser();
    bool load(std::string fileName);
  };
}

#endif // XMLPARSER_H
