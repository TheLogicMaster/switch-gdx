#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"

#include <java/nio/ByteBuffer.hpp>
#include <java/nio/CharBuffer.hpp>
#include <java/nio/ShortBuffer.hpp>
#include <java/nio/FloatBuffer.hpp>
#include <java/nio/DoubleBuffer.hpp>
#include <java/nio/IntBuffer.hpp>
#include <java/nio/LongBuffer.hpp>
#include <java/io/IOException.hpp>

#include <com/thelogicmaster/switchgdx/SwitchApplication.hpp>
#include <com/thelogicmaster/switchgdx/SwitchAudio.hpp>
#include <com/thelogicmaster/switchgdx/SwitchMusic.hpp>
#include <com/thelogicmaster/switchgdx/SwitchGraphics.hpp>
#include <com/thelogicmaster/switchgdx/SwitchGL.hpp>
#include <com/thelogicmaster/switchgdx/SwitchInput.hpp>
#include <com/thelogicmaster/switchgdx/SwitchControllerManager.hpp>
#include <com/thelogicmaster/switchgdx/SwitchSound.hpp>
#include <com/thelogicmaster/switchgdx/SwitchNet.hpp>
#include <com/thelogicmaster/switchgdx/SwitchFiles.hpp>
#include <com/thelogicmaster/switchgdx/SwitchHttpResponse.hpp>
#include <com/thelogicmaster/switchgdx/SwitchSocket.hpp>
#include <com/thelogicmaster/switchgdx/SwitchServerSocket.hpp>
#include <com/badlogic/gdx/utils/GdxRuntimeException.hpp>
#include <com/badlogic/gdx/Input_TextInputListener.hpp>
#include <com/badlogic/gdx/utils/BufferUtils.hpp>
#include <com/badlogic/gdx/math/Matrix4.hpp>
#include <com/badlogic/gdx/graphics/g2d/Gdx2DPixmap.hpp>
#include <com/badlogic/gdx/graphics/glutils/ETC1.hpp>

#include <fcntl.h>
#include <csignal>
#include <vector>
#include <string>
#include "switchgdx/gdx_buffer_utils.h"
#include "switchgdx/gdx_matrix4.h"
#include "switchgdx/gdx2d.h"
#include "switchgdx/etc1_utils.h"
#include "switchgdx/tinyfiledialogs.h"
#include <curl/curl.h>
#include <chrono>
#include <SDL.h>
#include "switchgdx/SDL_mixer.h"
#include <SDL_gamecontroller.h>

using namespace com::badlogic::gdx;
using namespace com::thelogicmaster::switchgdx;

#if !defined(__WIN32__) && !defined(__WINRT__)
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <netdb.h>
#else
# include <winsock2.h>
# include <ws2tcpip.h>
typedef int socklen_t;
#endif

#ifdef __WINRT__
#include "winrt/base.h"
namespace winrt::impl {
    template <typename Async>
    auto wait_for(Async const& async, Windows::Foundation::TimeSpan const& timeout);
}
#include <Windows.h>
#include <winrt/base.h>
#include <winrt/Windows.Storage.h>
std::string getLocalPathUWP() {
    auto path = winrt::Windows::Storage::ApplicationData::Current().LocalFolder().Path();
    return std::string(path.begin(), path.end());
}

#define main main
extern "C" extern int main(int argc, char* args[]);
int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
    AllocConsole();
    FILE* fpstdin = stdin, * fpstdout = stdout, * fpstderr = stderr;
    freopen_s(&fpstdin, "CONIN$", "r", stdin);
    freopen_s(&fpstdout, "CONOUT$", "w", stdout);
    freopen_s(&fpstderr, "CONOUT$", "w", stderr);

    SDL_WinRTRunApp(main, nullptr);
}
#endif

#ifdef __SWITCH__
# include <switch.h>
# include <EGL/egl.h>
# include <EGL/eglext.h>
# include <glad/glad.h>
# include <stdio.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <sys/errno.h>
# include <unistd.h>
#else
#include "glad/gles2.h"
#endif

static int touches[16 * 3];

#ifdef __SWITCH__
static EGLDisplay display;
static EGLContext context;
static EGLSurface surface;

static PadState combinedPad;
static PadState pads[8];

static int nxlinkSock = -1;
static bool socketInit;
#else
static SDL_Window *window;
static int buttons;
static float joysticks[4];
#endif

#ifdef __SWITCH__
extern "C" void userAppInit() {
    socketInitializeDefault();
    nxlinkStdio();
}

extern "C" void userAppExit() {
    socketExit();
}
#endif

void onMusicFinished() {
    SwitchAudio::SM_onMusicFinished();
}

void onSoundFinished(int channel) {
    SwitchAudio::SM_onSoundFinished(channel);
}

void SwitchApplication::SM_init() {
    for (int i = 0; i < 16; i++)
        touches[i * 3] = -1;

#if defined(__WIN32__) || defined(__WINRT__)
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data))
        vm::throwNew<java::io::IOException>();
#endif

#ifdef __SWITCH__
    padConfigureInput(8, HidNpadStyleSet_NpadStandard);
    padInitializeAny(&combinedPad);

    padInitializeDefault(&pads[0]);
    for (int i = 1; i < 8; i++)
        padInitialize(&pads[i], static_cast<HidNpadIdType>(HidNpadIdType_No1 + i));

    setInitialize();

    hidInitializeTouchScreen();

    Result result = romfsInit();
    if (R_FAILED(result))
        printf("Failed to initilize RomFS: %08X\n", result);

    // Todo: Error handling/logging
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, NULL, NULL);
    eglBindAPI(EGL_OPENGL_API);
    EGLConfig config;
    EGLint numConfigs;
    static const EGLint framebufferAttributeList[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
        EGL_RED_SIZE,     8,
        EGL_GREEN_SIZE,   8,
        EGL_BLUE_SIZE,    8,
        EGL_ALPHA_SIZE,   8,
        EGL_DEPTH_SIZE,   24,
        EGL_STENCIL_SIZE, 8,
        EGL_NONE
    };
    eglChooseConfig(display, framebufferAttributeList, &config, 1, &numConfigs);
    surface = eglCreateWindowSurface(display, config, nwindowGetDefault(), NULL);
    static const EGLint contextAttributeList[] =
    {
        EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
        EGL_CONTEXT_MAJOR_VERSION_KHR, 2,
        EGL_CONTEXT_MINOR_VERSION_KHR, 0,
        EGL_NONE
    };
    context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttributeList);
    eglMakeCurrent(display, surface, surface, context);
    gladLoadGL();

    SDL_Init(SDL_INIT_AUDIO);
#else
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER);

    window = SDL_CreateWindow("SwitchGDX", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);

#ifdef __WINRT__
    SDL_SetHint(SDL_HINT_OPENGL_ES_DRIVER, "1");
    SDL_SetHint("SDL_WINRT_HANDLE_BACK_BUTTON", "1");
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#endif

    auto context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);
    SDL_GL_SetSwapInterval(1);

    gladLoadGLES2((GLADloadfunc) SDL_GL_GetProcAddress);
#endif

    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
    Mix_AllocateChannels(32);
    Mix_HookMusicFinished(onMusicFinished);
    Mix_ChannelFinished(onSoundFinished);

    curl_global_init(CURL_GLOBAL_ALL);
}

void SwitchApplication::SM_dispose() {
#if defined(__WIN32__) || defined(__WINRT__)
    WSACleanup();
#endif

#ifdef __SWITCH__
    if (display) {
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (context)
            eglDestroyContext(display, context);
        if (surface)
            eglDestroySurface(display, surface);
        eglTerminate(display);
    }

    Mix_Quit();
    SDL_Quit();

    romfsExit();
#endif

    curl_global_cleanup();
}

#ifndef __SWITCH__
static int keyToButton(int key) {
    switch (key) {
        case SDL_SCANCODE_Z:
            return 1 << 3; // Y
        case SDL_SCANCODE_X:
            return 1 << 1; // B
        case SDL_SCANCODE_C:
            return 1 << 0; // A
        case SDL_SCANCODE_V:
            return 1 << 2; // X
        case SDL_SCANCODE_F:
            return 1 << 4; // Left stick
        case SDL_SCANCODE_G:
            return 1 << 5; // Right stick
        case SDL_SCANCODE_Q:
            return 1 << 6; // L
        case SDL_SCANCODE_E:
            return 1 << 7; // R
        case SDL_SCANCODE_R:
            return 1 << 8; // ZL
        case SDL_SCANCODE_T:
            return 1 << 9; // ZR
        case SDL_SCANCODE_N:
            return 1 << 10; // Plus
        case SDL_SCANCODE_M:
            return 1 << 11; // Minus
        case SDL_SCANCODE_UP:
            return 1 << 13; // D-up
        case SDL_SCANCODE_DOWN:
            return 1 << 15; // D-down
        case SDL_SCANCODE_LEFT:
            return 1 << 12; // D-left
        case SDL_SCANCODE_RIGHT:
            return 1 << 14; // D-right
        default:
            return 0;
    }
}

static int keyToAxis(int scancode) {
    switch (scancode) {
        case SDL_SCANCODE_W:
            return 0x4 + 1;
        case SDL_SCANCODE_S:
            return 1;
        case SDL_SCANCODE_A:
            return 0x4 + 0;
        case SDL_SCANCODE_D:
            return 0;
        case SDL_SCANCODE_I:
            return 0x4 + 3;
        case SDL_SCANCODE_K:
            return 3;
        case SDL_SCANCODE_J:
            return 0x4 + 2;
        case SDL_SCANCODE_L:
            return 2;
        default:
            return -1;
    }
}

