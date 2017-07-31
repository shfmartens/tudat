/*    Copyright (c) 2010-2017, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 *
 */

#include <boost/regex.hpp>

#include "modular.h"

namespace tudat
{

namespace json_interface
{

//! Get the path for a JSON file.
path getPathForJSONFile( const std::string& file, const path& basePath )
{
    try
    {
        // Get absolute path to input file
        path filePath = boost::filesystem::canonical( file, basePath );
        if ( boost::filesystem::is_directory( filePath ) )
        {
            // If it's a directory, try to find a "main.json" file in that directory
            return getPathForJSONFile( "main.json", filePath );
        }
        else
        {
            return filePath;
        }
    }
    catch ( ... )
    {
        std::string fileWithExtension = file;
        try
        {
            // Add .json extension if no extension found
            if ( path( file ).extension( ).empty( ) )
            {
                fileWithExtension += ".json";
                return boost::filesystem::canonical( fileWithExtension, basePath );
            }
            else
            {
                throw;
            }
        }
        catch ( ... )
        {
            std::cerr << "The file " << basePath / fileWithExtension << " does not exist." << std::endl;
            throw;
        }
    }
}

//! Parse a modular `json` object containing "#import" commands.
void parseModularJSON( json& jsonObject, const path& parentDirectoryPath )
{
    for ( json::iterator it = jsonObject.begin( ); it != jsonObject.end( ); ++it )
    {
        const std::string key = it.key( );
        json& value = it.value( );
        if ( value.is_structured( ) )  // it is an array or a JSON object
        {
            if ( value.is_array( ) )
            {
                for ( unsigned int i = 0; i < value.size( ); ++i )
                {
                    json& subvalue = value.at( i );
                    if ( subvalue.is_object( ) )
                    {
                        parseModularJSON( subvalue, parentDirectoryPath );
                    }
                }
            }
            else  // it is a JSON object (convertible to map / struct / class)
            {
                parseModularJSON( value, parentDirectoryPath );
            }
        }
        else if ( value.is_string( ) )
        {
            std::string importCommand = value;
            boost::regex expression { "#import\\s+(.+)" };
            boost::regex_token_iterator< std::string::iterator >
                    bit{ importCommand.begin( ), importCommand.end( ), expression, 1 };
            boost::regex_token_iterator< std::string::iterator > bend;
            while ( bit != bend )
            {
                const std::string fileToImport = *bit++;
                const json importedJson =
                        getParsedModularJSON( getPathForJSONFile( fileToImport, parentDirectoryPath ) );
                if ( importedJson.size( ) == 1 && importedJson.count( key ) == 1 )
                {
                    jsonObject[ key ] = importedJson[ key ];
                }
                else
                {
                    jsonObject[ key ] = importedJson;
                }
            }
        }
    }
}

//! -DOC
json getParsedModularJSON( const path& filePath )
{
    json jsonObject = json::parse( std::ifstream( filePath.string( ) ) );
    parseModularJSON( jsonObject, filePath.parent_path( ) );
    return jsonObject;
}

}  // namespace json_interface

}  // namespace tudat