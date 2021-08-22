#include "scarlet/common/Types.hpp"

#include "scarlet/core/Application.hpp"
#include "scarlet/core/Window.hpp"
#include "scarlet/core/Scene.hpp"

#include "scarlet/debug/Assert.hpp"
#include "scarlet/debug/OpenGLDebug.hpp"

#include "scarlet/system/AssetPool.hpp"
#include "scarlet/system/InputManager.hpp"
#include "scarlet/system/SceneManager.hpp"
#include "scarlet/system/EditorSceneManager.hpp"
#include "scarlet/system/StateManager.hpp"

#include "scarlet/imgui/ImGuiManager.hpp"

#include "scarlet/entity/GameObject.hpp"
#include "scarlet/entity/Registry.hpp"
#include "scarlet/entity/Component.hpp"
#include "scarlet/entity/Transform.hpp"
#include "scarlet/entity/SpriteRenderer.hpp"

#include "scarlet/graphics/GraphicsContext.hpp"
#include "scarlet/graphics/Renderer.hpp"
#include "scarlet/graphics/FrameBuffer.hpp"
#include "scarlet/graphics/VertexArray.hpp"
#include "scarlet/graphics/VertexBuffer.hpp"
#include "scarlet/graphics/IndexBuffer.hpp"
#include "scarlet/graphics/Shader.hpp"
#include "scarlet/graphics/Texture.hpp"
#include "scarlet/graphics/Sprite.hpp"

#include "scarlet/graphics/camera/Camera.hpp"

#include "scarlet/primitives/Line.hpp"
#include "scarlet/primitives/Rect.hpp"

#include "scarlet/math/Math.hpp"
#include "scarlet/math/Random.hpp"
#include "scarlet/math/Color.hpp"
#include "scarlet/math/Vector2.hpp"
#include "scarlet/math/Vector3.hpp"
#include "scarlet/math/Vector4.hpp"
#include "scarlet/math/Matrix4.hpp"

#include "scarlet/utils/MemoryUtils.hpp"
#include "scarlet/utils/StringUtils.hpp"
#include "scarlet/utils/TextureUtils.hpp"
#include "scarlet/utils/Time.hpp"
#include "scarlet/utils/logger/Logger.hpp"

#include "scarletEditor/CameraController.hpp"
#include "scarletEditor/GridLines.hpp"
#include "scarletEditor/Selector.hpp"
