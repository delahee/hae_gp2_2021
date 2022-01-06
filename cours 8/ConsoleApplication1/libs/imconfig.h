//-----------------------------------------------------------------------------
// COMPILE-TIME OPTIONS FOR DEAR IMGUI
// Runtime options (clipboard callbacks, enabling various features, etc.) can generally be set via the ImGuiIO structure.
// You can use ImGui::SetAllocatorFunctions() before calling ImGui::CreateContext() to rewire memory allocation functions.
//-----------------------------------------------------------------------------
// A) You may edit imconfig.h (and not overwrite it when updating Dear ImGui, or maintain a patch/rebased branch with your modifications to it)
// B) or '#define IMGUI_USER_CONFIG "my_imgui_config.h"' in your project and then add directives in your own file without touching this template.
//-----------------------------------------------------------------------------
// You need to make sure that configuration settings are defined consistently _everywhere_ Dear ImGui is used, which include the imgui*.cpp
// files but also _any_ of your code that uses Dear ImGui. This is because some compile-time options have an affect on data structures.
// Defining those options in imconfig.h will ensure every compilation unit gets to see the same data structure layouts.
// Call IMGUI_CHECKVERSION() from your .cpp files to verify that the data structures your files are using are matching the ones imgui.cpp is using.
//-----------------------------------------------------------------------------

#pragma once

//---- Define assertion handler. Defaults to calling assert().
// If your macro uses multiple statements, make sure is enclosed in a 'do { .. } while (0)' block so it can be used as a single statement.
//#define IM_ASSERT(_EXPR)  MyAssert(_EXPR)
//#define IM_ASSERT(_EXPR)  ((void)(_EXPR))     // Disable asserts

//---- Define attributes of all API symbols declarations, e.g. for DLL under Windows
// Using Dear ImGui via a shared library is not recommended, because of function call overhead and because we don't guarantee backward nor forward ABI compatibility.
// DLL users: heaps and globals are not shared across DLL boundaries! You will need to call SetCurrentContext() + SetAllocatorFunctions()
// for each static/DLL boundary you are calling from. Read "Context and Memory Allocators" section of imgui.cpp for more details.
//#define IMGUI_API __declspec( dllexport )
//#define IMGUI_API __declspec( dllimport )

//---- Don't define obsolete functions/enums/behaviors. Consider enabling from time to time after updating to avoid using soon-to-be obsolete function/names.
//#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS

//---- Disable all of Dear ImGui or don't implement standard windows.
// It is very strongly recommended to NOT disable the demo windows during development. Please read comments in imgui_demo.cpp.
//#define IMGUI_DISABLE                                     // Disable everything: all headers and source files will be empty.
//#define IMGUI_DISABLE_DEMO_WINDOWS                        // Disable demo windows: ShowDemoWindow()/ShowStyleEditor() will be empty. Not recommended.
//#define IMGUI_DISABLE_METRICS_WINDOW                      // Disable metrics/debugger and other debug tools: ShowMetricsWindow() and ShowStackToolWindow() will be empty.

