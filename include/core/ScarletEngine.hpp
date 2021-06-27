#include "core/Application.hpp"
#include "core/Window.hpp"
#include "core/Time.hpp"

#include "core/Logger.hpp"

#include "core/Camera.hpp"

//Managers
#include "core/manager/InputManager.hpp"
#include "core/manager/SceneManager.hpp"

//ECS
#include "core/manager/GameObjectManager.hpp"
#include "core/GameObject.hpp"
#include "core/Component.hpp"

//Components
#include "core/components/SpriteRenderer.hpp"
#include "core/Sprite.hpp"

//Rendering
#include "core/renderer/Renderer.hpp"
#include "core/renderer/VertexArray.hpp"
#include "core/renderer/VertexBuffer.hpp"
#include "core/renderer/VertexBufferLayout.hpp"
#include "core/renderer/IndexBuffer.hpp"
#include "core/renderer/Shader.hpp"
#include "core/renderer/Texture.hpp"

//Primitives
#include "core/primitives/Rect.hpp"

//Math
#include "core/math/Math.hpp"
#include "core/math/Vector2.hpp"
#include "core/math/Vector3.hpp"
#include "core/math/Vector4.hpp"
#include "core/math/Matrix4.hpp"
