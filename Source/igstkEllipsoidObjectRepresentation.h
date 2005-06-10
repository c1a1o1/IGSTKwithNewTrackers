/*=========================================================================

  Program:   Image Guided Surgery Software Toolkit
  Module:    igstkEllipsoidObjectRepresentation.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) ISIS Georgetown University. All rights reserved.
  See IGSTKCopyright.txt or http://www.igstk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __igstkEllipsoidObjectRepresentation_h
#define __igstkEllipsoidObjectRepresentation_h

#include "igstkMacros.h"
#include "igstkObjectRepresentation.h"
#include "igstkEllipsoidObject.h"
#include "vtkSuperquadricSource.h"
#include "igstkStateMachine.h"

namespace igstk
{

/** \class EllipsoidObjectRepresentation
 * 
 * \brief This class represents an ellipsoid object. The parameters of the
 * object are the three radii defining the lenght of the principal axes of the
 * ellipsoid.  The axes of the ellipsoid are orthogonal. The Ellipsoidal object
 * is rendered in a VTK scene using the vtkSuperquadricSource object.

 * 
 * \ingroup ObjectRepresentation
 */

class EllipsoidObjectRepresentation 
: public ObjectRepresentation
{

public:

  /** Typedefs */
  typedef EllipsoidObjectRepresentation  Self;
  typedef ObjectRepresentation           Superclass;
  typedef itk::SmartPointer<Self>        Pointer;
  typedef itk::SmartPointer<const Self>  ConstPointer; 
  typedef EllipsoidObject                EllipsoidObjectType;

  /**  Run-time type information (and related methods). */
  igstkTypeMacro( EllipsoidObjectRepresentation, ObjectRepresentation );

  /** Method for creation of a reference counted object. */
  igstkNewMacro( EllipsoidObjectRepresentation );

  /** Return a copy of the current object representation */
  Pointer Copy() const;

  /** Connect this representation class to the spatial object */
  void RequestSetEllipsoidObject( const EllipsoidObjectType * ellipsoidObject );

  /** Declarations needed for the State Machine */
  igstkStateMachineMacro();

protected:

  EllipsoidObjectRepresentation( void );
  virtual ~EllipsoidObjectRepresentation( void );

  /** Print the object information in a stream. */
  virtual void PrintSelf( std::ostream& os, itk::Indent indent ) const; 

  /** Create the VTK actors per view */
  void CreateActors();

private:

  /** Internal itkSpatialObject */
  EllipsoidObjectType::ConstPointer   m_EllipsoidObject;

  /** VTK class that generates the geometrical representation of the cylinder */
  vtkSuperquadricSource * m_EllipsoidSource;

  /** update the visual representation with changes in the geometry */
  virtual void UpdateRepresentation();

  /** Connect this representation class to the spatial object. Only to be
   * called by the State Machine. */
  void SetEllipsoidObject(); 

private:

  /** Inputs to the State Machine */
  InputType            m_ValidEllipsoidObjectInput;
  InputType            m_NullEllipsoidObjectInput;
  
  /** States for the State Machine */
  StateType            m_NullEllipsoidObjectState;
  StateType            m_ValidEllipsoidObjectState;

  EllipsoidObjectType::ConstPointer m_EllipsoidObjectToAdd;

};

} // end namespace igstk

#endif // __igstkEllipsoidObjectRepresentation_h
