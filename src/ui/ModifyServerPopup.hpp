/*
 * Named modify instead of edit to avoid confusion
 * cause, well, EditServerPopup and ModifyServerPopup would be confusing
 */

#pragma once

#include "ui/ServerListLayer.hpp"
#include "Types.hpp"

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class ModifyServerPopup : public Popup {
    protected:
        TextInput *m_nameInput = nullptr;
        TextInput *m_urlInput = nullptr;
        TextInput *m_saveInput = nullptr;
        CCMenuItemSpriteExtra *m_saveBtn = nullptr;
        ServerListLayer *m_listLayer = nullptr;
        GDPSTypes::Server m_server;
        GDPSTypes::Server m_orig;

        bool m_isNew = true;

        bool init(GDPSTypes::Server server, ServerListLayer * layer);
    public:
        virtual void onClose(CCObject *sender) override;
        void onSave(CCObject *sender);

        void checkValidity();
        static ModifyServerPopup* create(GDPSTypes::Server server, ServerListLayer * layer);
};