//
// AirPodsDesktop - AirPods Desktop User Experience Enhancement Program.
// Copyright (C) 2021 SpriteOvO
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#pragma once

#include <memory>
#include <cxxopts.hpp>
#include <SingleApplication>

#include "Gui/TrayIcon.h"
#include "Gui/MainWindow.h"
#include "Gui/DownloadWindow.h"
#include "Core/AirPods.h"
#include "Core/LowAudioLatency.h"

class ApdApplication : public SingleApplication
{
private:
    struct LaunchOptions {
        bool enableTrace{false};
    };

public:
    static bool PreInitialize(int argc, char *argv[]);
    ApdApplication(int argc, char *argv[]);

    bool Prepare();
    int Run();

    inline auto &GetTrayIcon()
    {
        return _trayIcon;
    }
    inline auto &GetMainWindow()
    {
        return _mainWindow;
    }
    inline auto &GetLowAudioLatencyController()
    {
        return _lowAudioLatencyController;
    }

    inline static bool IsFirstTimeUse()
    {
        return _isFirstTimeUse;
    }

    static void QuitSafety();

private:
    static inline LaunchOptions _launchOptions;
    static inline bool _isFirstTimeUse{false};
    std::unique_ptr<Gui::TrayIcon> _trayIcon;
    std::unique_ptr<Gui::MainWindow> _mainWindow;
    std::unique_ptr<Gui::DownloadWindow> _downloadWindow;
    std::unique_ptr<Core::LowAudioLatency::Controller> _lowAudioLatencyController;

    static void InitSettings();
    static void FirstTimeUse();

    void QuitHandler();
};

#define ApdApp (dynamic_cast<ApdApplication *>(QCoreApplication::instance()))
