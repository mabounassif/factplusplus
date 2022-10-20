#include "fpp_assert.h"

#include "xmlscanner.h"

bool XmlScanner::is_legal_tag_char(char c) const
{
    return !isspace(c) && !eof(c);
}

bool XmlScanner::is_whitespace(char c)
{
    return c <= ' ' && (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f');
}

char XmlScanner::skip_whitespace(void)
{
    while (char c = NextChar())
    {
        if (!is_whitespace(c))
            return c;
    }
    return 0;
}

char *XmlScanner::get_tagname(void)
{
    return LexBuff;
}

Xml::Token XmlScanner::scan_body(void)
{
    char c = NextChar();

    if(is_whitespace(c))
        c = skip_whitespace();

    if (c == 0)
        return Xml::LEXEOF;
    else if (c == '<')
        return scan_tag();

    return Xml::LEXEOF;
}

Xml::Token XmlScanner::scan_doctype(void)
{
    return Xml::BAD_LEX;
}

Xml::Token XmlScanner::scan_xml_declaration(void)
{
    char c;

    for (LexBuffLength = 0; LexBuffLength < (MaxIDLength - 1); ++LexBuffLength)
    {
        c = NextChar();
        if (c == 0)
            return Xml::LEXEOF;
        LexBuff[LexBuffLength] = c;

        if (LexBuffLength >= 2 && LexBuff[LexBuffLength] == '>')
        {
            c_scan = &XmlScanner::scan_body;
            break;
        }
    }

    return Xml::DECLARATION_END;
}

Xml::Token XmlScanner::scan_tag(void)
{
    LexBuffLength = 0;

    char c = NextChar();

    while (c)
    {
        if (is_whitespace(c))
        {
            break;
        }

        append_tag_name(c);

        switch (LexBuffLength)
        {
        case 1:
            if (isKeyword("?"))
            {
                c_scan = &XmlScanner::scan_xml_declaration;
                return Xml::DECLARATION_START;
            }

            break;
        case 8:
            if (isKeyword("!DOCTYPE"))
            {
                c_scan = &XmlScanner::scan_doctype;
                return Xml::DOCTYPE_START;
            }

            break;
        }

        c = NextChar();
    }

    return Xml::TAG_START;
}

void XmlScanner::append_tag_name(char c)
{
    if (LexBuffLength < (MaxIDLength - 1))
        LexBuff[LexBuffLength++] = char(c);
}