static int mapButtonSDL(int button) {
    switch (button) {
        case SDL_CONTROLLER_BUTTON_A:
            return 1 << 0;
        case SDL_CONTROLLER_BUTTON_B:
            return 1 << 1;
        case SDL_CONTROLLER_BUTTON_X:
            return 1 << 2;
        case SDL_CONTROLLER_BUTTON_Y:
            return 1 << 3;
        case SDL_CONTROLLER_BUTTON_LEFTSTICK:
            return 1 << 4;
        case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
            return 1 << 5;
        case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
            return 1 << 6;
        case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
            return 1 << 7;
        case SDL_CONTROLLER_BUTTON_START:
            return 1 << 10;
        case SDL_CONTROLLER_BUTTON_BACK:
            return 1 << 11;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            return 1 << 12;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            return 1 << 13;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            return 1 << 14;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            return 1 << 15;
        default:
            return 0;
    }
}
#else
static u64 remapPadButtons(u64 buttons, u32 style) {
    u64 mapped = buttons;

    if (style & HidNpadStyleTag_NpadJoyLeft) {
        mapped &= ~(
            HidNpadButton_Left | HidNpadButton_Right | HidNpadButton_Up | HidNpadButton_Down |
            HidNpadButton_StickLLeft | HidNpadButton_StickLRight | HidNpadButton_StickLUp | HidNpadButton_StickLDown |
            HidNpadButton_LeftSL | HidNpadButton_LeftSR
        );

        if (buttons & HidNpadButton_Left)
            mapped |= HidNpadButton_B;
        if (buttons & HidNpadButton_Down)
            mapped |= HidNpadButton_A;
        if (buttons & HidNpadButton_Up)
            mapped |= HidNpadButton_Y;
        if (buttons & HidNpadButton_Right)
            mapped |= HidNpadButton_X;

        if (buttons & HidNpadButton_StickLLeft)
            mapped |= HidNpadButton_StickLDown;
        if (buttons & HidNpadButton_StickLDown)
            mapped |= HidNpadButton_StickLRight;
        if (buttons & HidNpadButton_StickLRight)
            mapped |= HidNpadButton_StickLUp;
        if (buttons & HidNpadButton_StickLUp)
            mapped |= HidNpadButton_StickLLeft;

        if (buttons & HidNpadButton_LeftSL)
            mapped |= HidNpadButton_L;
        if (buttons & HidNpadButton_LeftSR)
            mapped |= HidNpadButton_R;
    } else if (style & HidNpadStyleTag_NpadJoyRight) {
        mapped &= ~(
            HidNpadButton_A | HidNpadButton_B | HidNpadButton_X | HidNpadButton_Y |
            HidNpadButton_StickLLeft | HidNpadButton_StickLRight | HidNpadButton_StickLUp | HidNpadButton_StickLDown |
            HidNpadButton_LeftSL | HidNpadButton_LeftSR
        );

        if (buttons & HidNpadButton_A)
            mapped |= HidNpadButton_B;
        if (buttons & HidNpadButton_X)
            mapped |= HidNpadButton_A;
        if (buttons & HidNpadButton_B)
            mapped |= HidNpadButton_Y;
        if (buttons & HidNpadButton_Y)
            mapped |= HidNpadButton_X;

        if (buttons & HidNpadButton_StickRLeft)
            mapped |= HidNpadButton_StickRUp;
        if (buttons & HidNpadButton_StickRDown)
            mapped |= HidNpadButton_StickRLeft;
        if (buttons & HidNpadButton_StickRRight)
            mapped |= HidNpadButton_StickRDown;
        if (buttons & HidNpadButton_StickRUp)
            mapped |= HidNpadButton_StickRRight;

        if (buttons & HidNpadButton_RightSL)
            mapped |= HidNpadButton_L;
        if (buttons & HidNpadButton_RightSR)
            mapped |= HidNpadButton_R;
    }

    return mapped;
}

static void remapPadAxes(float *axes, u32 style) {
    if (style & HidNpadStyleTag_NpadJoyLeft) {
        float temp = axes[0];
        axes[0] = -axes[1];
        axes[1] = temp;
    } else if(style & HidNpadStyleTag_NpadJoyRight) {
        axes[0] = axes[3];
        axes[1] = -axes[2];
        axes[2] = 0;
        axes[3] = 0;
    }
}
#endif

jbool SwitchApplication::SM_update_R_boolean() {
#ifdef __SWITCH__
    padUpdate(&combinedPad);
    u64 kDown = padGetButtonsDown(&combinedPad);
    if (kDown & HidNpadButton_Plus)
        return false;

    for (int i = 0; i < 8; i++)
        padUpdate(&pads[i]);

    HidTouchScreenState touchState;
    if (hidGetTouchScreenStates(&touchState, 1)) {
        for (int i = 0; i < 16; i++)
            if (i < touchState.count) {
                touches[i * 3 + 0] = touchState.touches[i].finger_id;
                touches[i * 3 + 1] = touchState.touches[i].x;
                touches[i * 3 + 2] = touchState.touches[i].y;
            } else {
                touches[i * 3 + 0] = -1;
                touches[i * 3 + 1] = 0;
                touches[i * 3 + 2] = 0;
            }
    }

    eglSwapBuffers(display, surface);
    return appletMainLoop();
#else
    SDL_Event event;
    int axis;
    while (SDL_PollEvent(&event))
        switch (event.type) {
            case SDL_QUIT:
                return false;
            case SDL_MOUSEMOTION:
                touches[1] = event.motion.x;
                touches[2] = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                touches[0] = 0;
                touches[1] = event.button.x;
                touches[2] = event.button.y;
                break;
            case SDL_MOUSEBUTTONUP:
                touches[0] = -1;
                break;
            case SDL_KEYDOWN:
                buttons |= keyToButton(event.key.keysym.scancode);
                axis = keyToAxis(event.key.keysym.scancode);
                if (axis > -1 and !event.key.repeat)
                    joysticks[axis & 0x3] += axis & 0x4 ? -1 : 1;
                break;
            case SDL_KEYUP:
                buttons &= ~keyToButton(event.key.keysym.scancode);
                axis = keyToAxis(event.key.keysym.scancode);
                if (axis > -1 and !event.key.repeat)
                    joysticks[axis & 0x3] = 0;
                break;
            case SDL_CONTROLLERBUTTONDOWN:
                buttons |= mapButtonSDL(event.cbutton.button);
                break;
            case SDL_CONTROLLERBUTTONUP:
                buttons &= ~mapButtonSDL(event.cbutton.button);
                break;
            case SDL_CONTROLLERAXISMOTION:
                if (event.caxis.axis >= 0 && event.caxis.axis < 4)
                    joysticks[event.caxis.axis] = (float)event.caxis.value / 32768.f;
                for (int i = 0; i < 2; i++)
                    if (event.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT + i) {
                        if (event.caxis.value > 512)
                            buttons |= 1 << (8 + i);
                        else
                            buttons &= ~(1 << (8 + i));
                    }
                break;
            case SDL_CONTROLLERDEVICEADDED:
                SDL_GameControllerOpen(event.cdevice.which);
                break;
            case SDL_CONTROLLERDEVICEREMOVED:
                SDL_GameControllerClose(SDL_GameControllerFromPlayerIndex(event.cdevice.which));
                break;
        }

    SDL_GL_SwapWindow(window);
    return true;
#endif
}

jstring SwitchFiles::M_getLocalStoragePath_R_java_lang_String() {
#ifdef __WINRT__
    auto path = getLocalPathUWP();
    return vm::createString(path.c_str());
#else
    return vm::createString("data");
#endif
}

jbool SwitchNet::M_openURI_R_boolean(const jstring &urlObj) {
#ifdef __SWITCH__
    WebCommonConfig config;
    WebCommonReply reply;
    return !webPageCreate(&config, vm::getNativeString(urlObj)) and !webConfigSetWhitelist(&config, "^http*") and !webConfigShow(&config, &reply);
#else
    std::string url(vm::getNativeString(urlObj));
# if defined(__WIN32__) || defined(__WINRT__)
    system(("start " + url).c_str());
# elif __APPLE__
    system(("open " + url).c_str());
# else
    system(("xdg-open " + url).c_str());
# endif
    return true;
#endif
}

static size_t curlWriteCallback(void *contents, size_t size, size_t nmemb, void *string) {
    auto *data = (std::string *)string;
    data->append((const char *)contents, size * nmemb);
    return size * nmemb;
}

jstring SwitchNet::SM_sendRequest_Array1_byte_Array1_java_lang_String_R_java_lang_String(const jstring &urlObj, const jarray &contentArray, const jarray &headersArray, const jstring &methodObj, jlong timeout, const shared_ptr<SwitchHttpResponse> &httpResponse) {
    char errorBuffer[CURL_ERROR_SIZE]{};
    CURL *curl = curl_easy_init();
    if (!curl)
        return nullptr;

    std::string responseData;
    curl_easy_setopt(curl, CURLOPT_URL, vm::getNativeString(urlObj));
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "switchgdx-agent/1.0");
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);

    curl_slist *headers = nullptr;
    for (int i = 0; i < headersArray->length; i++)
        headers = curl_slist_append(headers, vm::getNativeString(object_cast<String>(((jobject *)headersArray->data)[i])));
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    auto method = std::string(vm::getNativeString(methodObj));
    if (method == "POST" or method == "PUT" or method == "PATCH") {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, contentArray->length);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, contentArray->data);
    } else if (method == "HEAD")
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    else if (method == "GET")
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);

    curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, timeout);

    long status;
    CURLcode res = curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK)
        return vm::createString(strlen(errorBuffer) ? errorBuffer : curl_easy_strerror(res));

    httpResponse->F_status = (jint)status;

    auto response = vm::newArray(vm::classByte, (int)responseData.length());
    memcpy(response->data, responseData.c_str(), responseData.length());
    httpResponse->F_result = response;

    return nullptr;
}

void throwNativeSocketException(bool inErrno = false) {
    auto exception = make_shared<java::io::IOException>();
    jstring error;
    if (errno == ETIMEDOUT)
        error = vm::createString("Timed out");
    else {
#if defined(__WIN32__)
        if (!inErrno)
            errno = WSAGetLastError();
        char buffer[256];
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK, nullptr, errno, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buffer, sizeof(buffer), nullptr);
        error = vm::createString(buffer);
#elif defined(__WINRT__)
        error = vm::createString("Socket error");
#else
        error = vm::createString(strerror(errno));
#endif
    }
    exception->init(error);
    vm::throwEx(exception);
}

void SwitchSocket::M_dispose() {
    if (F_fd) {
#if defined(__WIN32__) || defined(__WINRT__)
        shutdown(F_fd, SD_SEND);
        closesocket(F_fd);
#else
        close(F_fd);
#endif
        F_fd = 0;
    }
}

void setSocketTimeout(int fd, int timeout) {
#if defined(__WIN32__) || defined(__WINRT__)
    DWORD timeoutVal = timeout;
    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeoutVal, sizeof timeoutVal);
    setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeoutVal, sizeof timeoutVal);
#else
    timeout /= 2; // Timeout doesn't seem to be reliable in blocking mode
    timeval timeoutVal{};
    timeoutVal.tv_usec = 1000 * (timeout % 1000);
    timeoutVal.tv_sec = timeout / 1000;
    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeoutVal, sizeof timeoutVal);
    setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &timeoutVal, sizeof timeoutVal);
#endif
}