//---- Don't implement some functions to reduce linkage requirements.
//#define IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCTIONS   // [Win32] Don't implement default clipboard handler. Won't use and link with OpenClipboard/GetClipboardData/CloseClipboard etc. (user32.lib/.a, kernel32.lib/.a)
//#define IMGUI_ENABLE_WIN32_DEFAULT_IME_FUNCTIONS          // [Win32] [Default with Visual Studio] Implement default IME handler (require imm32.lib/.a, auto-link for Visual Studio, -limm32 on command-line for MinGW)
//#define IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS         // [Win32] [Default with non-Visual Studio compilers] Don't implement default IME handler (won't require imm32.lib/.a)
//#define IMGUI_DISABLE_WIN32_FUNCTIONS                     // [Win32] Won't use and link with any Win32 function (clipboard, ime).
//#define IMGUI_ENABLE_OSX_DEFAULT_CLIPBOARD_FUNCTIONS      // [OSX] Implement default OSX clipboard handler (need to link with '-framework ApplicationServices', this is why this is not the default).
//#define IMGUI_DISABLE_DEFAULT_FORMAT_FUNCTIONS            // Don't implement ImFormatString/ImFormatStringV so you can implement them yourself (e.g. if you don't want to link with vsnprintf)
//#define IMGUI_DISABLE_DEFAULT_MATH_FUNCTIONS              // Don't implement ImFabs/ImSqrt/ImPow/ImFmod/ImCos/ImSin/ImAcos/ImAtan2 so you can implement them yourself.
//#define IMGUI_DISABLE_FILE_FUNCTIONS                      // Don't implement ImFileOpen/ImFileClose/ImFileRead/ImFileWrite and ImFileHandle at all (replace them with dummies)
//#define IMGUI_DISABLE_DEFAULT_FILE_FUNCTIONS              // Don't implement ImFileOpen/ImFileClose/ImFileRead/ImFileWrite and ImFileHandle so you can implement them yourself if you don't want to link with fopen/fclose/fread/fwrite. This will also disable the LogToTTY() function.
//#define IMGUI_DISABLE_DEFAULT_ALLOCATORS                  // Don't implement default allocators calling malloc()/free() to avoid linking with them. You will need to call ImGui::SetAllocatorFunctions().
//#define IMGUI_DISABLE_SSE                                 // Disable use of SSE intrinsics even if available

//---- Include imgui_user.h at the end of imgui.h as a convenience
//#define IMGUI_INCLUDE_IMGUI_USER_H

//---- Pack colors to BGRA8 instead of RGBA8 (to avoid converting from one to another)
//#define IMGUI_USE_BGRA_PACKED_COLOR

//---- Use 32-bit for ImWchar (default is 16-bit) to support unicode planes 1-16. (e.g. point beyond 0xFFFF like emoticons, dingbats, symbols, shapes, ancient languages, etc...)
//#define IMGUI_USE_WCHAR32

//---- Avoid multiple STB libraries implementations, or redefine path/filenames to prioritize another version
// By default the embedded implementations are declared static and not available outside of Dear ImGui sources files.
//#define IMGUI_STB_TRUETYPE_FILENAME   "my_folder/stb_truetype.h"
//#define IMGUI_STB_RECT_PACK_FILENAME  "my_folder/stb_rect_pack.h"
//#define IMGUI_DISABLE_STB_TRUETYPE_IMPLEMENTATION
//#define IMGUI_DISABLE_STB_RECT_PACK_IMPLEMENTATION

//---- Use stb_printf's faster implementation of vsnprintf instead of the one from libc (unless IMGUI_DISABLE_DEFAULT_FORMAT_FUNCTIONS is defined)
// Requires 'stb_sprintf.h' to be available in the include path. Compatibility checks of arguments and formats done by clang and GCC will be disabled in order to support the extra formats provided by STB sprintf.
// #define IMGUI_USE_STB_SPRINTF

//---- Use FreeType to build and rasterize the font atlas (instead of stb_truetype which is embedded by default in Dear ImGui)
// Requires FreeType headers to be available in the include path. Requires program to be compiled with 'misc/freetype/imgui_freetype.cpp' (in this repository) + the FreeType library (not provided).
// On Windows you may use vcpkg with 'vcpkg install freetype --triplet=x64-windows' + 'vcpkg integrate install'.
//#define IMGUI_ENABLE_FREETYPE

//---- Use stb_truetype to build and rasterize the font atlas (default)
// The only purpose of this define is if you want force compilation of the stb_truetype backend ALONG with the FreeType backend.
//#define IMGUI_ENABLE_STB_TRUETYPE

//---- Define constructor and implicit cast operators to convert back<>forth between your math types and ImVec2/ImVec4.
// This will be inlined as part of ImVec2 and ImVec4 class declarations.
/*
#define IM_VEC2_CLASS_EXTRA                                                 \
        ImVec2(const MyVec2& f) { x = f.x; y = f.y; }                       \
        operator MyVec2() const { return MyVec2(x,y); }

#define IM_VEC4_CLASS_EXTRA                                                 \
        ImVec4(const MyVec4& f) { x = f.x; y = f.y; z = f.z; w = f.w; }     \
        operator MyVec4() const { return MyVec4(x,y,z,w); }
*/

