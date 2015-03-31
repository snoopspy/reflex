#include <string.h>
#include <glog/logging.h>
#include "xmlparser.h"

static void _onStartElementNs(
  void *ctx,
  const xmlChar *localname,
  const xmlChar *prefix,
  const xmlChar *URI,
  int nb_namespaces,
  const xmlChar **namespaces,
  int nb_attributes,
  int nb_defaulted,
  const xmlChar **attributes
)
{
  std::string tag = std::string((const char*)localname);

  XmlParser::Attrs attrs;
  int index = 0;
  for (int i = 0; i < nb_attributes; ++i, index += 5)
  {
    XmlParser::Attr attr;
    attr.name = std::string((const char*)attributes[index]);
    attr.value = std::string(attributes[index + 3], attributes[index + 4]);
    attrs.push_back(std::move(attr));
  }

  XmlParser* xmlParser = (XmlParser*)ctx;
  xmlParser->onStartElement(tag, attrs);
}

static void _onEndElementNs(
  void* ctx,
  const xmlChar* localname,
  const xmlChar* prefix,
  const xmlChar* URI
)
{
  std::string tag = std::string((const char*)localname);

  XmlParser* xmlParser = (XmlParser*)ctx;
  xmlParser->onEndElement(tag);
}

static void _onCharacters(
  void *ctx,
  const xmlChar *ch,
  int len
)
{
  std::string _ch = std::string((const char*)ch, len);

  XmlParser* xmlParser = (XmlParser*)ctx;
  xmlParser->onCharacters(_ch);
}

XmlParser::XmlParser()
{
}

XmlParser::~XmlParser()
{
}

bool XmlParser::load(std::string fileName)
{
  xmlSAXHandler SAXHander;

  memset(&SAXHander, 0, sizeof(xmlSAXHandler));

  SAXHander.initialized = XML_SAX2_MAGIC;
  SAXHander.startElementNs = _onStartElementNs;
  SAXHander.endElementNs = _onEndElementNs;
  SAXHander.characters = _onCharacters;

  if (xmlSAXUserParseFile(&SAXHander, this, fileName.c_str()) < 0) {
      return false;
  }
  return true;
}

void XmlParser::onStartElement(std::string& tag, Attrs& attrs)
{
  std::string msg = "<" + tag + " ";
  for (auto it = attrs.begin(); it != attrs.end(); it++) {
    Attr& attr = *it;
    msg += attr.name + "='" + attr.value + "' ";
  }
  msg += ">";
  DLOG(INFO) << "XmlParser::onStartElement " << msg;
}

void XmlParser::onEndElement(std::string& tag)
{
  std::string msg = "<" + tag + "/>";
  DLOG(INFO) << "XmlParser::onEndElement   " << msg;
}

void XmlParser::onCharacters(std::string& ch)
{
  DLOG(INFO) << "XmlParser::onCharacters";
}
