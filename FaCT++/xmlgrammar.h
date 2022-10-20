#ifndef XML_GRAMMAR_H
#define XML_GRAMMAR_H

namespace Xml
{
    enum Token
    {
        BAD_LEX = 50,

        UNUSED, // never used one

        LEXEOF,

        TAG_START,
        TAG_END,

        DECLARATION_START,
        DECLARATION_END,

        DOCTYPE_START,
        DOCTYPE_END
    };
}
#endif
