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

#include <optional>
#include <functional>

#include "../Helper.h"
#include "Bluetooth.h"

namespace Core::AirPods {

using Battery = std::optional<uint32_t>;

namespace Details {

struct BasicState {
    Battery battery;
    bool isCharging{false};

    inline bool operator==(const BasicState &rhs) const
    {
        return battery == rhs.battery && isCharging == rhs.isCharging;
    }
    inline bool operator!=(const BasicState &rhs) const
    {
        return battery != rhs.battery || isCharging != rhs.isCharging;
    }
};
} // namespace Details

enum class Model : uint32_t {
    Unknown = 0,
    AirPods_1,
    AirPods_2,
    AirPods_Pro,
    Powerbeats_3,
    Beats_X,
    Beats_Solo3,
};

enum class Side : uint32_t { Left, Right };

struct PodState : Details::BasicState {
    bool isInEar{false};

    inline bool operator==(const PodState &rhs) const
    {
        return *(Details::BasicState *)this == *(Details::BasicState *)&rhs &&
               isInEar == rhs.isInEar;
    }
    inline bool operator!=(const PodState &rhs) const
    {
        return *(Details::BasicState *)this != *(Details::BasicState *)&rhs ||
               isInEar != rhs.isInEar;
    }
};

struct CaseState : Details::BasicState {
    bool isBothPodsInCase{false};
    bool isLidOpened{false};

    inline bool operator==(const CaseState &rhs) const
    {
        return *(Details::BasicState *)this == *(Details::BasicState *)&rhs &&
               isBothPodsInCase == rhs.isBothPodsInCase && isLidOpened == rhs.isLidOpened;
    }
    inline bool operator!=(const CaseState &rhs) const
    {
        return *(Details::BasicState *)this != *(Details::BasicState *)&rhs ||
               isBothPodsInCase != rhs.isBothPodsInCase || isLidOpened != rhs.isLidOpened;
    }
};

struct PodsState {
    PodState left, right;

    inline bool operator==(const PodsState &rhs) const
    {
        return left == rhs.left && right == rhs.right;
    }
    inline bool operator!=(const PodsState &rhs) const
    {
        return left != rhs.left || right != rhs.right;
    }
};

struct State {
    Model model{Model::Unknown};
    PodsState pods;
    CaseState caseBox;

    inline bool operator==(const State &rhs) const
    {
        return model == rhs.model && pods == rhs.pods && caseBox == rhs.caseBox;
    }
    inline bool operator!=(const State &rhs) const
    {
        return model != rhs.model || pods != rhs.pods || caseBox != rhs.caseBox;
    }
};

std::optional<State> GetState();
void StartScanner();
QString GetDisplayName();
void OnBindDeviceChanged(uint64_t address);
void OnQuit();

} // namespace Core::AirPods

template <>
inline QString Helper::ToString<Core::AirPods::Model>(const Core::AirPods::Model &value)
{
    switch (value) {
    case Core::AirPods::Model::AirPods_1:
        return "AirPods 1";
    case Core::AirPods::Model::AirPods_2:
        return "AirPods 2";
    case Core::AirPods::Model::AirPods_Pro:
        return "AirPods Pro";
    case Core::AirPods::Model::Powerbeats_3:
        return "Powerbeats 3";
    case Core::AirPods::Model::Beats_X:
        return "BeatsX";
    case Core::AirPods::Model::Beats_Solo3:
        return "BeatsSolo3";
    default:
        return "Unknown";
    }
}

template <>
inline QString Helper::ToString<Core::AirPods::Side>(const Core::AirPods::Side &value)
{
    switch (value) {
    case Core::AirPods::Side::Left:
        return "Left";
    case Core::AirPods::Side::Right:
        return "Right";
    default:
        return "Unknown";
    }
}
