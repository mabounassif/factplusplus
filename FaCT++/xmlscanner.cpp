#include "fpp_assert.h"

#include "xmlscanner.h"

inline bool XmlScanner::equal(const char* s, const char* s1, size_t length)
{
    switch(length)
    {
    case 8: if(s1[7] != s[7]) return false;
    case 7: if(s1[6] != s[6]) return false;
    case 6: if(s1[5] != s[5]) return false;
    case 5: if(s1[4] != s[4]) return false;
    case 4: if(s1[3] != s[3]) return false;
    case 3: if(s1[2] != s[2]) return false;
    case 2: if(s1[1] != s[1]) return false;
    case 1: if(s1[0] != s[0]) return false;
    case 0: return true;
    default: return strncmp(s,s1,length) == 0;
    }
}

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

    if (is_whitespace(c))
        c = skip_whitespace();

    if (c == 0)
        return Xml::LEXEOF;
    else if (c == '<')
        return scan_tag();

    return Xml::LEXEOF;
}

Xml::Token XmlScanner::scan_doctype(void)
{
    if (got_tail)
    {
        c_scan = &XmlScanner::scan_body;
        got_tail = false;
        return Xml::DOCTYPE_END;
    }

    char c;
    unsigned int tc = 0;

    for (LexBuffLength = 0; LexBuffLength < (MaxIDLength - 1); ++LexBuffLength)
    {
        c = NextChar();
        if (c == 0)
            return Xml::LEXEOF;

        LexBuff[LexBuffLength] = c;

        if (c == '\"')
            tc++;
        else if (c == '>' && (tc & 1) == 0)
        {
            got_tail = true;
            break;
        }
    }

    return Xml::DOCTYPE_DATA;
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
            break;

        append_tag_name(c);

        switch (LexBuffLength)
        {
        case 1:
            if (equal(LexBuff, "?", 1))
            {
                c_scan = &XmlScanner::scan_xml_declaration;
                return Xml::DECLARATION_START;
            }

            break;
        case 8:
            if (equal(LexBuff, "!DOCTYPE", 8))
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