jint SwitchSocket::SM_create_R_int(const jstring &hostObj, jint port, jint connectTimeout, jint timeout) {
//    std::string host(hostObj ? vm::getNativeString(hostObj) : "");
//    const char *hostname = nullptr;
//    if (hostObj)
//        hostname = host.c_str();
//
//    int fd = -1;
//
//    addrinfo hints{};
//    addrinfo *addrInfo = nullptr, *addrInfoIter = nullptr;
//    in6_addr serverAddr{};
//    hints.ai_flags = AI_NUMERICSERV;
//    hints.ai_family = AF_UNSPEC;
//    hints.ai_socktype = SOCK_STREAM;
//
//    auto portString = std::to_string(port);
//
//    if (hostname) {
//        if (inet_pton(AF_INET, hostname, &serverAddr) == 1) {
//            hints.ai_family = AF_INET;
//            hints.ai_flags |= AI_NUMERICHOST;
//        } else if (inet_pton(AF_INET6, hostname, &serverAddr) == 1) {
//            hints.ai_family = AF_INET6;
//            hints.ai_flags |= AI_NUMERICHOST;
//        }
//    }
//
//    if (getaddrinfo(hostname, portString.c_str(), &hints, &addrInfo))
//        goto error;
//
//    for (addrInfoIter = addrInfo; addrInfoIter; addrInfoIter = addrInfoIter->ai_next) {
//        fd = socket(addrInfoIter->ai_family, addrInfoIter->ai_socktype, addrInfoIter->ai_protocol);
//        if (fd < 0)
//            goto error;
//
//#if defined(__WIN32__) || defined(__WINRT__)
//        u_long nonblocking = 1;
//        ioctlsocket(fd, FIONBIO, &nonblocking);
//#else
//        if (fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK) < 0)
//            goto error;
//#endif
//
//        if (connect(fd, addrInfoIter->ai_addr, (int)addrInfoIter->ai_addrlen)) {
//#if defined(__WIN32__) || defined(__WINRT__)
//            if (WSAGetLastError() == WSAEWOULDBLOCK) {
//#else
//            if (errno == EWOULDBLOCK or errno == EINPROGRESS) {
//#endif
//                auto start = std::chrono::steady_clock::now();
//                int remaining;
//                while (true) {
//                    remaining = connectTimeout - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
//                    if (remaining <= 0) {
//                        fd = -1;
//                        errno = ETIMEDOUT;
//                        break;
//                    }
//                    fd_set wr{}, ex{};
//                    timeval t{};
//                    FD_SET(fd, &wr);
//                    FD_SET(fd, &ex);
//                    t.tv_sec = remaining / 1000;
//                    t.tv_usec = (remaining % 1000) * 1000;
//                    int rc = select(fd + 1, nullptr, &wr, &ex, &t);
//                    if (rc < 0 && errno == EINTR)
//                        continue;
//                    if (rc == 0 or FD_ISSET(fd, &ex))
//                        fd = -1;
//                    if (rc == 0)
//                        errno = ETIMEDOUT;
//                    break;
//                }
//                if (fd >= 0)
//                    break;
//            } else {
//#if defined(__WIN32__) || defined(__WINRT__)
//                shutdown(fd, SD_SEND);
//                closesocket(fd);
//#else
//                close(fd);
//#endif
//                fd = -1;
//            }
//        } else
//            break;
//    }
//
//    if (fd < 0)
//        goto error;
//
//#if defined(__WIN32__) || defined(__WINRT__)
//    {
//        u_long nonblocking = 0;
//        ioctlsocket(fd, FIONBIO, &nonblocking);
//    }
//#else
//    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) & ~O_NONBLOCK);
//#endif
//
//    setSocketTimeout(fd, timeout);
//
//    freeaddrinfo(addrInfo);
//    return fd;
//
//    error:
//#if defined(__WIN32__) || defined(__WINRT__)
//    errno = WSAGetLastError();
//#endif
//
//    if (fd > 0) {
//#if defined(__WIN32__) || defined(__WINRT__)
//        shutdown(fd, SD_SEND);
//        closesocket(fd);
//#else
//        close(fd);
//#endif
//    }
//    if (addrInfo)
//        freeaddrinfo(addrInfo);
//    throwNativeSocketException(true);
    return 0;
}

jint SwitchSocket::M_read_R_int() {
//    signed char buffer;
//    if (!F_fd)
//        vm::throwNew<java::io::IOException>();
//    if (recv(F_fd, (char *)&buffer, 1, 0) != 1) {
//#if defined(__WIN32__) || defined(__WINRT__)
//        errno = WSAGetLastError();
//#endif
//        throwNativeSocketException(true);
//    }
//    return buffer;
    return 0;
}

void SwitchSocket::M_write(jint value) {
//    auto buffer = (signed char) value;
//    if (!F_fd)
//        vm::throwNew<java::io::IOException>();
//    if (send(F_fd, (char *)&buffer, 1, 0) != 1) {
//#if defined(__WIN32__) || defined(__WINRT__)
//        errno = WSAGetLastError();
//#endif
//        throwNativeSocketException();
//    }
}

jstring SwitchSocket::M_getRemoteAddress_R_java_lang_String() {
//    if (!F_fd)
//        vm::throwNew<java::io::IOException>();
//    sockaddr_storage address{};
//    socklen_t addrLen = sizeof(address);
//    char addrStr[INET6_ADDRSTRLEN];
//    if (getpeername(F_fd, (sockaddr *) &address, &addrLen))
//        throwNativeSocketException();
//    auto data = address.ss_family == AF_INET ? (void *)&((sockaddr_in *)&address)->sin_addr : (void *)&((sockaddr_in6 *)&address)->sin6_addr;
//    if (!inet_ntop(address.ss_family, data, addrStr, sizeof(addrStr)))
//        throwNativeSocketException();
//    return vm::createString(addrStr);
    return nullptr;
}

void SwitchServerSocket::M_dispose() {
//    if (F_fd) {
//#if defined(__WIN32__) || defined(__WINRT__)
//        shutdown(F_fd, SD_SEND);
//        closesocket(F_fd);
//#else
//        close(F_fd);
//#endif
//        F_fd = 0;
//    }
}

jint SwitchServerSocket::SM_create_R_int(jint port, jbool reuseAddress) {
//    sockaddr_in address{};
//    address.sin_family = AF_INET;
//    address.sin_port = htons(port);
//    address.sin_addr.s_addr = INADDR_ANY;
//    int fd;
//
//    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
//        goto error;
//
//    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *) &reuseAddress, sizeof(int)) < 0)
//        goto error;
//
//#if defined(__WIN32__) || defined(__WINRT__)
//    {
//        u_long nonblocking = 1;
//        ioctlsocket(fd, FIONBIO, &nonblocking);
//    }
//#else
//    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
//#endif
//
//    if (bind(fd, (sockaddr *) &address, sizeof(address)) < 0)
//        goto error;
//
//    if (listen(fd, 10) < 0)
//        goto error;
//
//    return fd;
//
//    error:
//#if defined(__WIN32__) || defined(__WINRT__)
//    errno = WSAGetLastError();
//#endif
//
//    if (fd > 0) {
//#if defined(__WIN32__) || defined(__WINRT__)
//        shutdown(fd, SD_SEND);
//        closesocket(fd);
//#else
//        close(fd);
//#endif
//    }
//    throwNativeSocketException(true);
    return 0;
}

jint SwitchServerSocket::M_accept_R_int(jint timeout) {
//    if (!F_fd)
//        vm::throwNew<java::io::IOException>();
//
//    sockaddr_in6 address{};
//    socklen_t addrLen = sizeof(address);
//    if (getsockname(F_fd, (sockaddr *) &address, &addrLen))
//        throwNativeSocketException();
//
//    int fd = -1;
//    auto start = std::chrono::steady_clock::now();
//    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() < F_acceptTimeout) {
//        fd = accept(F_fd, (sockaddr *) &address, &addrLen);
//        if (fd >= 0)
//            break;
//#if defined(__WIN32__) || defined(__WINRT__)
//        if (WSAGetLastError() != WSAEWOULDBLOCK)
//#else
//        if (errno != EAGAIN)
//#endif
//            throwNativeSocketException();
//    }
//
//    if (fd < 0) {
//        auto error = java::io::IOException::newObject();
//        vm::checkedCast<java::io::IOException>(error)->init_java_lang_String(vm::createString("Accept timed out"));
//        throw error;
//    }
//
//#if defined(__WIN32__) || defined(__WINRT__)
//    {
//        u_long nonblocking = 0;
//        ioctlsocket(fd, FIONBIO, &nonblocking);
//    }
//#else
//    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) & ~O_NONBLOCK);
//#endif
//    setSocketTimeout(fd, timeout);
//    return fd;
    return 0;
}

void SwitchMusic::M_create(const jstring &file) {
    auto music = Mix_LoadMUS(vm::getNativeString(file));
    if (!music)
        vm::throwExceptionCause<com::badlogic::gdx::utils::GdxRuntimeException>(Mix_GetError());
    F_handle = (jlong)music;
}

void SwitchMusic::M_start(jbool looping) {
    Mix_PlayMusic((Mix_Music*)F_handle, looping ? -1 : 0);
}

void SwitchMusic::SM_resume() {
    Mix_ResumeMusic();
}

void SwitchMusic::SM_pause0() {
    Mix_PauseMusic();
}

void SwitchMusic::SM_stop0() {
    Mix_HaltMusic();
}

void SwitchMusic::SM_setVolume0(jfloat volume) {
    Mix_VolumeMusic((int)(volume * MIX_MAX_VOLUME));
}

void SwitchMusic::SM_setPosition0(jfloat position) {
    Mix_RewindMusic();
    Mix_SetMusicPosition(position);
}

void SwitchMusic::M_dispose0() {
    auto& handle = F_handle;
    if (!handle)
        return;
    Mix_FreeMusic((Mix_Music *)handle);
    handle = 0;
}

void SwitchSound::M_create(const jstring &file) {
    auto sound = Mix_LoadWAV(vm::getNativeString(file));
    if (!sound)
        vm::throwExceptionCause<com::badlogic::gdx::utils::GdxRuntimeException>(Mix_GetError());
    F_handle = (jlong)sound;
}

void SwitchSound::M_dispose0() {
    auto &handle = F_handle;
    if (!handle)
        return;
    Mix_FreeChunk((Mix_Chunk *)handle);
    handle = 0;
}

jint SwitchSound::M_play0_R_int(jbool looping) {
    return Mix_PlayChannel(-1, (Mix_Chunk*)F_handle, looping ? -1 : 0);
}

void SwitchSound::M_setLooping0(jint channel, jbool looping) {
    Mix_PlayChannel(channel, (Mix_Chunk*)F_handle, looping ? -1 : 0);
}

void SwitchSound::SM_stop0(jint channel) {
    Mix_HaltChannel(channel);
}

void SwitchSound::SM_pause0(jint channel) {
    Mix_Pause(channel);
}

void SwitchSound::SM_resume0(jint channel) {
    Mix_Resume(channel);
}

void SwitchSound::SM_setPitch0(jint channel, jfloat pitch) {
    // Todo: Custom pitch changing effect based on: https://gist.github.com/hydren/ea794e65e95c7713c00c88f74b71f8b1
}

void SwitchSound::SM_setVolume0(jint channel, jfloat volume) {
    Mix_Volume(channel, (int)(volume * MIX_MAX_VOLUME));
}

void SwitchSound::SM_setPan0(jint channel, jfloat pan) {
    uint8_t left, right;
    if (pan <= 0) {
        left = 255;
        right = (uint8_t)((1 + pan) * 255);
    } else {
        left = (uint8_t)((1 - pan) * 255);
        right = 255;
    }
    Mix_SetPanning(channel, left, right);
}

