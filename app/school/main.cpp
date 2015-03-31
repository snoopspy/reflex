#include <iostream>
#include <glog/logging.h>
#include "xmlparser.h"

int main()
{
  std::cout << "school\n";
  XmlParser xmlParser;
  bool res = xmlParser.load("_school.xml");
  DLOG(INFO) << "xmlParser.load return " << res;
  return 0;
}
