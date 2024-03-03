// StringUtils.cpp
// ECS 034
// -------------------------------------------------------------------------------------------------
// C++ Headers
#include <expat.h>
#include <iostream>
#include <sstream>
#include <cctype>
#include <cstddef>
#include <algorithm>
#include <vector>
// Project Headers
#include "StringUtils.h"
// -------------------------------------------------------------------------------------------------

namespace StringUtils
{

//  ( 1 ) Slice
//-------------------------------------------------------------------------------------------------
    std::string Slice( const std::string &str, ssize_t start, ssize_t end)noexcept
    { return str.substr(start,str.length()-start); }

// ( 2 ) Capitalize
//-------------------------------------------------------------------------------------------------
    std::string Capitalize(const std::string &str)noexcept
    {
        // Capitalize first character
        std::string temp_str = str;
        temp_str[0] = toupper(str[0]);

        // Lower all other characters
        for(size_t i = 1; i < temp_str.length(); i++) 
        { temp_str[i]= tolower(temp_str[i]); }
        return temp_str;
    }

// ( 3a ) Upper
//-------------------------------------------------------------------------------------------------
    std::string Upper(const std::string &str)noexcept
    { 
        // Capitalize all characters
        std::string temp_str = str;
        for(size_t i = 0; i < temp_str.length(); i++)
        { temp_str[i]= toupper(temp_str[i]); }
        return temp_str;
    }

//  ( 3b ) Lower
//-------------------------------------------------------------------------------------------------
    std::string Lower(const std::string &str)noexcept
    {
        // Lower all characters
        std::string temp_str = str;
        for(size_t i = 0; i < temp_str.length(); i++)
        { temp_str[i]= tolower(temp_str[i]); }
        return temp_str;
    }

//  ( 4a ) Left
//-------------------------------------------------------------------------------------------------
    std::string LStrip(const std::string &str)noexcept
    { 
        std::string line = str;
        auto pos = line.begin();
        while (pos != line.end() && std::isspace(*pos)) { pos++; }
        line.erase(line.begin(), pos);
        return line;
    }

// ( 4b ) Right
// -------------------------------------------------------------------------------------------------
    std::string RStrip(const std::string &str)noexcept
    {
        std::string line = str;
        std::reverse(line.begin(),line.end());
        auto pos = line.begin();
        while (pos != line.end() && std::isspace(*pos)) { pos++; }
        line.erase(line.begin(), pos);
        std::reverse(line.begin(), line.end());
        return line;
    }

//  ( 4c ) Both
//-------------------------------------------------------------------------------------------------
    std::string Strip(const std::string &str)noexcept
    {
        auto line = str;
        auto i = line.begin();
        while (i != line.end() && std::isspace(*i)) { i++; }
        line.erase(line.begin(), i);
        std::reverse(line.begin(), line.end());
        auto j = line.begin();
        while (j != line.end() && std::isspace(*j)) { j++; }
        line.erase(line.begin(), j);
        std::reverse(line.begin(), line.end());
        return line;
    }

//  ( 5a ) Center Justified
//-------------------------------------------------------------------------------------------------
    std::string Center(const std::string &str, int width, char fill)noexcept
    { 
        int padding = std::max(0, width - static_cast<int>(str.length()));
        
        // Odd Case
        if ( padding % 2 == 1) 
        {
            padding = ( padding/2 ); 
            return std::string(padding, fill) + str + std::string(padding + 1, fill); 
        }

        // Even Case
        else 
        { 
            padding = ( padding / 2 ); 
            return std::string(padding, fill) + str + std::string(padding, fill);
        }
    }

//  ( 5b ) Left Justified
//-------------------------------------------------------------------------------------------------
    std::string LJust(const std::string &str, int width, char fill)noexcept
    { 
        // Finds number of characters needed to reach desired width of string
        // Max protects against invalid inputs less than original str length
        int padding = std::max(0, width - static_cast<int>( str.length() ) );

        // Adds and returns string of length padding to str
        return str + std::string(padding, fill);
    }

//  ( 5c ) Right Justified
//-------------------------------------------------------------------------------------------------
    std::string RJust(const std::string &str, int width, char fill)noexcept
    { 
        // Finds number of characters needed to reach desired width of string
        // Max protects against invalid inputs less than original str length
        int padding = std::max(0, width - static_cast<int>( str.length() ) );

        // Adds and returns string of length padding to str
        return std::string(padding, fill) + str;
    }

//  ( 6 ) Replace
//-------------------------------------------------------------------------------------------------
    std::string Replace(const std::string &str, const std::string &old, const std::string &rep)noexcept
    {
        std::string newString = str;
        size_t pos = 0;
    
        // Checks if 'old' is empty
        if (old.empty()) 
        { return newString; }

        // Searches for instances of 'old'
        while ((pos = newString.find(old, pos)) != std::string::npos) 
        {
            newString.replace(pos, old.length(), rep);
            pos = pos + rep.length(); 
        }

        return newString;
    }

//  ( 7 ) Splits
//-------------------------------------------------------------------------------------------------
    std::vector< std::string > Split(const std::string &str, const std::string &splt )noexcept
    {
        std::vector<std::string> result;
        if (str.empty()) { return result; }
        int start = 0;
        int end = 0;

        // Splits string by spaces
        if (splt.empty())
        {
            while (start < str.size())
            {
                while (start < str.size() && std::isspace(str[start])) { ++start; }
                if (start >= str.size()) { break; }
                end = start;
                while (end < str.size() && !std::isspace(str[end])) { ++end; }
                result.push_back(str.substr(start, end - start));
                start = end;
            }
        }

        // Splits string by provided delimiter "splt"
        else
        {
            while (start < str.size() + 1)
            {
                end = str.find(splt, start);
                if (end == std::string::npos){ result.push_back(str.substr(start)); break; }
                result.push_back(str.substr(start, end - start));
                start = end + splt.size();
            }
        }

        return result;
    }


// ( 8 ) Join
// -------------------------------------------------------------------------------------------------
    std::string Join(const std::string &str, const std::vector< std::string >&vect)noexcept
    {
        std::string joined_string;
        for (size_t i = 0; i < vect.size(); i++) 
        {
            joined_string = joined_string + vect[i];
            if (i < vect.size() - 1) { joined_string += str; }
        }
        return joined_string;
    }

//  ( 9 ) Expand Tabs ( FIX LATER -> README.MD -> Issue 1 )
//-------------------------------------------------------------------------------------------------
    std::string ExpandTabs(const std::string &str, int tabsize )noexcept
    {
        std::string result = str;
        size_t pos = 0;
        
        while ((pos = result.find('\t', pos)) != result.size())
        {
            int spaces = tabsize - (pos % tabsize);
            result.replace(pos, 1, std::string(spaces, ' '));
            pos += spaces;
        }
        return result;
    }

    //  ( 10 ) Levenshtein Distance ( FIX LATER -> README.MD -> Issue 1 )
    //-------------------------------------------------------------------------------------------------
    int EditDistance(const std::string &left, const std::string &right, bool ignorecase)noexcept
    { 
        std::string temp_left = left;
        std::string temp_right = right;

        int total_edits = 0;
        int left_size = temp_left.length();
        int right_size = temp_right.length();
        int smallest_size; 
        
        // Initilizes total_edits with length difference between left and right
        if( std::abs( left_size - right_size ) != 0 ) { total_edits = std::abs( left_size - right_size ); }

        // Checks which string to iterate ( avoids out of bounds error ) 
        if( left_size == right_size ) { smallest_size = left_size; }
        else if( left_size < right_size ) { smallest_size = left_size; } 
        else if( left_size > right_size ) { smallest_size = right_size; }

        // Loop to change left_string -> right_string ( i = length of smallest string )
        for( int i = 0; i < smallest_size; i++ ) 
        {
            if( temp_left[i] != temp_right[i] ) 
            { total_edits = total_edits + 1; }
        }

        return total_edits;
    }
}