// Todo: Move to Utils.hpp
template <typename T>
static void *getBufferAddress(const shared_ptr<T> &buffer) {
    if (!buffer)
        return nullptr;
    int typeSize = 1;
    if (vm::instanceof<java::nio::ByteBuffer>(buffer))
        typeSize = sizeof(jbyte);
    else if (vm::instanceof<java::nio::FloatBuffer>(buffer))
        typeSize = sizeof(jfloat);
    else if (vm::instanceof<java::nio::IntBuffer>(buffer))
        typeSize = sizeof(jint);
    else if (vm::instanceof<java::nio::ShortBuffer>(buffer))
        typeSize = sizeof(jshort);
    else if (vm::instanceof<java::nio::CharBuffer>(buffer))
        typeSize = sizeof(jchar);
    else if (vm::instanceof<java::nio::LongBuffer>(buffer))
        typeSize = sizeof(jlong);
    else if (vm::instanceof<java::nio::DoubleBuffer>(buffer))
        typeSize = sizeof(jdouble);
    return (char*)buffer->F_address + typeSize * buffer->F_position;
}

template<>
void *getBufferAddress(const shared_ptr<ByteBuffer> &buffer) {
    return (char*)buffer->F_address + sizeof(jbyte) * buffer->F_position;
}

template<>
void *getBufferAddress(const shared_ptr<ShortBuffer> &buffer) {
    return (char*)buffer->F_address + sizeof(jshort) * buffer->F_position;
}

template<>
void *getBufferAddress(const shared_ptr<CharBuffer> &buffer) {
    return (char*)buffer->F_address + sizeof(jchar) * buffer->F_position;
}

template<>
void *getBufferAddress(const shared_ptr<IntBuffer> &buffer) {
    return (char*)buffer->F_address + sizeof(jint) * buffer->F_position;
}

template<>
void *getBufferAddress(const shared_ptr<LongBuffer> &buffer) {
    return (char*)buffer->F_address + sizeof(jlong) * buffer->F_position;
}

template<>
void *getBufferAddress(const shared_ptr<FloatBuffer> &buffer) {
    return (char*)buffer->F_address + sizeof(jfloat) * buffer->F_position;
}

template<>
void *getBufferAddress(const shared_ptr<DoubleBuffer> &buffer) {
    return (char*)buffer->F_address + sizeof(jdouble) * buffer->F_position;
}

void com::badlogic::gdx::utils::BufferUtils::SM_freeMemory(const shared_ptr<ByteBuffer> &buffer) {
    auto memory = (char *) buffer->F_address;
    if (memory) {
        delete[] memory;
        buffer->F_address = 0;
    }
}

shared_ptr<ByteBuffer> com::badlogic::gdx::utils::BufferUtils::SM_newDisposableByteBuffer_R_java_nio_ByteBuffer(jint param1) {
    return java::nio::ByteBuffer::SM_allocateDirect_R_java_nio_ByteBuffer(param1);
}

jlong com::badlogic::gdx::utils::BufferUtils::SM_getBufferAddress_R_long(const shared_ptr<Buffer> &buffer) {
    return buffer->F_address;
}

void com::badlogic::gdx::utils::BufferUtils::SM_clear(const shared_ptr<ByteBuffer> &buffer, jint numBytes) {
    memset((void *) buffer->F_address, 0, numBytes);
}

void com::badlogic::gdx::utils::BufferUtils::SM_copyJni_Array1_float(const jarray &src, const shared_ptr<Buffer> &dst, jint numFloats, jint offset) {
    memcpy((float *) dst->F_address, (float *) src->data + offset, numFloats << 2);
}

void com::badlogic::gdx::utils::BufferUtils::SM_copyJni_Array1_byte(const jarray &src, jint srcOffset, const shared_ptr<Buffer> &dst, jint dstOffset, jint numBytes) {
    memcpy((char *) dst->F_address + dstOffset, (jbyte *) src->data + srcOffset, numBytes);
}

void com::badlogic::gdx::utils::BufferUtils::SM_copyJni_Array1_char(const jarray &src, jint srcOffset, const shared_ptr<Buffer> &dst, jint dstOffset, jint numBytes) {
    memcpy((char *) dst->F_address + dstOffset, (jchar *) src->data + srcOffset, numBytes);
}

void com::badlogic::gdx::utils::BufferUtils::SM_copyJni_Array1_short(const jarray &src, jint srcOffset, const shared_ptr<Buffer> &dst, jint dstOffset, jint numBytes) {
    memcpy((char *) dst->F_address + dstOffset, (jshort *) src->data + srcOffset, numBytes);
}

void com::badlogic::gdx::utils::BufferUtils::SM_copyJni_Array1_int(const jarray &src, jint srcOffset, const shared_ptr<Buffer> &dst, jint dstOffset, jint numBytes) {
    memcpy((char *) dst->F_address + dstOffset, (jint *) src->data + srcOffset, numBytes);
}

void com::badlogic::gdx::utils::BufferUtils::SM_copyJni_Array1_long(const jarray &src, jint srcOffset, const shared_ptr<Buffer> &dst, jint dstOffset, jint numBytes) {
    memcpy((char *) dst->F_address + dstOffset, (jlong *) src->data + srcOffset, numBytes);
}

void com::badlogic::gdx::utils::BufferUtils::SM_copyJni_Array1_float(const jarray &src, jint srcOffset, const shared_ptr<Buffer> &dst, jint dstOffset, jint numBytes) {
    memcpy((char *) dst->F_address + dstOffset, (jfloat *) src->data + srcOffset, numBytes);
}

void com::badlogic::gdx::utils::BufferUtils::SM_copyJni_Array1_double(const jarray &src, jint srcOffset, const shared_ptr<Buffer> &dst, jint dstOffset, jint numBytes) {
    memcpy((char *) dst->F_address + dstOffset, (jdouble *) src->data + srcOffset, numBytes);
}

void com::badlogic::gdx::utils::BufferUtils::SM_copyJni(const shared_ptr<Buffer> &src, jint srcOffset, const shared_ptr<Buffer> &dst, jint dstOffset, jint numBytes) {
    memcpy((char *) dst->F_address + dstOffset, (char *) src->F_address + srcOffset, numBytes);
}

void com::badlogic::gdx::utils::BufferUtils::SM_transformV4M4Jni_Array1_float(const shared_ptr<Buffer> &data, jint strideInBytes, jint count, const jarray &matrix, jint offsetInBytes) {
    transform<4, 4>((float *) data->F_address, strideInBytes / 4, count, (float *) matrix->data, offsetInBytes / 4);
}

void com::badlogic::gdx::utils::BufferUtils::SM_transformV4M4Jni_Array1_float_Array1_float(const jarray &data, jint strideInBytes, jint count, const jarray &matrix, jint offsetInBytes) {
    transform<4, 4>((float *) data->data, strideInBytes / 4, count, (float *) matrix->data, offsetInBytes / 4);
}

void com::badlogic::gdx::utils::BufferUtils::SM_transformV3M4Jni_Array1_float(const shared_ptr<Buffer> &data, jint strideInBytes, jint count, const jarray &matrix, jint offsetInBytes) {
    transform<3, 4>((float *) data->F_address, strideInBytes / 4, count, (float *) matrix->data, offsetInBytes / 4);
}

void com::badlogic::gdx::utils::BufferUtils::SM_transformV3M4Jni_Array1_float_Array1_float(const jarray &data, jint strideInBytes, jint count, const jarray &matrix, jint offsetInBytes) {
    transform<3, 4>((float *) data->data, strideInBytes / 4, count, (float *) matrix->data, offsetInBytes / 4);
}

void com::badlogic::gdx::utils::BufferUtils::SM_transformV2M4Jni_Array1_float(const shared_ptr<Buffer> &data, jint strideInBytes, jint count, const jarray &matrix, jint offsetInBytes) {
    transform<2, 4>((float *) data->F_address, strideInBytes / 4, count, (float *) matrix->data, offsetInBytes / 4);
}

void com::badlogic::gdx::utils::BufferUtils::SM_transformV2M4Jni_Array1_float_Array1_float(const jarray &data, jint strideInBytes, jint count, const jarray &matrix, jint offsetInBytes) {
    transform<2, 4>((float *) data->data, strideInBytes / 4, count, (float *) matrix->data, offsetInBytes / 4);
}

void com::badlogic::gdx::utils::BufferUtils::SM_transformV3M3Jni_Array1_float(const shared_ptr<Buffer> &data, jint strideInBytes, jint count, const jarray &matrix, jint offsetInBytes) {
    transform<3, 3>((float *) data->F_address, strideInBytes / 4, count, (float *) matrix->data, offsetInBytes / 4);
}

void com::badlogic::gdx::utils::BufferUtils::SM_transformV3M3Jni_Array1_float_Array1_float(const jarray &data, jint strideInBytes, jint count, const jarray &matrix, jint offsetInBytes) {
    transform<3, 3>((float *) data->data, strideInBytes / 4, count, (float *) matrix->data, offsetInBytes / 4);
}

void com::badlogic::gdx::utils::BufferUtils::SM_transformV2M3Jni_Array1_float(const shared_ptr<Buffer> &data, jint strideInBytes, jint count, const jarray &matrix, jint offsetInBytes) {
    transform<2, 3>((float *) data->F_address, strideInBytes / 4, count, (float *) matrix->data, offsetInBytes / 4);
}

void com::badlogic::gdx::utils::BufferUtils::SM_transformV2M3Jni_Array1_float_Array1_float(const jarray &data, jint strideInBytes, jint count, const jarray &matrix, jint offsetInBytes) {
    transform<2, 3>((float *) data->data, strideInBytes / 4, count, (float *) matrix->data, offsetInBytes / 4);
}

jlong com::badlogic::gdx::utils::BufferUtils::SM_find_R_long(const shared_ptr<Buffer> &vertex, jint vertexOffsetInBytes, jint strideInBytes, const shared_ptr<Buffer> &vertices, jint verticesOffsetInBytes, jint numVertices) {
    return find(&((float *) vertex->F_address)[vertexOffsetInBytes / 4], strideInBytes / 4, &((float *) vertices->F_address)[verticesOffsetInBytes / 4], numVertices);
}

jlong com::badlogic::gdx::utils::BufferUtils::SM_find_Array1_float_R_long(const jarray &vertex, jint vertexOffsetInBytes, jint strideInBytes, const shared_ptr<Buffer> &vertices, jint verticesOffsetInBytes, jint numVertices) {
    return find(&((float *) vertex->data)[vertexOffsetInBytes / 4], strideInBytes / 4, &((float *) vertices->F_address)[verticesOffsetInBytes / 4], numVertices);
}

jlong com::badlogic::gdx::utils::BufferUtils::SM_find_Array1_float_R_long(const shared_ptr<Buffer> &vertex, jint vertexOffsetInBytes, jint strideInBytes, const jarray &vertices, jint verticesOffsetInBytes, jint numVertices) {
    return find(&((float *) vertex->F_address)[vertexOffsetInBytes / 4], strideInBytes / 4, &((float *) vertices->data)[verticesOffsetInBytes / 4], numVertices);
}

jlong com::badlogic::gdx::utils::BufferUtils::SM_find_Array1_float_Array1_float_R_long(const jarray &vertex, jint vertexOffsetInBytes, jint strideInBytes, const jarray &vertices, jint verticesOffsetInBytes, jint numVertices) {
    return find(&((float *) vertex->data)[vertexOffsetInBytes / 4], strideInBytes / 4, &((float *) vertices->data)[verticesOffsetInBytes / 4], numVertices);
}

