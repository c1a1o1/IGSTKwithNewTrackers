/*=========================================================================

  Program:   Image Guided Surgery Software Toolkit
  Module:    igstkAuroraTrackerToolTest.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) ISC  Insight Software Consortium.  All rights reserved.
  See IGSTKCopyright.txt or http://www.igstk.org/copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#if defined(_MSC_VER)
//  Warning about: identifier was truncated to '255' characters 
//  in the debug information (MVC6.0 Debug)
#pragma warning( disable : 4786 )
#endif

#include <iostream>
#include <fstream>

#include "igstkAuroraTrackerTool.h"


int igstkAuroraTrackerToolTest( int, char * [] )
{
  igstk::RealTimeClock::Initialize();

  typedef igstk::AuroraTrackerTool           TrackerToolType;
  typedef TrackerToolType::TransformType     TransformType;
    
  TrackerToolType::Pointer trackerTool = TrackerToolType::New();

  trackerTool->RequestConfigure();

  std::cout << trackerTool << std::endl;

  return EXIT_SUCCESS;
}
