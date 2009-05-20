#include <iostream>
#include <string>

#include "RcsbFile.h"
#include "CifFile.h"
#include "DicFile.h"

#include "CifParserBase.h"
#include "DICParserBase.h"

#include "CifFileUtil.h"


using std::cout;
using std::endl;
using std::string;


DicFile* GetDictFile(DicFile* ddlFileP, const string& dictFileName,
  const string& dictSdbFileName, const bool verbose, const eFileMode fileMode)
{
    DicFile* dictFileP = NULL;

    if (!dictFileName.empty())
    {
        dictFileP = ParseDict(dictFileName, ddlFileP, verbose);

        return(dictFileP);
    }

    if (!dictSdbFileName.empty())
    {
        dictFileP = new DicFile(fileMode, dictSdbFileName, verbose);

        return(dictFileP);
    }

    return(dictFileP);
}


void CheckDict(DicFile* dictFileP, DicFile* ddlFileP,
  const string& dictFileName, const bool extraChecks)
{
    string relLogFileName;
    RcsbFile::RelativeFileName(relLogFileName, dictFileName);

    relLogFileName += "-diag.log";

    dictFileP->DataChecking(*ddlFileP, relLogFileName, extraChecks);
}


void CheckCif(CifFile* cifFileP, DicFile* dictFileP, const string& cifFileName)
{
    string relLogFileName;
    RcsbFile::RelativeFileName(relLogFileName, cifFileName);
    
    relLogFileName += "-diag.log";

    cifFileP->DataChecking(*dictFileP, relLogFileName);
}


CifFile* ParseCif(const string& fileName, const bool verbose)
{
    CifFile* cifFileP = new CifFile(verbose);

    CifParser cifParser(cifFileP, cifFileP->GetVerbose());

    string diags;
    cifParser.Parse(fileName, diags);

    if (!diags.empty())
    {
        cout << "Diags for file " << fileName << "  = " << diags << endl;
    }

    return (cifFileP);
}


DicFile* ParseDict(const string& dictFileName, DicFile* inRefFileP,
  const bool verbose)
{
    CifFile* refFileP = NULL;

    DicFile* dictFileP = new DicFile(verbose);

    if (inRefFileP == NULL)
    {
        // DDL file parsing
        refFileP = dictFileP->GetRefFile();
    }
    else
    {
        refFileP = inRefFileP;
    }

    DICParser dicParser(dictFileP, refFileP, verbose);

    string diags;
    dicParser.Parse(dictFileName, diags);

    if (!diags.empty())
    {
        cout << "Dictionary file \"" << dictFileName << "\" parsing info "\
          "= " << diags << endl;
    }

    if (inRefFileP != NULL)
    {
        // Compres only if dictionary parsing is done
#ifndef VLAD_TMP_DEL_RESOLVE
        // The existence of Compress() indicates problems. Our code base
        // should never invoke this method !!!!
        dictFileP->Compress(refFileP);
#endif
    }
    else
    {
        delete (refFileP);
    }

    return (dictFileP);
}