jlong com::badlogic::gdx::utils::BufferUtils::SM_find_R_long(const shared_ptr<Buffer> &vertex, jint vertexOffsetInBytes, jint strideInBytes, const shared_ptr<Buffer> &vertices, jint verticesOffsetInBytes, jint numVertices, jfloat epsilon) {
    return find(&((float *) vertex->F_address)[vertexOffsetInBytes / 4], strideInBytes / 4, &((float *) vertices->F_address)[verticesOffsetInBytes / 4], numVertices, epsilon);
}

jlong com::badlogic::gdx::utils::BufferUtils::SM_find_Array1_float_R_long(const jarray &vertex, jint vertexOffsetInBytes, jint strideInBytes, const shared_ptr<Buffer> &vertices, jint verticesOffsetInBytes, jint numVertices, jfloat epsilon) {
    return find(&((float *) vertex->data)[vertexOffsetInBytes / 4], strideInBytes / 4, &((float *) vertices->F_address)[verticesOffsetInBytes / 4], numVertices, epsilon);
}

jlong com::badlogic::gdx::utils::BufferUtils::SM_find_Array1_float_R_long(const shared_ptr<Buffer> &vertex, jint vertexOffsetInBytes, jint strideInBytes, const jarray &vertices, jint verticesOffsetInBytes, jint numVertices, jfloat epsilon) {
    return find(&((float *) vertex->F_address)[vertexOffsetInBytes / 4], strideInBytes / 4, &((float *) vertices->data)[verticesOffsetInBytes / 4], numVertices, epsilon);
}

jlong com::badlogic::gdx::utils::BufferUtils::SM_find_Array1_float_Array1_float_R_long(const jarray &vertex, jint vertexOffsetInBytes, jint strideInBytes, const jarray &vertices, jint verticesOffsetInBytes, jint numVertices, jfloat epsilon) {
    return find(&((float *) vertex->data)[vertexOffsetInBytes / 4], strideInBytes / 4, &((float *) vertices->data)[verticesOffsetInBytes / 4], numVertices, epsilon);
}

void com::badlogic::gdx::math::Matrix4::SM_mulVec_Array1_float_Array1_float(const jarray &mat, const jarray &vecs, jint offset, jint numVecs, jint stride) {
    auto vecPtr = (float *) vecs->data + offset;
    for (int i = 0; i < numVecs; i++) {
        matrix4_mulVec((float *) mat->data, vecPtr);
        vecPtr += stride;
    }
}

void com::badlogic::gdx::math::Matrix4::SM_prj_Array1_float_Array1_float(const jarray &mat, const jarray &vecs, jint offset, jint numVecs, jint stride) {
    auto vecPtr = (float *) vecs->data + offset;
    for (int i = 0; i < numVecs; i++) {
        matrix4_proj((float *) mat->data, vecPtr);
        vecPtr += stride;
    }
}

void com::badlogic::gdx::math::Matrix4::SM_rot_Array1_float_Array1_float(const jarray &mat, const jarray &vecs, jint offset, jint numVecs, jint stride) {
    auto vecPtr = (float *) vecs->data + offset;
    for (int i = 0; i < numVecs; i++) {
        matrix4_rot((float *) mat->data, vecPtr);
        vecPtr += stride;
    }
}

shared_ptr<ByteBuffer> com::badlogic::gdx::graphics::g2d::Gdx2DPixmap::SM_load_Array1_long_Array1_byte_R_java_nio_ByteBuffer(const jarray &nativeData, const jarray &buffer, jint offset, jint len) {
    auto pixmap = gdx2d_load((unsigned char *) buffer->data + offset, len);
    if (!pixmap)
        return nullptr;
    auto pixelBuffer = make_shared<java::nio::ByteBuffer>();
    pixelBuffer->init((jlong) pixmap->pixels, (jint) (pixmap->width * pixmap->height * gdx2d_bytes_per_pixel(pixmap->format)), false);
    auto nativeDataPtr = (jlong *) nativeData->data;
    nativeDataPtr[0] = (jlong) pixmap;
    nativeDataPtr[1] = pixmap->width;
    nativeDataPtr[2] = pixmap->height;
    nativeDataPtr[3] = pixmap->format;
    return pixelBuffer;
}

shared_ptr<ByteBuffer> com::badlogic::gdx::graphics::g2d::Gdx2DPixmap::SM_loadByteBuffer_Array1_long_R_java_nio_ByteBuffer(const jarray &nativeData, const shared_ptr<ByteBuffer> &buffer, jint offset, jint len) {
    auto pixmap = gdx2d_load((unsigned char *) buffer->F_address + offset, len);
    if (!pixmap)
        return nullptr;
    auto pixelBuffer = make_shared<java::nio::ByteBuffer>();
    pixelBuffer->init((jlong) pixmap->pixels, (jint) (pixmap->width * pixmap->height * gdx2d_bytes_per_pixel(pixmap->format)), false);
    auto nativeDataPtr = (jlong *) nativeData->data;
    nativeDataPtr[0] = (jlong) pixmap;
    nativeDataPtr[1] = pixmap->width;
    nativeDataPtr[2] = pixmap->height;
    nativeDataPtr[3] = pixmap->format;
    return pixelBuffer;
}

shared_ptr<ByteBuffer> com::badlogic::gdx::graphics::g2d::Gdx2DPixmap::SM_newPixmap_Array1_long_R_java_nio_ByteBuffer(const jarray &nativeData, jint width, jint height, jint format) {
    auto pixmap = gdx2d_new(width, height, format);
    if (!pixmap)
        return nullptr;
    auto pixelBuffer = make_shared<java::nio::ByteBuffer>();
    pixelBuffer->init((jlong) pixmap->pixels, (jint) (pixmap->width * pixmap->height * gdx2d_bytes_per_pixel(pixmap->format)), false);
    auto nativeDataPtr = (jlong *) nativeData->data;
    nativeDataPtr[0] = (jlong) pixmap;
    nativeDataPtr[1] = pixmap->width;
    nativeDataPtr[2] = pixmap->height;
    nativeDataPtr[3] = pixmap->format;
    return pixelBuffer;
}

void com::badlogic::gdx::graphics::g2d::Gdx2DPixmap::SM_free(jlong pixmap) {
    gdx2d_free((gdx2d_pixmap *) pixmap);
}

void com::badlogic::gdx::graphics::g2d::Gdx2DPixmap::SM_clear(jlong pixmap, jint color) {
    gdx2d_clear((gdx2d_pixmap *) pixmap, color);
}

void com::badlogic::gdx::graphics::g2d::Gdx2DPixmap::SM_setPixel(jlong pixmap, jint x, jint y, jint color) {
    gdx2d_set_pixel((gdx2d_pixmap *) pixmap, x, y, color);
}

jint com::badlogic::gdx::graphics::g2d::Gdx2DPixmap::SM_getPixel_R_int(jlong pixmap, jint x, jint y) {
    return (jint) gdx2d_get_pixel((gdx2d_pixmap *) pixmap, x, y);
}

void com::badlogic::gdx::graphics::g2d::Gdx2DPixmap::SM_drawLine(jlong pixmap, jint x, jint y, jint x2, jint y2, jint color) {
    gdx2d_draw_line((gdx2d_pixmap *) pixmap, x, y, x2, y2, color);
}

void com::badlogic::gdx::graphics::g2d::Gdx2DPixmap::SM_drawRect(jlong pixmap, jint x, jint y, jint width, jint height, jint color) {
    gdx2d_draw_rect((gdx2d_pixmap *) pixmap, x, y, width, height, color);
}

void com::badlogic::gdx::graphics::g2d::Gdx2DPixmap::SM_drawCircle(jlong pixmap, jint x, jint y, jint radius, jint color) {
    gdx2d_draw_circle((gdx2d_pixmap *) pixmap, x, y, radius, color);
}

void com::badlogic::gdx::graphics::g2d::Gdx2DPixmap::SM_fillRect(jlong pixmap, jint x, jint y, jint width, jint height, jint color) {
    gdx2d_fill_rect((gdx2d_pixmap *) pixmap, x, y, width, height, color);
}

void com::badlogic::gdx::graphics::g2d::Gdx2DPixmap::SM_fillCircle(jlong pixmap, jint x, jint y, jint radius, jint color) {
    gdx2d_fill_circle((gdx2d_pixmap *) pixmap, x, y, radius, color);
}

void com::badlogic::gdx::graphics::g2d::Gdx2DPixmap::SM_fillTriangle(jlong pixmap, jint x1, jint y1, jint x2, jint y2, jint x3, jint y3, jint color) {
    gdx2d_fill_triangle((gdx2d_pixmap *) pixmap, x1, y1, x2, y2, x3, y3, color);
}

void com::badlogic::gdx::graphics::g2d::Gdx2DPixmap::SM_drawPixmap(jlong src, jlong dst, jint srcX, jint srcY, jint srcWidth, jint srcHeight, jint dstX, jint dstY, jint dstWidth, jint dstHeight) {
    gdx2d_draw_pixmap((gdx2d_pixmap *) src, (gdx2d_pixmap *) dst, srcX, srcY, srcWidth, srcHeight, dstX, dstY, dstWidth, dstHeight);
}

void com::badlogic::gdx::graphics::g2d::Gdx2DPixmap::SM_setBlend(jlong src, jint blend) {
    gdx2d_set_blend((gdx2d_pixmap *) src, blend);
}

void com::badlogic::gdx::graphics::g2d::Gdx2DPixmap::SM_setScale(jlong src, jint scale) {
    gdx2d_set_scale((gdx2d_pixmap *) src, scale);
}

jstring com::badlogic::gdx::graphics::g2d::Gdx2DPixmap::SM_getFailureReason_R_java_lang_String() {
    return vm::createString(gdx2d_get_failure_reason());
}

jint com::badlogic::gdx::graphics::glutils::ETC1::SM_getCompressedDataSize_R_int(jint width, jint height) {
    return (jint) etc1_get_encoded_data_size(width, height);
}

void com::badlogic::gdx::graphics::glutils::ETC1::SM_formatHeader(const shared_ptr<ByteBuffer> &header, jint offset, jint width, jint height) {
    etc1_pkm_format_header((etc1_byte *) header->F_address + offset, width, height);
}

jint com::badlogic::gdx::graphics::glutils::ETC1::SM_getWidthPKM_R_int(const shared_ptr<ByteBuffer> &header, jint offset) {
    return (jint) etc1_pkm_get_width((etc1_byte *) header->F_address + offset);
}

jint com::badlogic::gdx::graphics::glutils::ETC1::SM_getHeightPKM_R_int(const shared_ptr<ByteBuffer> &header, jint offset) {
    return (jint) etc1_pkm_get_height((etc1_byte *) header->F_address + offset);
}