//---- Use 32-bit vertex indices (default is 16-bit) is one way to allow large meshes with more than 64K vertices.
// Your renderer backend will need to support it (most example renderer backends support both 16/32-bit indices).
// Another way to allow large meshes while keeping 16-bit indices is to handle ImDrawCmd::VtxOffset in your renderer.
// Read about ImGuiBackendFlags_RendererHasVtxOffset for details.
//#define ImDrawIdx unsigned int

//---- Override ImDrawCallback signature (will need to modify renderer backends accordingly)
//struct ImDrawList;
//struct ImDrawCmd;
//typedef void (*MyImDrawCallback)(const ImDrawList* draw_list, const ImDrawCmd* cmd, void* my_renderer_user_data);
//#define ImDrawCallback MyImDrawCallback

//---- Debug Tools: Macro to break in Debugger
// (use 'Metrics->Tools->Item Picker' to pick widgets with the mouse and break into them for easy debugging.)
//#define IM_DEBUG_BREAK  IM_ASSERT(0)
//#define IM_DEBUG_BREAK  __debugbreak()

//---- Debug Tools: Have the Item Picker break in the ItemAdd() function instead of ItemHoverable(),
// (which comes earlier in the code, will catch a few extra items, allow picking items other than Hovered one.)
// This adds a small runtime cost which is why it is not enabled by default.
//#define IMGUI_DEBUG_TOOL_ITEM_PICKER_EX

//---- Debug Tools: Enable slower asserts
//#define IMGUI_DEBUG_PARANOID

//---- Tip: You can add extra functions within the ImGui:: namespace, here or in your own headers files.
/*
namespace ImGui
{
    void MyFunction(const char* name, const MyMatrix44& v);
}
*/

#ifndef IMGUI_SFML_H
#define IMGUI_SFML_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Joystick.hpp>

#include "imgui-SFML_export.h"

namespace sf {
	class Event;
	class RenderTarget;
	class RenderTexture;
	class RenderWindow;
	class Sprite;
	class Texture;
	class Window;
}

namespace ImGui {
	namespace SFML {
		IMGUI_SFML_API void Init(sf::RenderWindow& window, bool loadDefaultFont = true);
		IMGUI_SFML_API void Init(sf::Window& window, sf::RenderTarget& target, bool loadDefaultFont = true);
		IMGUI_SFML_API void Init(sf::Window& window, const sf::Vector2f& displaySize,
			bool loadDefaultFont = true);

		IMGUI_SFML_API void SetCurrentWindow(const sf::Window& window);
		IMGUI_SFML_API void ProcessEvent(const sf::Event& event); // DEPRECATED: use (window,
																  // event) overload
		IMGUI_SFML_API void ProcessEvent(const sf::Window& window, const sf::Event& event);

		IMGUI_SFML_API void Update(sf::RenderWindow& window, sf::Time dt);
		IMGUI_SFML_API void Update(sf::Window& window, sf::RenderTarget& target, sf::Time dt);
		IMGUI_SFML_API void Update(const sf::Vector2i& mousePos, const sf::Vector2f& displaySize,
			sf::Time dt);

		IMGUI_SFML_API void Render(sf::RenderWindow& target);
		IMGUI_SFML_API void Render(sf::RenderTarget& target);
		IMGUI_SFML_API void Render();

		IMGUI_SFML_API void Shutdown(const sf::Window& window);
		// Shuts down all ImGui contexts
		IMGUI_SFML_API void Shutdown();

		IMGUI_SFML_API void UpdateFontTexture();
		IMGUI_SFML_API sf::Texture& GetFontTexture();

		// joystick functions
		IMGUI_SFML_API void SetActiveJoystickId(unsigned int joystickId);
		IMGUI_SFML_API void SetJoytickDPadThreshold(float threshold);
		IMGUI_SFML_API void SetJoytickLStickThreshold(float threshold);

