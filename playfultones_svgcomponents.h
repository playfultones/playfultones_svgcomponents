/*
  ==============================================================================

   This file is part of the Playful Tones SVG Components module.
   Copyright (c) 2025 - Playful Tones

   The code included in this file is provided under the terms of the GPL v3 license:
   https://www.gnu.org/licenses/gpl-3.0.html

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

  ==============================================================================

    BEGIN_JUCE_MODULE_DECLARATION

      ID:                 playfultones_svgcomponents
      vendor:             Playful Tones
      version:            1.0.0
      name:               Playful Tones SVG Components
      description:        A collection of SVG-based JUCE components with builder pattern support
      website:            https://www.playfultones.com
      license:            GPL3

      dependencies:       juce_core, juce_gui_basics, Resvg4JUCE

    END_JUCE_MODULE_DECLARATION

*/

#pragma once
#define PLAYFULTONES_SVGCOMPONENTS_H_INCLUDED

#include <juce_core/juce_core.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <Resvg4JUCE/Resvg4JUCE.h>

namespace PlayfulTones
{
    namespace SVGComponents
    {
        #include "src/StaticImageComponent.h"
        #include "src/ButtonComponent.h"
        #include "src/DropdownComponent.h"
    }
}