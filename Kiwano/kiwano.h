// Copyright (c) 2016-2018 Kiwano - Nomango
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// Website: https://www.kiwano.cn
// Source Code: https://github.com/kiwano/kiwano
//


#pragma once

#include "macros.h"


//
// common
//

#include "common/Array.h"
#include "common/String.h"
#include "common/helper.h"
#include "common/closure.hpp"
#include "common/IntrusiveList.hpp"
#include "common/IntrusivePtr.hpp"
#include "common/ComPtr.hpp"
#include "common/noncopyable.hpp"
#include "common/Singleton.hpp"
#include "common/Json.h"


//
// math
//

#include "math/constants.hpp"
#include "math/scalar.hpp"
#include "math/ease.hpp"
#include "math/Vec2.hpp"
#include "math/rand.h"
#include "math/Matrix.hpp"


//
// base
//

#include "base/window.h"
#include "base/input.h"
#include "base/time.h"
#include "base/logs.h"
#include "renderer/render.h"
#include "platform/modules.h"
#include "platform/Application.h"

#include "base/Object.h"
#include "base/Event.hpp"
#include "base/EventListener.h"
#include "base/EventDispatcher.h"
#include "base/Timer.h"
#include "base/TimerManager.h"
#include "base/AsyncTask.h"
#include "base/Resource.h"

#include "2d/Font.hpp"
#include "2d/Color.h"
#include "2d/Transform.hpp"
#include "2d/TextStyle.hpp"

#include "2d/Image.h"
#include "2d/GifImage.h"
#include "2d/Frames.h"
#include "2d/Geometry.h"
#include "2d/Action.h"
#include "2d/ActionGroup.h"
#include "2d/ActionTween.h"
#include "2d/ActionHelper.h"
#include "2d/Animation.h"
#include "2d/ActionManager.h"
#include "2d/Transition.h"

#include "2d/Node.h"
#include "2d/Scene.h"
#include "2d/Layer.h"
#include "2d/Sprite.h"
#include "2d/Text.h"
#include "2d/Canvas.h"
#include "2d/GeometryNode.h"
#include "2d/DebugNode.h"


//
// utils
//

#include "utils/Path.h"
#include "utils/DataUtil.h"
#include "utils/File.h"
#include "utils/ResLoader.h"


//
// ui
//

#include "ui/Button.h"
#include "ui/Menu.h"
