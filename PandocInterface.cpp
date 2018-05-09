//
//  PandocInterface.cpp
//  Latr
//
//  Created by Amyth on 1/23/17.
//
//

#include "PandocInterface.h"


PandocInterface::PandocInterface(){
    
}

void PandocInterface::setSource(const char* sourceFile){
    source = sourceFile;
    std::size_t lastIndex = source.find_last_of("/\\");
    primary_directory = source.substr(0,lastIndex);
}

std::string PandocInterface::getSource(){
    return source;
}

void PandocInterface::setDirectory(const char* directory){
    primary_directory = directory;
}

void PandocInterface::setOutput(const char* outputFile){
    output = outputFile;
}

std::string PandocInterface::getOutput(){
    return output;
}

void PandocInterface::setBib(const char* bibFile){
    bib = bibFile;
}
std::string PandocInterface::getBib(){
    return bib;
}

void PandocInterface::setStyleLocation(const char* styleFile){
    style_location = styleFile;
}

std::string PandocInterface::getStyleLocation(){
    return style_location;
}

bool PandocInterface::executePandoc(const char* pandocLocation){
    
    //Assume that source and output is populated
    
    
    
    chdir(primary_directory.c_str());
    
    std::cout<<"executing Pandoc.."<<std::endl;
    
    std::string preCommand = pandocLocation;
    std::string strCommand = preCommand+"pandoc -s '";
    strCommand +=  source + "' ";
    
    if(bib.size()>0){
        strCommand += "--bibliography='" + bib + "' ";
        
        if(this->style_location.size()>0){
            strCommand += "--filter  "+preCommand+"pandoc-citeproc --csl='" + style_location +"' ";
        }
    }
    
    strCommand+= "-o '" + output +"'";
    
    std::cout<<strCommand.c_str()<<std::endl;
    
    //strCommand = preCommand+strCommand;
    system(strCommand.c_str());

    return true;
}

std::string PandocInterface::getStrCommand(){
    /*std::string strCommand = "pandoc -s ";
    strCommand += source + " ";
    
    if(bib.size()>0){
        strCommand += "--bibliography=" + bib + " ";
        
        if(this->style_location.size()>0){
            strCommand += "--filter  pandoc-citeproc --csl=" + style_location +" ";
        }
    }
    
    strCommand+= "-o " + output;*/
    
    return NULL;
    
}

