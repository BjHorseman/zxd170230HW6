//Zijia Ding
//zxd170230
//zxd170230@utdallas.edu
//CS3377.002

#ifndef _PROGRAM_6_H_
#define _PROGRAM_6_H_

#include<fstream>
#include<iostream>
#include<string>
#include<cdk.h>
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

class BinaryFileHeader
{
 public:

  uint32_t magicNumber;
  //should be 0XFEEDFACE
  uint32_t versionNumber;
  uint64_t numRecords;
};

const int maxRecordStringLength = 25;

class BinaryFileRecord
{
 public:

  uint8_t strLength;
  char stringBuffer [maxRecordStringLength];
};
#endif