jbool com::badlogic::gdx::graphics::glutils::ETC1::SM_isValidPKM_R_boolean(const shared_ptr<ByteBuffer> &header, jint offset) {
    return etc1_pkm_is_valid((etc1_byte *) header->F_address + offset);
}

void com::badlogic::gdx::graphics::glutils::ETC1::SM_decodeImage(const shared_ptr<ByteBuffer> &compressedData, jint offset, const shared_ptr<ByteBuffer> &decodedData, jint offsetDec, jint width, jint height, jint pixelSize) {
    etc1_decode_image((etc1_byte *) compressedData->F_address + offset, (etc1_byte *) decodedData->F_address + offsetDec, width, height, pixelSize, width * pixelSize);
}

shared_ptr<ByteBuffer> com::badlogic::gdx::graphics::glutils::ETC1::SM_encodeImage_R_java_nio_ByteBuffer(const shared_ptr<ByteBuffer> &imageData, jint offset, jint width, jint height, jint pixelSize) {
    auto compressedSize = etc1_get_encoded_data_size(width, height);
    auto compressedData = (etc1_byte *) malloc(compressedSize);
    etc1_encode_image((etc1_byte *) imageData->F_address + offset, width, height, pixelSize, width * pixelSize, compressedData);
    auto pixelBuffer = make_shared<java::nio::ByteBuffer>();
    pixelBuffer->init((jlong) compressedData, (jint) compressedSize);
    return pixelBuffer;
}

shared_ptr<ByteBuffer> com::badlogic::gdx::graphics::glutils::ETC1::SM_encodeImagePKM_R_java_nio_ByteBuffer(const shared_ptr<ByteBuffer> &imageData, jint offset, jint width, jint height, jint pixelSize) {
    auto compressedSize = etc1_get_encoded_data_size(width, height);
    auto compressed = (etc1_byte *) malloc(compressedSize + ETC_PKM_HEADER_SIZE);
    etc1_pkm_format_header(compressed, width, height);
    etc1_encode_image((etc1_byte *) imageData->F_address + offset, width, height, pixelSize, width * pixelSize, compressed + ETC_PKM_HEADER_SIZE);
    auto pixelBuffer = make_shared<java::nio::ByteBuffer>();
    pixelBuffer->init((jlong) compressed, (jint) compressedSize);
    return pixelBuffer;
}

jint SwitchGraphics::M_getWidth_R_int() {
    int width;
    SDL_GetWindowSize(window, &width, nullptr);
    return width;
}

jint SwitchGraphics::M_getHeight_R_int() {
    int height;
    SDL_GetWindowSize(window, nullptr, &height);
    return height;
}

jint SwitchControllerManager::SM_getButtons_R_int(jint controller) {
#ifdef __SWITCH__
    auto &pad = controller == -1 ? combinedPad : pads[controller];
    return remapPadButtons(padGetButtons(&pad), padGetStyleSet(&pad));
#else
    return buttons;
#endif
}

void SwitchControllerManager::SM_getAxes_Array1_float(jint controller, const jarray &axes) {
    auto array = (float *) axes->data;
#ifdef __SWITCH__
    const auto &pad = controller == -1 ? combinedPad : pads[controller];
    auto stickLeft = padGetStickPos(&pad, 0);
    auto stickRight = padGetStickPos(&pad, 1);
    array[0] = (float)stickLeft.x / JOYSTICK_MAX;
    array[1] = (float)stickLeft.y / JOYSTICK_MAX;
    array[2] = (float)stickRight.x / JOYSTICK_MAX;
    array[3] = (float)stickRight.y / JOYSTICK_MAX;
    remapPadAxes(array, padGetStyleSet(&pad));
    // Todo: Is inversion needed?
    array[1] *= -1;
    array[3] *= -1;
#else
    memcpy(array, joysticks, sizeof(joysticks));
#endif
}

jbool SwitchControllerManager::SM_isConnected_R_boolean(jint controller) {
#ifdef __SWITCH__
    return pads[controller].active_handheld or pads[controller].active_id_mask;
#else
    return controller == 0;
#endif
}

void SwitchControllerManager::SM_remapControllers(jint min, jint max, jbool dualJoy, jbool singleMode) {
#ifdef __SWITCH__
    HidLaControllerSupportArg arg;
    hidLaCreateControllerSupportArg(&arg);
    arg.hdr.player_count_min = min;
    arg.hdr.player_count_max = max;
    arg.hdr.enable_permit_joy_dual = dualJoy;
    arg.hdr.enable_single_mode = singleMode;
    hidLaShowControllerSupportForSystem(nullptr, &arg, false);
#endif
}

void SwitchInput::SM_getTouchData_Array1_int(const jarray &touchData) {
    memcpy((void *) touchData->data, touches, sizeof(touches));
}

void SwitchInput::M_getTextInput(const shared_ptr<Input$TextInputListener> &listener, const jstring &title, const jstring &text, const jstring &hint, const shared_ptr<Input$OnscreenKeyboardType> &type) {
#ifdef __SWITCH__
    Result rc;
    SwkbdConfig kbd;
    char buffer[256];
    rc = swkbdCreate(&kbd, 0);
    if (rc)
        goto failed;
    swkbdConfigMakePresetDefault(&kbd);
    swkbdConfigSetHeaderText(&kbd, vm::getNativeString(title));
    swkbdConfigSetGuideText(&kbd, vm::getNativeString(text));
    swkbdConfigSetInitialText(&kbd, vm::getNativeString(hint));
    swkbdConfigSetStringLenMax(&kbd, sizeof(buffer) - 1);
    rc = swkbdShow(&kbd, buffer, sizeof(buffer));
    if (rc)
        goto failed;
    listener->M_input(vm::createString(buffer));
    return;
#elif defined(__WINRT__)
    goto failed;
#else
    auto input = tinyfd_inputBox(vm::getNativeString(title), vm::getNativeString(text), "");
    if (!input)
        goto failed;
    listener->M_input(vm::createString(input));
    return;
#endif
    failed:
    listener->M_canceled();
}

void SwitchGL::M_glActiveTexture(jint texture) {
    glActiveTexture(texture);
}

void SwitchGL::M_glBindTexture(jint target, jint texture) {
    glBindTexture(target, texture);
}

void SwitchGL::M_glBlendFunc(jint sfactor, jint dfactor) {
    glBlendFunc(sfactor, dfactor);
}

void SwitchGL::M_glClear(jint mask) {
    glClear(mask);
}

void SwitchGL::M_glClearColor(jfloat red, jfloat green, jfloat blue, jfloat alpha) {
    glClearColor(red, green, blue, alpha);
}

void SwitchGL::M_glClearDepthf(jfloat depth) {
    glClearDepthf(depth);
}

void SwitchGL::M_glClearStencil(jint s) {
    glClearStencil(s);
}

void SwitchGL::M_glColorMask(jbool red, jbool green, jbool blue, jbool alpha) {
    glColorMask(red, green, blue, alpha);
}

void SwitchGL::M_glCompressedTexImage2D(jint target, jint level, jint internalformat, jint width, jint height, jint border, jint imageSize, const shared_ptr<Buffer> &data) {
    glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, (void *) getBufferAddress(data));
}

void SwitchGL::M_glCompressedTexSubImage2D(jint target, jint level, jint xoffset, jint yoffset, jint width, jint height, jint format, jint imageSize, const shared_ptr<Buffer> &data) {
    glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, (void *) getBufferAddress(data));
}

void SwitchGL::M_glCopyTexImage2D(jint target, jint level, jint internalformat, jint x, jint y, jint width, jint height, jint border) {
    glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
}

void SwitchGL::M_glCopyTexSubImage2D(jint target, jint level, jint xoffset, jint yoffset, jint x, jint y, jint width, jint height) {
    glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}

void SwitchGL::M_glCullFace(jint mode) {
    glCullFace(mode);
}

void SwitchGL::M_glDeleteTextures(jint n, const shared_ptr<IntBuffer> &textures) {
    glDeleteTextures(n, (GLuint *) getBufferAddress(textures));
}

void SwitchGL::M_glDeleteTexture(jint texture) {
    glDeleteTextures(1, (GLuint *) &texture);
}

void SwitchGL::M_glDepthFunc(jint func) {
    glDepthFunc(func);
}

void SwitchGL::M_glDepthMask(jbool flag) {
    glDepthMask(flag);
}

void SwitchGL::M_glDepthRangef(jfloat zNear, jfloat zFar) {
    glDepthRangef(zNear, zFar);
}

void SwitchGL::M_glDisable(jint cap) {
    glDisable(cap);
}

void SwitchGL::M_glDrawArrays(jint mode, jint first, jint count) {
    glDrawArrays(mode, first, count);
}

void SwitchGL::M_glDrawElements(jint mode, jint count, jint type, const shared_ptr<Buffer> &indices) {
    glDrawElements(mode, count, type, (void *) getBufferAddress(indices));
}

void SwitchGL::M_glEnable(jint cap) {
    glEnable(cap);
}

void SwitchGL::M_glFinish() {
    glFinish();
}

void SwitchGL::M_glFlush() {
    glFlush();
}

void SwitchGL::M_glFrontFace(jint mode) {
    glFrontFace(mode);
}

void SwitchGL::M_glGenTextures(jint n, const shared_ptr<IntBuffer> &textures) {
    glGenTextures(n, (GLuint *) getBufferAddress(textures));
}

jint SwitchGL::M_glGenTexture_R_int() {
    GLuint texture;
    glGenTextures(1, &texture);
    return (jint) texture;
}

jint SwitchGL::M_glGetError_R_int() {
    return (jint) glGetError();
}

void SwitchGL::M_glGetIntegerv(jint pname, const shared_ptr<IntBuffer> &params) {
    glGetIntegerv(pname, (GLint *) getBufferAddress(params));
}

jstring SwitchGL::M_glGetString_R_java_lang_String(jint name) {
    return vm::createString((char *) glGetString(name));
}

void SwitchGL::M_glHint(jint target, jint mode) {
    glHint(target, mode);
}

void SwitchGL::M_glLineWidth(jfloat width) {
    glLineWidth(width);
}

void SwitchGL::M_glPixelStorei(jint pname, jint param) {
    glPixelStorei(pname, param);
}

void SwitchGL::M_glPolygonOffset(jfloat factor, jfloat units) {
    glPolygonOffset(factor, units);
}

void SwitchGL::M_glReadPixels(jint x, jint y, jint width, jint height, jint format, jint type, const shared_ptr<Buffer> &pixels) {
    glReadPixels(x, y, width, height, format, type, (void *) getBufferAddress(pixels));
}

void SwitchGL::M_glScissor(jint x, jint y, jint width, jint height) {
    glScissor(x, y, width, height);
}

void SwitchGL::M_glStencilFunc(jint func, jint ref, jint mask) {
    glStencilFunc(func, ref, mask);
}

void SwitchGL::M_glStencilMask(jint mask) {
    glStencilMask(mask);
}

void SwitchGL::M_glStencilOp(jint fail, jint zfail, jint zpass) {
    glStencilOp(fail, zfail, zpass);
}

