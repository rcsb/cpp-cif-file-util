//$$FILE$$
//$$VERSION$$
//$$DATE$$
//$$LICENSE$$


#ifndef CIFFILEUTIL_H
#define CIFFILEUTIL_H


#include <string>

#include "DicFile.h"
#include "CifFile.h"


DicFile* GetDictFile(DicFile* ddlFileP, const std::string& dictFileName,
  const std::string& dictSdbFileName = std::string(), const bool verbose =
  false, const eFileMode fileMode = READ_MODE);
void CheckDict(DicFile* dictFileP, DicFile* ddlFileP,
  const string& dictFileName, const bool extraChecks = false);
void CheckCif(CifFile* cifFileP, DicFile* dictFileP,
  const string& cifFileName);

DicFile* ParseDict(const std::string& dictFileName, DicFile* ddlFileP = NULL,
  const bool verbose = false);
CifFile* ParseCif(const std::string& fileName, const bool verbose = false,
  const Char::eCompareType caseSense = Char::eCASE_SENSITIVE,
  const unsigned int maxLineLength = CifFile::STD_CIF_LINE_LENGTH,
  const std::string& nullValue = CifString::UnknownValue);


#endif
