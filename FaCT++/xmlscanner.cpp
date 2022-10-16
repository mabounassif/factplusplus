#include "xmlscanner.h"

Xml::Token XmlScanner :: scan_body ( void )
{
    char c = NextChar();

    if ( c == 0 ) return Xml::LEXEOF;
    else if ( c == '<' ) return scan_tag();
    
    return Xml::LEXEOF;
}

Xml::Token XmlScanner :: scan_tag ( void )
{
    
}