void SwitchGL::M_glTexImage2D(jint target, jint level, jint internalformat, jint width, jint height, jint border, jint format, jint type, const shared_ptr<Buffer> &pixels) {
    glTexImage2D(target, level, internalformat, width, height, border, format, type, (void *) getBufferAddress(pixels));
}

void SwitchGL::M_glTexParameterf(jint target, jint pname, jfloat param) {
    glTexParameterf(target, pname, param);
}

void SwitchGL::M_glTexSubImage2D(jint target, jint level, jint xoffset, jint yoffset, jint width, jint height, jint format, jint type, const shared_ptr<Buffer> &pixels) {
    glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, (void *) getBufferAddress(pixels));
}

void SwitchGL::M_glViewport(jint x, jint y, jint width, jint height) {
    glViewport(x, y, width, height);
}

void SwitchGL::M_glAttachShader(jint program, jint shader) {
    glAttachShader(program, shader);
}

void SwitchGL::M_glBindAttribLocation(jint program, jint index, const jstring &name) {
    glBindAttribLocation(program, index, vm::getNativeString(name));
}

void SwitchGL::M_glBindBuffer(jint target, jint buffer) {
    glBindBuffer(target, buffer);
}

void SwitchGL::M_glBindFramebuffer(jint target, jint framebuffer) {
    glBindFramebuffer(target, framebuffer);
}

void SwitchGL::M_glBindRenderbuffer(jint target, jint renderbuffer) {
    glBindRenderbuffer(target, renderbuffer);
}

void SwitchGL::M_glBlendColor(jfloat red, jfloat green, jfloat blue, jfloat alpha) {
    glBlendColor(red, green, blue, alpha);
}

void SwitchGL::M_glBlendEquation(jint mode) {
    glBlendEquation(mode);
}

void SwitchGL::M_glBlendEquationSeparate(jint modeRGB, jint modeAlpha) {
    glBlendEquationSeparate(modeRGB, modeAlpha);
}

void SwitchGL::M_glBlendFuncSeparate(jint srcRGB, jint dstRGB, jint srcAlpha, jint dstAlpha) {
    glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
}

void SwitchGL::M_glBufferData(jint target, jint size, const shared_ptr<Buffer> &buffer, jint usage) {
    glBufferData(target, size, (void *) getBufferAddress(buffer), usage);
}

void SwitchGL::M_glBufferSubData(jint target, jint offset, jint size, const shared_ptr<Buffer> &data) {
    glBufferSubData(target, offset, size, (void *) getBufferAddress(data));
}

jint SwitchGL::M_glCheckFramebufferStatus_R_int(jint target) {
    return (jint) glCheckFramebufferStatus(target);
}

void SwitchGL::M_glCompileShader(jint shader) {
    glCompileShader(shader);
}

jint SwitchGL::M_glCreateProgram_R_int() {
    return (int) glCreateProgram();
}

jint SwitchGL::M_glCreateShader_R_int(jint type) {
    return (int) glCreateShader(type);
}

void SwitchGL::M_glDeleteBuffer(jint buffer) {
    glDeleteBuffers(1, (GLuint *) &buffer);
}

void SwitchGL::M_glDeleteBuffers(jint n, const shared_ptr<IntBuffer> &buffers) {
    glDeleteBuffers(n, (GLuint *) getBufferAddress(buffers));
}

void SwitchGL::M_glDeleteFramebuffer(jint framebuffer) {
    glDeleteFramebuffers(1, (GLuint *) &framebuffer);
}

void SwitchGL::M_glDeleteFramebuffers(jint n, const shared_ptr<IntBuffer> &framebuffers) {
    glDeleteFramebuffers(n, (GLuint *) getBufferAddress(framebuffers));
}

void SwitchGL::M_glDeleteProgram(jint program) {
    glDeleteProgram(program);
}

void SwitchGL::M_glDeleteRenderbuffer(jint renderbuffer) {
    glDeleteRenderbuffers(1, (GLuint *) &renderbuffer);
}

void SwitchGL::M_glDeleteRenderbuffers(jint n, const shared_ptr<IntBuffer> &renderbuffers) {
    glDeleteRenderbuffers(n, (GLuint *) getBufferAddress(renderbuffers));
}

void SwitchGL::M_glDeleteShader(jint shader) {
    glDeleteShader(shader);
}

void SwitchGL::M_glDetachShader(jint program, jint shader) {
    glDetachShader(program, shader);
}

void SwitchGL::M_glDisableVertexAttribArray(jint index) {
    glDisableVertexAttribArray(index);
}

void SwitchGL::M_glDrawElements(jint mode, jint count, jint type, jint indices) {
    glDrawElements(mode, count, type, (void *) (jlong) indices);
}

void SwitchGL::M_glEnableVertexAttribArray(jint index) {
    glEnableVertexAttribArray(index);
}

