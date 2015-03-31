#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <list>
#include <string>
#include <libxml/parser.h>

class XmlParser
{
public:
  struct Attr {
    std::string name;
    std::string value;
  };
  typedef std::list<Attr> Attrs;

public:
  XmlParser();
  virtual ~XmlParser();
  bool load(std::string fileName);

public:
  virtual void onStartElement(std::string& tag, Attrs& attrs);
  virtual void onEndElement(std::string& tag);
  virtual void onCharacters(std::string& ch);
};

#endif // XMLPARSER_H
