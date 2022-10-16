#ifndef OWL_SCANNER_H
#define OWL_SCANNER_H

#include "xmlgrammar.h"
#include "comscanner.h"

class XmlScanner : public CommonScanner
{
public:     // interface

    explicit XmlScanner ( std::istream* inp ) : CommonScanner(inp) {
        c_scan = &XmlScanner::scan_body;
    }

        /// get next token from stream
    Xml::Token GetLex(void) { return (this->*c_scan)(); };

private:

    typedef Xml::Token (XmlScanner::*scan)();
    scan        c_scan; // current 'reader'

    Xml::Token scan_body();
    Xml::Token scan_tag();
}; // XmlScanner

#endif
