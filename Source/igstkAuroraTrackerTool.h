/*=========================================================================

  Program:   Image Guided Surgery Software Toolkit
  Module:    igstkAuroraTrackerTool.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) ISIS Georgetown University. All rights reserved.
  See IGSTKCopyright.txt or http://www.igstk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __igstk_AuroraTrackerTool_h_
#define __igstk_AuroraTrackerTool_h_

#include "igstkTrackerTool.h"

namespace igstk
{
/** \class AuroraTrackerTool
  * \brief An Aurora-specific TrackerTool class.
  *
  * This class is a for providing Aurora-specific functionality
  * for TrackerTools, and also to allow compile-time type enforcement
  * for other classes and functions that specifically require
  * an Aurora tool.
*/

class AuroraTrackerTool : public TrackerTool
{
public:

  typedef AuroraTrackerTool              Self;
  typedef TrackerTool                    Superclass;
  typedef itk::SmartPointer<Self>        Pointer;
  typedef itk::SmartPointer<const Self>  ConstPointer;

  /** Run-time type information (and related methods). */
  igstkTypeMacro(AuroraTrackerTool, TrackerTool);

  /** Method for creation of a reference counted object. */
  igstkNewMacro(Self);  

protected:

  AuroraTrackerTool();
  ~AuroraTrackerTool();

  /** Print object information */
  virtual void PrintSelf( std::ostream& os, itk::Indent indent ) const; 

private:

  AuroraTrackerTool(const Self&);    //purposely not implemented
  void operator=(const Self&);       //purposely not implemented

};  


} // namespace igstk


#endif  // __igstk_AuroraTrackerTool_h_