void SwitchGL::M_glFramebufferRenderbuffer(jint target, jint attachment, jint renderbuffertarget, jint renderbuffer) {
    glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

void SwitchGL::M_glFramebufferTexture2D(jint target, jint attachment, jint textarget, jint texture, jint level) {
    glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

jint SwitchGL::M_glGenBuffer_R_int() {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    return (jint) buffer;
}

void SwitchGL::M_glGenBuffers(jint n, const shared_ptr<IntBuffer> &buffers) {
    glGenBuffers(n, (GLuint *) getBufferAddress(buffers));
}

void SwitchGL::M_glGenerateMipmap(jint target) {
    glGenerateMipmap(target);
}

jint SwitchGL::M_glGenFramebuffer_R_int() {
    GLuint buffer;
    glGenFramebuffers(1, &buffer);
    return (jint) buffer;
}

void SwitchGL::M_glGenFramebuffers(jint n, const shared_ptr<IntBuffer> &framebuffers) {
    glGenFramebuffers(n, (GLuint *) getBufferAddress(framebuffers));
}

jint SwitchGL::M_glGenRenderbuffer_R_int() {
    GLuint buffer;
    glGenRenderbuffers(1, &buffer);
    return (jint) buffer;
}

void SwitchGL::M_glGenRenderbuffers(jint n, const shared_ptr<IntBuffer> &renderbuffers) {
    glGenRenderbuffers(n, (GLuint *) getBufferAddress(renderbuffers));
}

jstring SwitchGL::M_glGetActiveAttrib_R_java_lang_String(jint program, jint index, const shared_ptr<IntBuffer> &size, const shared_ptr<IntBuffer> &type) {
    char buffer[64];
    glGetActiveAttrib(program, index, 63, nullptr, (GLint *) getBufferAddress(size), (GLenum *) getBufferAddress(type), buffer);
    return vm::createString(buffer);
}

jstring SwitchGL::M_glGetActiveUniform_R_java_lang_String(jint program, jint index, const shared_ptr<IntBuffer> &size, const shared_ptr<IntBuffer> &type) {
    char buffer[64];
    glGetActiveUniform(program, index, 63, nullptr, (GLint *) getBufferAddress(size), (GLenum *) getBufferAddress(type), buffer);
    return vm::createString(buffer);
}

void SwitchGL::M_glGetAttachedShaders(jint program, jint maxcount, const shared_ptr<Buffer> &count, const shared_ptr<IntBuffer> &shaders) {
    glGetAttachedShaders(program, maxcount, (GLsizei *) getBufferAddress(count), (GLuint *) getBufferAddress(shaders));
}

jint SwitchGL::M_glGetAttribLocation_R_int(jint program, const jstring &name) {
    return glGetAttribLocation(program, vm::getNativeString(name));
}

void SwitchGL::M_glGetBooleanv(jint pname, const shared_ptr<Buffer> &params) {
    glGetBooleanv(pname, (GLboolean *) getBufferAddress(params));
}

void SwitchGL::M_glGetBufferParameteriv(jint target, jint pname, const shared_ptr<IntBuffer> &params) {
    glGetBufferParameteriv(target, pname, (GLint *) getBufferAddress(params));
}

void SwitchGL::M_glGetFloatv(jint pname, const shared_ptr<FloatBuffer> &params) {
    glGetFloatv(pname, (GLfloat *) getBufferAddress(params));
}

void SwitchGL::M_glGetFramebufferAttachmentParameteriv(jint target, jint attachment, jint pname, const shared_ptr<IntBuffer> &params) {
    glGetFramebufferAttachmentParameteriv(target, attachment, pname, (GLint *) getBufferAddress(params));
}

void SwitchGL::M_glGetProgramiv(jint program, jint pname, const shared_ptr<IntBuffer> &params) {
    glGetProgramiv(program, pname, (GLint *) getBufferAddress(params));
}

jstring SwitchGL::M_glGetProgramInfoLog_R_java_lang_String(jint program) {
    char buffer[128];
    glGetProgramInfoLog(program, 127, nullptr, buffer);
    return vm::createString(buffer);
}

void SwitchGL::M_glGetRenderbufferParameteriv(jint target, jint pname, const shared_ptr<IntBuffer> &params) {
    glGetRenderbufferParameteriv(target, pname, (GLint *) getBufferAddress(params));
}

void SwitchGL::M_glGetShaderiv(jint shader, jint pname, const shared_ptr<IntBuffer> &params) {
    glGetShaderiv(shader, pname, (GLint *) getBufferAddress(params));
}

jstring SwitchGL::M_glGetShaderInfoLog_R_java_lang_String(jint program) {
    char buffer[128];
    glGetShaderInfoLog(program, 127, nullptr, buffer);
    return vm::createString(buffer);
}

void SwitchGL::M_glGetShaderPrecisionFormat(jint shadertype, jint precisiontype, const shared_ptr<IntBuffer> &range, const shared_ptr<IntBuffer> &precision) {
    glGetShaderPrecisionFormat(shadertype, precisiontype, (GLint *) getBufferAddress(range), (GLint *) getBufferAddress(precision));
}

void SwitchGL::M_glGetTexParameterfv(jint target, jint pname, const shared_ptr<FloatBuffer> &params) {
    glGetTexParameterfv(target, pname, (GLfloat *) getBufferAddress(params));
}

void SwitchGL::M_glGetTexParameteriv(jint target, jint pname, const shared_ptr<IntBuffer> &params) {
    glGetTexParameteriv(target, pname, (GLint *) getBufferAddress(params));
}

void SwitchGL::M_glGetUniformfv(jint program, jint location, const shared_ptr<FloatBuffer> &params) {
    glGetUniformfv(program, location, (GLfloat *) getBufferAddress(params));
}

void SwitchGL::M_glGetUniformiv(jint program, jint location, const shared_ptr<IntBuffer> &params) {
    glGetUniformiv(program, location, (GLint *) getBufferAddress(params));
}

jint SwitchGL::M_glGetUniformLocation_R_int(jint program, const jstring &name) {
    return glGetUniformLocation(program, vm::getNativeString(name));
}

void SwitchGL::M_glGetVertexAttribfv(jint index, jint pname, const shared_ptr<FloatBuffer> &params) {
    glGetVertexAttribfv(index, pname, (GLfloat *) getBufferAddress(params));
}

void SwitchGL::M_glGetVertexAttribiv(jint index, jint pname, const shared_ptr<IntBuffer> &params) {
    glGetVertexAttribiv(index, pname, (GLint *) getBufferAddress(params));
}

void SwitchGL::M_glGetVertexAttribPointerv(jint index, jint pname, const shared_ptr<Buffer> &pointer) {
    glGetVertexAttribPointerv(index, pname, (void **) getBufferAddress(pointer));
}

jbool SwitchGL::M_glIsBuffer_R_boolean(jint buffer) {
    return glIsBuffer(buffer);
}

jbool SwitchGL::M_glIsEnabled_R_boolean(jint cap) {
    return glIsEnabled(cap);
}

jbool SwitchGL::M_glIsFramebuffer_R_boolean(jint framebuffer) {
    return glIsFramebuffer(framebuffer);
}

jbool SwitchGL::M_glIsProgram_R_boolean(jint program) {
    return glIsProgram(program);
}

jbool SwitchGL::M_glIsRenderbuffer_R_boolean(jint renderbuffer) {
    return glIsRenderbuffer(renderbuffer);
}

jbool SwitchGL::M_glIsShader_R_boolean(jint shader) {
    return glIsShader(shader);
}

jbool SwitchGL::M_glIsTexture_R_boolean(jint texture) {
    return glIsTexture(texture);
}

void SwitchGL::M_glLinkProgram(jint program) {
    glLinkProgram(program);
}

void SwitchGL::M_glReleaseShaderCompiler() {
    glReleaseShaderCompiler();
}

void SwitchGL::M_glRenderbufferStorage(jint target, jint internalformat, jint width, jint height) {
    glRenderbufferStorage(target, internalformat, width, height);
}

void SwitchGL::M_glSampleCoverage(jfloat value, jbool invert) {
    glSampleCoverage(value, invert);
}

void SwitchGL::M_glShaderBinary(jint n, const shared_ptr<IntBuffer> &shaders, jint binaryformat, const shared_ptr<Buffer> &binary, jint length) {
    glShaderBinary(n, (GLuint *) getBufferAddress(shaders), binaryformat, (void *) getBufferAddress(binary), length);
}

void SwitchGL::M_glShaderSource(jint shader, const jstring &sourceObject) {
    auto source = vm::getNativeString(sourceObject);
    glShaderSource(shader, 1, &source, nullptr);
}

void SwitchGL::M_glStencilFuncSeparate(jint face, jint func, jint ref, jint mask) {
    glStencilFuncSeparate(face, func, ref, mask);
}

void SwitchGL::M_glStencilMaskSeparate(jint face, jint mask) {
    glStencilMaskSeparate(face, mask);
}

void SwitchGL::M_glStencilOpSeparate(jint face, jint fail, jint zfail, jint zpass) {
    glStencilOpSeparate(face, fail, zfail, zpass);
}

void SwitchGL::M_glTexParameterfv(jint target, jint pname, const shared_ptr<FloatBuffer> &params) {
    glTexParameterfv(target, pname, (GLfloat *) getBufferAddress(params));
}

void SwitchGL::M_glTexParameteri(jint target, jint pname, jint param) {
    glTexParameteri(target, pname, param);
}

void SwitchGL::M_glTexParameteriv(jint target, jint pname, const shared_ptr<IntBuffer> &params) {
    glTexParameteriv(target, pname, (GLint *) getBufferAddress(params));
}

void SwitchGL::M_glUniform1f(jint location, jfloat x) {
    glUniform1f(location, x);
}

void SwitchGL::M_glUniform1fv(jint location, jint count, const shared_ptr<FloatBuffer> &v) {
    glUniform1fv(location, count, (GLfloat *) getBufferAddress(v));
}

void SwitchGL::M_glUniform1fv_Array1_float(jint location, jint count, const jarray &v, jint offset) {
    glUniform1fv(location, count, (GLfloat *) v->data + offset);
}

void SwitchGL::M_glUniform1i(jint location, jint x) {
    glUniform1i(location, x);
}

void SwitchGL::M_glUniform1iv(jint location, jint count, const shared_ptr<IntBuffer> &v) {
    glUniform1iv(location, count, (GLint *) getBufferAddress(v));
}

void SwitchGL::M_glUniform1iv_Array1_int(jint location, jint count, const jarray &v, jint offset) {
    glUniform1iv(location, count, (GLint *) v->data + offset);
}

void SwitchGL::M_glUniform2f(jint location, jfloat x, jfloat y) {
    glUniform2f(location, x, y);
}

void SwitchGL::M_glUniform2fv(jint location, jint count, const shared_ptr<FloatBuffer> &v) {
    glUniform2fv(location, count, (GLfloat *) getBufferAddress(v));
}

void SwitchGL::M_glUniform2fv_Array1_float(jint location, jint count, const jarray &v, jint offset) {
    glUniform2fv(location, count, (GLfloat *) v->data + offset);
}

void SwitchGL::M_glUniform2i(jint location, jint x, jint y) {
    glUniform2i(location, x, y);
}

void SwitchGL::M_glUniform2iv(jint location, jint count, const shared_ptr<IntBuffer> &v) {
    glUniform2iv(location, count, (GLint *) getBufferAddress(v));
}

void SwitchGL::M_glUniform2iv_Array1_int(jint location, jint count, const jarray &v, jint offset) {
    glUniform2iv(location, count, (GLint *) v->data + offset);
}

void SwitchGL::M_glUniform3f(jint location, jfloat x, jfloat y, jfloat z) {
    glUniform3f(location, x, y, z);
}

void SwitchGL::M_glUniform3fv(jint location, jint count, const shared_ptr<FloatBuffer> &v) {
    glUniform3fv(location, count, (GLfloat *) getBufferAddress(v));
}

void SwitchGL::M_glUniform3fv_Array1_float(jint location, jint count, const jarray &v, jint offset) {
    glUniform3fv(location, count, (GLfloat *) v->data + offset);
}

void SwitchGL::M_glUniform3i(jint location, jint x, jint y, jint z) {
    glUniform3i(location, x, y, z);
}

void SwitchGL::M_glUniform3iv(jint location, jint count, const shared_ptr<IntBuffer> &v) {
    glUniform3iv(location, count, (GLint *) getBufferAddress(v));
}

void SwitchGL::M_glUniform3iv_Array1_int(jint location, jint count, const jarray &v, jint offset) {
    glUniform3iv(location, count, (GLint *) v->data + offset);
}

void SwitchGL::M_glUniform4f(jint location, jfloat x, jfloat y, jfloat z, jfloat w) {
    glUniform4f(location, x, y, z, w);
}

void SwitchGL::M_glUniform4fv(jint location, jint count, const shared_ptr<FloatBuffer> &v) {
    glUniform4fv(location, count, (GLfloat *) getBufferAddress(v));
}

void SwitchGL::M_glUniform4fv_Array1_float(jint location, jint count, const jarray &v, jint offset) {
    glUniform4fv(location, count, (GLfloat *) v->data + offset);
}

void SwitchGL::M_glUniform4i(jint location, jint x, jint y, jint z, jint w) {
    glUniform4i(location, x, y, z, w);
}

void SwitchGL::M_glUniform4iv(jint location, jint count, const shared_ptr<IntBuffer> &v) {
    glUniform4iv(location, count, (GLint *) getBufferAddress(v));
}

void SwitchGL::M_glUniform4iv_Array1_int(jint location, jint count, const jarray &v, jint offset) {
    glUniform4iv(location, count, (GLint *) v->data + offset);
}

void SwitchGL::M_glUniformMatrix2fv(jint location, jint count, jbool transpose, const shared_ptr<FloatBuffer> &value) {
    glUniformMatrix2fv(location, count, transpose, (GLfloat *) getBufferAddress(value));
}

void SwitchGL::M_glUniformMatrix2fv_Array1_float(jint location, jint count, jbool transpose, const jarray &value, jint offset) {
    glUniformMatrix2fv(location, count, transpose, (GLfloat *) value->data + offset);
}

void SwitchGL::M_glUniformMatrix3fv(jint location, jint count, jbool transpose, const shared_ptr<FloatBuffer> &value) {
    glUniformMatrix3fv(location, count, transpose, (GLfloat *) getBufferAddress(value));
}

void SwitchGL::M_glUniformMatrix3fv_Array1_float(jint location, jint count, jbool transpose, const jarray &value, jint offset) {
    glUniformMatrix3fv(location, count, transpose, (GLfloat *) value->data + offset);
}

void SwitchGL::M_glUniformMatrix4fv(jint location, jint count, jbool transpose, const shared_ptr<FloatBuffer> &value) {
    glUniformMatrix4fv(location, count, transpose, (GLfloat *) getBufferAddress(value));
}

void SwitchGL::M_glUniformMatrix4fv_Array1_float(jint location, jint count, jbool transpose, const jarray &value, jint offset) {
    glUniformMatrix4fv(location, count, transpose, (GLfloat *) value->data + offset);
}

void SwitchGL::M_glUseProgram(jint program) {
    glUseProgram(program);
}

void SwitchGL::M_glValidateProgram(jint program) {
    glValidateProgram(program);
}

void SwitchGL::M_glVertexAttrib1f(jint indx, jfloat x) {
    glVertexAttrib1f(indx, x);
}

void SwitchGL::M_glVertexAttrib1fv(jint indx, const shared_ptr<FloatBuffer> &values) {
    glVertexAttrib1fv(indx, (GLfloat *) getBufferAddress(values));
}

void SwitchGL::M_glVertexAttrib2f(jint indx, jfloat x, jfloat y) {
    glVertexAttrib2f(indx, x, y);
}

void SwitchGL::M_glVertexAttrib2fv(jint indx, const shared_ptr<FloatBuffer> &values) {
    glVertexAttrib2fv(indx, (GLfloat *) getBufferAddress(values));
}

void SwitchGL::M_glVertexAttrib3f(jint indx, jfloat x, jfloat y, jfloat z) {
    glVertexAttrib3f(indx, x, y, z);
}

void SwitchGL::M_glVertexAttrib3fv(jint indx, const shared_ptr<FloatBuffer> &values) {
    glVertexAttrib3fv(indx, (GLfloat *) getBufferAddress(values));
}

void SwitchGL::M_glVertexAttrib4f(jint indx, jfloat x, jfloat y, jfloat z, jfloat w) {
    glVertexAttrib4f(indx, x, y, z, w);
}

void SwitchGL::M_glVertexAttrib4fv(jint indx, const shared_ptr<FloatBuffer> &values) {
    glVertexAttrib4fv(indx, (GLfloat *) getBufferAddress(values));
}

void SwitchGL::M_glVertexAttribPointer(jint index, jint size, jint type, jbool normalized, jint stride, const shared_ptr<Buffer> &ptr) {
    glVertexAttribPointer(index, size, type, normalized, stride, getBufferAddress(ptr));
}

void SwitchGL::M_glVertexAttribPointer(jint index, jint size, jint type, jbool normalized, jint stride, jint ptr) {
    glVertexAttribPointer(index, size, type, normalized, stride, (void *) (jlong) ptr);
}
