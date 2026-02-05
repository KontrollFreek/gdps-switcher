#pragma once

#include <Geode/ui/Popup.hpp>
#include <Geode/ui/ScrollLayer.hpp>

class BonusSettingsPopup : public geode::Popup {
    protected:
        bool init() override;
        geode::ScrollLayer *m_scroll = nullptr;
        std::vector<cocos2d::CCMenu*> m_options = {};
        bool m_reloadLayer = false;
    public:
        static BonusSettingsPopup *create();

        virtual void onClose(CCObject *sender) override;
};