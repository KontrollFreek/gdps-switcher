#pragma once

#include "Geode/utils/async.hpp"
#include "Geode/utils/web.hpp"
#include "Types.hpp"

#include <Geode/loader/Event.hpp>
#include <Geode/utils/web.hpp>

class LoadDataEventData {
	GDPSTypes::Server& m_server;

public:
    LoadDataEventData(GDPSTypes::Server& server) : m_server(server) {}
    GDPSTypes::Server& getServer() const;
};

class LoadDataEvent : public geode::Event<LoadDataEvent, bool(LoadDataEventData*)> {
	using Event::Event;
};

class ServerInfoManager {
	protected:
		static ServerInfoManager *m_instance;
		std::map<int, geode::async::TaskHolder<geode::utils::web::WebResponse>> m_listeners;
	public:
		void fetch(GDPSTypes::Server& server);

		static ServerInfoManager *get();
};
