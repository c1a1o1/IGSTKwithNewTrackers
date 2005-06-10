/*=========================================================================

  Program:   Image Guided Surgery Software Toolkit
  Module:    igstkSpatialObject.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) ISIS Georgetown University. All rights reserved.
  See IGSTKCopyright.txt or http://www.igstk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __igstkSpatialObject_h
#define __igstkSpatialObject_h

#include "igstkMacros.h"
#include "itkObject.h"
#include "itkSpatialObject.h"
#include "igstkTransform.h"
#include "igstkStateMachine.h"
#include "igstkTrackerTool.h"
#include "igstkEvents.h"
#include "itkCommand.h"

namespace igstk
{

/** \class SpatialObject
 * 
 * \brief This class encapsulates an ITK spatial object with the goal of
 * restricting access to functionalities that are not essential for IGS
 * applications, or to functionalities thay may present risks and unnecessary
 * flexibility.  This is an abstract class, you should use the derived classes
 * that represent specific shapes.
 *
 * \ingroup Object
 */

class SpatialObject : public itk::Object
{

public:

  /** Typedefs */
  typedef SpatialObject                  Self;
  typedef itk::Object                    Superclass;
  typedef itk::SmartPointer<Self>        Pointer;
  typedef itk::SmartPointer<const Self>  ConstPointer; 
  typedef itk::SpatialObject<3>          SpatialObjectType;

  /**  Run-time type information (and related methods). */
  igstkTypeMacro( SpatialObject, Object );

  /** Set the Transform corresponding to the ObjectToWorld transformation of
   * the SpatialObject. */
  void RequestSetTransform( const Transform & transform );

  /** Return the Transform associated to the ObjectToWorld transformation
   * of the SpatialObject */
  const Transform & GetTransform() const;

  /** Request the protocol for attaching to a tracker tool. This is a one-time
   * operation. Once a Spatial Object is attached to a tracker tool it is not
   * expected to get back to manual nor to be re-attached to a second tracker
   * tool. */
  void RequestAttachToTrackerTool( const TrackerTool * trackerTool );

  /** Declarations needed for the State Machine */
  igstkStateMachineMacro();

protected:

  SpatialObject( void );
  ~SpatialObject( void );

  /** Connect this representation class to the spatial object */
  void RequestSetSpatialObject( SpatialObjectType * );

  /** Print the object information in a stream. */
  virtual void PrintSelf( std::ostream& os, itk::Indent indent ) const; 


private:
  
  /** Command observer that will receive events from traker tools */
  typedef ::itk::ReceptorMemberCommand< Self >           CommandType;

  /** Internal itkSpatialObject */
  SpatialObjectType::Pointer   m_SpatialObject;
  SpatialObjectType::Pointer   m_SpatialObjectToBeSet;

  /** Internal Transform and temporary transform */
  Transform                    m_Transform;
  Transform                    m_TransformToBeSet;

  /** TrackerTool to be attached to, and temporary pointer */
  TrackerTool::ConstPointer    m_TrackerTool;
  TrackerTool::ConstPointer    m_TrackerToolToAttachTo;

  /** Command observer that will listen for Events sent from a TrackerTool. */
  CommandType::Pointer         m_TrackerToolObserver;

  /** Command observer that will listen for Events sent from a TrackerTool. */
  virtual void TransformUpdateFromTrackerTool( const ::itk::EventObject & event  );

  /** Set the Transform corresponding to the ObjectToWorld transformation of
   * the SpatialObject. This method is only intended to be called from a callback
   * that is observing events from a TrackerTool object. */
  void RequestSetTrackedTransform(const Transform & transform );

  /** Inputs to the State Machine */
  InputType            m_SpatialObjectNullInput;
  InputType            m_SpatialObjectValidInput;
  InputType            m_TrackingEnabledInput;
  InputType            m_TrackingLostInput;
  InputType            m_TrackingRestoredInput;
  InputType            m_TrackingDisabledInput;
  InputType            m_ManualTransformInput;
  InputType            m_TrackerTransformInput;

  /** States for the State Machine */
  StateType            m_InitialState;
  StateType            m_NonTrackedState;
  StateType            m_TrackedState;
  StateType            m_TrackedLostState;

  /** Action methods to be invoked only by the state machine */
  void SetSpatialObject();
  void ReportTrackingRestored();
  void ReportTrackingDisabled();
  void ReportTrackingLost();
  void ReportInvalidRequest();
  void AttachToTrackerTool();
  void SetTransform();
  
};

} // end namespace igstk

#endif // __igstkSpatialObject_h
