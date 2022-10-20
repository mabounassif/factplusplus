#ifndef XML_SCANNER_H
#define XML_SCANNER_H

#include "xmlgrammar.h"
#include "comscanner.h"

class XmlScanner : public CommonScanner
{
protected:
    void append_tag_name(char c);

    bool is_legal_tag_char(char c) const;
    bool is_whitespace(char c);

    char skip_whitespace(void);

public: // interface
    explicit XmlScanner(std::istream *inp) : CommonScanner(inp)
    {
        c_scan = &XmlScanner::scan_body;
    }

    /// get next token from stream
    Xml::Token GetLex(void) { return (this->*c_scan)(); };

    char *get_tagname(void);

private:
    typedef Xml::Token (XmlScanner::*scan)();
    scan c_scan; // current 'reader'

    unsigned int LexBuffLength;

    bool got_tail;

    Xml::Token scan_body();
    Xml::Token scan_tag();
    Xml::Token scan_xml_declaration();
    Xml::Token scan_doctype();

}; // XmlScanner

#endif
