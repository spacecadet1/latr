//
//  LatexDiffInferface.hpp
//  Latr
//
//  Created by Amith on 1/23/17.
//
//

#ifndef LatexDiffInferface_H
#define LatexDiffInferface_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

class LatexDiffInterface{
    
    std::string source;
    std::string output;
    std::string previous;
public:
    LatexDiffInterface();
    
    std::string getSource();
    std::string getOutput();
    std::string getPrevious();
    
    void setSource(const char* sourceFile);
    void setOutput(const char* outputFile);
    void setPrevious(const char* previousFile);
    
    
    void executeLatexDiff(const char* latexdiff_location);
    
};


#endif /* LatexDiffInferface_H */


