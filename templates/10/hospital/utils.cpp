#include "utils.hh"

std::vector<std::string> utils::split( std::string& str, char delim )
{
    std::vector<std::string> result = {""};
    bool inside_quotation = false;
    for ( auto current_char : str )
    {
        if ( current_char == '"' )
        {
            inside_quotation = not inside_quotation;
        }
        else if ( current_char == delim and not inside_quotation)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" )
    {
        result.pop_back();
    }
    return result;
}

bool utils::is_numeric(std::string& s, bool zero_allowed)
{
    if( not zero_allowed )
    {
        bool all_zeroes = true;
        for( unsigned int i = 0; i < s.length(); ++i )
        {
            if( s.at(i) != '0' )
            {
                all_zeroes = false;
            }
        }
        if( all_zeroes )
        {
            return false;
        }
    }
    for( unsigned int i = 0; i < s.length(); ++i )
    {
        if( not isdigit(s.at(i)) )
        {
            return false;
        }
    }
    return true;
}
