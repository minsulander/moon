#ifndef MOON_INTERACTIVE_H
#define MOON_INTERACTIVE_H

#include "moon/Export.h"
#include "moon/Control.h"
#include <osgGA/GUIEventHandler>
#include <vector>

namespace moon {
	
	/// \addtogroup core
	/// @{
	
	class MOON_EXPORT InteractionCallback;
	
	enum InteractionType { ACTION };
	
	/// Interface class for interactive objects (user clickable etc)
	class MOON_EXPORT Interactive {
	public:
		/// Called when a user interacts with the object
		virtual void interaction(const InteractionType type);
		/// Add a callback that is called when a user interacts with the object
		void addInteractionCallback(InteractionCallback *callback);
		/// Remove a callback that is called when a user interacts with the object
		void removeInteractionCallback(InteractionCallback *callback);
		
		virtual ~Interactive() {}
	private:
		typedef std::vector< osg::ref_ptr<InteractionCallback> > InteractionCallbackList;
		InteractionCallbackList callbacks;
	};
	
	/// Callback class for user interactions
	/// \see Interactive, InteractionHandler
	class MOON_EXPORT InteractionCallback : public osg::Referenced {
	public:
		virtual void interaction(const InteractionType type)=0;
	};
	
	class MOON_EXPORT InteractionHandler : public osgGA::GUIEventHandler, public ControlListener {
	public:
		InteractionHandler();
		virtual ~InteractionHandler();
		virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor *);
		virtual void controlUpdate(Control *control);
	private:
		osg::ref_ptr<ListenerControl> actionControl;
	};
	
	/// @}
	
}

#endif