		IMGUI_SFML_API void SetJoystickMapping(int action, unsigned int joystickButton);
		IMGUI_SFML_API void SetDPadXAxis(sf::Joystick::Axis dPadXAxis, bool inverted = false);
		IMGUI_SFML_API void SetDPadYAxis(sf::Joystick::Axis dPadYAxis, bool inverted = false);
		IMGUI_SFML_API void SetLStickXAxis(sf::Joystick::Axis lStickXAxis, bool inverted = false);
		IMGUI_SFML_API void SetLStickYAxis(sf::Joystick::Axis lStickYAxis, bool inverted = false);
	} // end of namespace SFML

	// custom SFML overloads for ImGui widgets

	// Image overloads for sf::Texture
	IMGUI_SFML_API void Image(const sf::Texture& texture, const sf::Color& tintColor = sf::Color::White,
		const sf::Color& borderColor = sf::Color::Transparent);
	IMGUI_SFML_API void Image(const sf::Texture& texture, const sf::Vector2f& size,
		const sf::Color& tintColor = sf::Color::White,
		const sf::Color& borderColor = sf::Color::Transparent);

	// Image overloads for sf::RenderTexture
	IMGUI_SFML_API void Image(const sf::RenderTexture& texture,
		const sf::Color& tintColor = sf::Color::White,
		const sf::Color& borderColor = sf::Color::Transparent);
	IMGUI_SFML_API void Image(const sf::RenderTexture& texture, const sf::Vector2f& size,
		const sf::Color& tintColor = sf::Color::White,
		const sf::Color& borderColor = sf::Color::Transparent);

	// Image overloads for sf::Sprite
	IMGUI_SFML_API void Image(const sf::Sprite& sprite, const sf::Color& tintColor = sf::Color::White,
		const sf::Color& borderColor = sf::Color::Transparent);
	IMGUI_SFML_API void Image(const sf::Sprite& sprite, const sf::Vector2f& size,
		const sf::Color& tintColor = sf::Color::White,
		const sf::Color& borderColor = sf::Color::Transparent);

	// ImageButton overloads for sf::Texture
	IMGUI_SFML_API bool ImageButton(const sf::Texture& texture, const int framePadding = -1,
		const sf::Color& bgColor = sf::Color::Transparent,
		const sf::Color& tintColor = sf::Color::White);
	IMGUI_SFML_API bool ImageButton(const sf::Texture& texture, const sf::Vector2f& size,
		const int framePadding = -1,
		const sf::Color& bgColor = sf::Color::Transparent,
		const sf::Color& tintColor = sf::Color::White);

	// ImageButton overloads for sf::RenderTexture
	IMGUI_SFML_API bool ImageButton(const sf::RenderTexture& texture, const int framePadding = -1,
		const sf::Color& bgColor = sf::Color::Transparent,
		const sf::Color& tintColor = sf::Color::White);
	IMGUI_SFML_API bool ImageButton(const sf::RenderTexture& texture, const sf::Vector2f& size,
		const int framePadding = -1,
		const sf::Color& bgColor = sf::Color::Transparent,
		const sf::Color& tintColor = sf::Color::White);

	// ImageButton overloads for sf::Sprite
	IMGUI_SFML_API bool ImageButton(const sf::Sprite& sprite, const int framePadding = -1,
		const sf::Color& bgColor = sf::Color::Transparent,
		const sf::Color& tintColor = sf::Color::White);
	IMGUI_SFML_API bool ImageButton(const sf::Sprite& sprite, const sf::Vector2f& size,
		const int framePadding = -1,
		const sf::Color& bgColor = sf::Color::Transparent,
		const sf::Color& tintColor = sf::Color::White);

	// Draw_list overloads. All positions are in relative coordinates (relative to top-left of the
	// current window)
	IMGUI_SFML_API void DrawLine(const sf::Vector2f& a, const sf::Vector2f& b, const sf::Color& col,
		float thickness = 1.0f);
	IMGUI_SFML_API void DrawRect(const sf::FloatRect& rect, const sf::Color& color,
		float rounding = 0.0f, int rounding_corners = 0x0F,
		float thickness = 1.0f);
	IMGUI_SFML_API void DrawRectFilled(const sf::FloatRect& rect, const sf::Color& color,
		float rounding = 0.0f, int rounding_corners = 0x0F);
} // end of namespace ImGui

#endif //# IMGUI_SFML_H

