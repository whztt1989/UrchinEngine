#ifndef ENGINE_URCHIN3DENGINE_H
#define ENGINE_URCHIN3DENGINE_H

#include "scene/SceneManager.h"
#include "scene/InputDevice.h"

#include "scene/renderer3d/light/LightManager.h"
#include "scene/renderer3d/shadow/ShadowManager.h"
#include "scene/renderer3d/camera/Camera.h"
#include "scene/renderer3d/camera/FpsCamera.h"
#include "scene/renderer3d/camera/FreeCamera.h"
#include "scene/renderer3d/model/Model.h"
#include "scene/renderer3d/light/sun/SunLight.h"
#include "scene/renderer3d/light/omnidirectional/OmnidirectionalLight.h"
#include "scene/renderer3d/antialiasing/AntiAliasingManager.h"

#include "scene/GUI/EventListener.h"
#include "scene/GUI/GUIRenderer.h"
#include "scene/GUI/widget/container/Container.h"
#include "scene/GUI/widget/window/Window.h"
#include "scene/GUI/widget/button/Button.h"
#include "scene/GUI/widget/staticbitmap/StaticBitmap.h"
#include "scene/GUI/widget/text/Text.h"
#include "scene/GUI/widget/textbox/TextBox.h"
#include "scene/GUI/widget/slider/Slider.h"

#include "texture/TextureManager.h"

#include "utils/shader/ShaderManager.h"

#include "utils/display/geometry/GeometryModel.h"
#include "utils/display/geometry/aabbox/AABBoxModel.h"
#include "utils/display/geometry/capsule/CapsuleModel.h"
#include "utils/display/geometry/cylinder/CylinderModel.h"
#include "utils/display/geometry/frustum/FrustumModel.h"
#include "utils/display/geometry/obbox/OBBoxModel.h"
#include "utils/display/geometry/points/PointsModel.h"
#include "utils/display/geometry/line/LineModel.h"
#include "utils/display/geometry/sphere/SphereModel.h"
#include "utils/display/geometry/convexhull/ConvexHullModel.h"

#endif
