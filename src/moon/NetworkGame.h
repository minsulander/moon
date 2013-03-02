#ifndef MOON_NETWORKGAME_H
#define MOON_NETWORKGAME_H

#include "FactoryProduct.h"
#include "Export.h"
#include "moonet/NetworkObject.h"
#include <vector>

namespace moon {
	
	/// \ingroup core net
	/// @{
	
	class NetworkGameListener;
	
	/// Network object specifying data about a network game
	class MOON_EXPORT NetworkGame : public FactoryProduct, public moonet::NetworkObject {
	public:
		NetworkGame();
		NetworkGame(const NetworkGame& other, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moon, NetworkGame);
		virtual const std::string networkObjectName() const { return "moon_NetworkGame"; }
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		virtual bool serialize(const bool full);
		virtual void deserialize(const bool full, const double timediff = 0);
		
		const std::string& getScenarioName() { return scenarioName; }
		void setScenarioName(const std::string& name) { scenarioName = name; }
		const double getGameTime() { return gametime; }
		void setGameTime(const double time) { gametime = time; }
		
		static void registerListener(NetworkGameListener *listener);
		static void unregisterListener(NetworkGameListener *listener);
		
	private:
		std::string scenarioName;
		double gametime;
		
		typedef std::vector<NetworkGameListener*> ListenerList;
		static ListenerList listeners;
	};
	
	class MOON_EXPORT NetworkGameListener {
	public:
		/// Called when a NetworkGame update is received
		virtual void updateNetworkGame(NetworkGame *game, const bool fullUpdate) = 0;
		virtual ~NetworkGameListener() {}
	};

	/// @}
}

#endif
