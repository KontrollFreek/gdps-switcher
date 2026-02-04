#include "ServerInfoManager.hpp"
#include "Geode/utils/web.hpp"
#include "utils/GDPSMain.hpp"

using namespace geode::prelude;

ServerInfoManager *ServerInfoManager::m_instance = nullptr;

void ServerInfoManager::fetch(GDPSTypes::Server& server) {
    if (server.infoLoaded == false) {
        server.infoLoaded = true;
        if (server.id < 0) return;
        // idk weird stuff
        int id = server.id;
        std::string url = server.url;

        auto req = web::WebRequest();

        std::string endpoint = server.url;
        if (!endpoint.empty() && endpoint.back() != '/')
            endpoint += "/";
        endpoint += "switcher/getInfo.php";

        m_listeners[server.id].spawn(
            req.get(endpoint),
            [this, id, url](web::WebResponse value) {
                if (value.json().isErr()) {
                    log::warn("Failed to parse info for {}: {}", url, value.json().err());
                } else {
                    auto info = value.json().unwrapOrDefault();
                    GDPSTypes::Server& server = GDPSMain::get()->m_servers[id];
                    server.motd = info["motd"].asString().unwrapOr("No MOTD found.");
                    server.icon = info["icon"].asString().unwrapOr("");
                    // serverData.modPolicy = info["mods"]["policy"].asString().unwrapOr(serverData.modPolicy);
                    // serverData.dependencies = info["mods"]["dependencies"].as<std::map<std::string, std::string>>().unwrapOr(serverData.dependencies);
                    // serverData.modList = info["mods"]["modList"].as<std::vector<std::string>>().unwrapOr(serverData.modList);
                    GDPSMain::get()->save();
                    LoadDataEventData event(server);
                    LoadDataEvent().send(&event);
                }
            }
        );
    }
}

GDPSTypes::Server& LoadDataEventData::getServer() const {
    return m_server;
}

ServerInfoManager *ServerInfoManager::get() {
    if (!m_instance) m_instance = new ServerInfoManager;
    return m_instance;
}