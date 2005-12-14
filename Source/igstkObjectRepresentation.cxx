/*=========================================================================

  Program:   Image Guided Surgery Software Toolkit
  Module:    igstkObjectRepresentation.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) ISIS Georgetown University. All rights reserved.
  See IGSTKCopyright.txt or http://www.igstk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "igstkObjectRepresentation.h" 
#include "vtkMatrix4x4.h"
#include "igstkEvents.h"
#include "vtkActor.h"
#include "vtkProp3D.h"
#include "vtkProperty.h"

namespace igstk 
{ 

/** Constructor */
ObjectRepresentation::ObjectRepresentation():m_StateMachine(this),m_Logger(NULL)
{
  m_Color[0] = 1.0;
  m_Color[1] = 1.0;
  m_Color[2] = 1.0;
  m_Opacity = 1.0;
  m_SpatialObject = NULL;
  m_LastMTime = 0;

  igstkAddInputMacro( ValidSpatialObjectInput );
  igstkAddInputMacro( NullSpatialObjectInput  );
  igstkAddInputMacro( UpdatePositionInput  );
  igstkAddInputMacro( UpdateRepresentationInput );

  igstkAddStateMacro( NullSpatialObjectState );
  igstkAddStateMacro( ValidSpatialObjectState );

  igstkAddTransitionMacro( NullSpatialObjectState, NullSpatialObjectInput, NullSpatialObjectState,  NoAction );
  igstkAddTransitionMacro( NullSpatialObjectState, ValidSpatialObjectInput, ValidSpatialObjectState,  SetSpatialObject );
  igstkAddTransitionMacro( NullSpatialObjectState, UpdatePositionInput, NullSpatialObjectState,  NoAction );
  igstkAddTransitionMacro( NullSpatialObjectState, UpdateRepresentationInput, NullSpatialObjectState,  NoAction );
 
  igstkAddTransitionMacro( ValidSpatialObjectState, UpdatePositionInput, ValidSpatialObjectState,  UpdatePosition );
  igstkAddTransitionMacro( ValidSpatialObjectState, NullSpatialObjectInput, NullSpatialObjectState,  NoAction ); 
  igstkAddTransitionMacro( ValidSpatialObjectState, ValidSpatialObjectInput, ValidSpatialObjectState,  NoAction ); 
  igstkAddTransitionMacro( ValidSpatialObjectState, UpdateRepresentationInput, ValidSpatialObjectState,  UpdateRepresentation );

  m_StateMachine.SelectInitialState( m_NullSpatialObjectState );

  m_StateMachine.SetReadyToRun();

} 

/** Destructor */
ObjectRepresentation::~ObjectRepresentation()  
{ 
  // This must be invoked in order to prevent Memory Leaks.
  this->DeleteActors();
}

/** Add an actor to the actors list */
void ObjectRepresentation::AddActor( vtkProp * actor )
{
  m_Actors.push_back( actor );
}

/** Empty the list of actors */
void ObjectRepresentation::DeleteActors()
{
  ActorsListType::iterator it = m_Actors.begin();
  while(it != m_Actors.end())
    {
    (*it)->Delete();
    it++;
    }

  // Reset the list of actors
  m_Actors.clear();
}

/** Has the object been modified */
bool ObjectRepresentation::IsModified() const
{
  if( m_LastMTime < this->GetMTime() )
    {
    return true;
    }
  return false;
}


/** Set the Spatial Object */
void ObjectRepresentation::RequestSetSpatialObject( const SpatialObjectType * spatialObject )
{
  m_SpatialObjectToAdd = spatialObject;
  if( !m_SpatialObjectToAdd )
    {
    m_StateMachine.PushInput( m_NullSpatialObjectInput );
    m_StateMachine.ProcessInputs();
    }
  else
    {
    m_StateMachine.PushInput( m_ValidSpatialObjectInput );
    m_StateMachine.ProcessInputs();
    }

}


/** Set the Spatial Object */
void ObjectRepresentation::SetSpatialObject()
{
  m_SpatialObject = m_SpatialObjectToAdd;
}



/** Set the color */
void ObjectRepresentation::SetColor(float r, float g, float b)
{
  if(m_Color[0] == r && m_Color[1] == g && m_Color[2] == b)
    {
    return;
    }
  m_Color[0] = r;
  m_Color[1] = g;
  m_Color[2] = b;

  // Update all the actors
  ActorsListType::iterator it = m_Actors.begin();
  while(it != m_Actors.end())
    {
    vtkActor * va = static_cast<vtkActor*>(*it);
    va->GetProperty()->SetColor(m_Color[0], m_Color[1], m_Color[2]); 
    it++;
    }
  this->Modified();
}


/** Request Update the object representation (i.e vtkActors). Maybe we should check also the transform
 *  modified time. */
void ObjectRepresentation::RequestUpdateRepresentation( const TimeStamp & time )
{
  m_TimeToRender = time; 
  m_StateMachine.PushInput( m_UpdateRepresentationInput );
  m_StateMachine.ProcessInputs();
}


/** Request Update the object position (i.e vtkActors). Maybe we should check also the transform
 *  modified time. */
void ObjectRepresentation::RequestUpdatePosition( const TimeStamp & time )
{
  m_TimeToRender = time; 
  m_StateMachine.PushInput( m_UpdatePositionInput );
  m_StateMachine.ProcessInputs();
}

/** Null operation for a State Machine transition */
void ObjectRepresentation::NoAction()
{
}

/** Update the object representation (i.e vtkActors). Maybe we should check also the transform
 *  modified time. */
void ObjectRepresentation::UpdatePosition()
{
  Transform transform = m_SpatialObject->GetTransform();

  vtkMatrix4x4* vtkMatrix = vtkMatrix4x4::New();

  transform.ExportTransform( *vtkMatrix );

  // Update all the actors
  ActorsListType::iterator it = m_Actors.begin();
  while( it != m_Actors.end() )
    {  
      vtkProp3D::SafeDownCast(*it)->SetUserMatrix(vtkMatrix);
     it++;
    }

  vtkMatrix->Delete();

  // Update the modified time
  m_LastMTime = this->GetMTime();
}


/** Print Self function */
void ObjectRepresentation::PrintSelf( std::ostream& os, itk::Indent indent ) const
{
  Superclass::PrintSelf(os, indent);
  os << indent << "Color: " << m_Color[0] << " : " << m_Color[1] << " : " << m_Color[2] << std::endl;
  os << indent << "Opacity: " << m_Opacity << std::endl;
}

} // end namespace igstk

