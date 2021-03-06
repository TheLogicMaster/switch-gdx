#include <fcntl.h>
#include <csignal>
#include <vector>
#include <string>
#include "gdx_buffer_utils.h"
#include "gdx_matrix4.h"
#include "gdx2d.h"
#include "etc1_utils.h"
#include "tinyfiledialogs.h"
#include <curl/curl.h>
#include <chrono>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_gamecontroller.h>

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

extern "C" {
#include "cn1_globals.h"
#include "java_nio_Buffer.h"
#include "java_nio_ByteBuffer.h"
#include "java_nio_FloatBuffer.h"
#include "java_nio_IntBuffer.h"
#include "java_io_File.h"
#include "java_io_FileNotFoundException.h"
#include "java_io_FileInputStream.h"
#include "java_io_FileOutputStream.h"
#include "java_lang_String.h"
#include "com_thelogicmaster_switchgdx_SwitchAudio.h"
#include "com_thelogicmaster_switchgdx_SwitchMusic.h"
#include "com_thelogicmaster_switchgdx_SwitchSound.h"
#include "com_thelogicmaster_switchgdx_SwitchHttpResponse.h"
#include "com_badlogic_gdx_utils_GdxRuntimeException.h"
#include "com_badlogic_gdx_Input_TextInputListener.h"
#include "com_thelogicmaster_switchgdx_SwitchSocket.h"
#include "com_thelogicmaster_switchgdx_SwitchServerSocket.h"

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

static PadState pad;

static int nxlinkSock = -1;
static bool socketInit;
#else
static SDL_Window *window;
static int buttons;
static float joysticks[4];
#endif

#ifdef __SWITCH__
static void initNxLink() {
    nxlinkSock = nxlinkStdio();
    if (nxlinkSock >= 0)
        printf("STDIO Redirected over NXLink\n");
}

static void deinitNxLink() {
    if (nxlinkSock >= 0) {
        close(nxlinkSock);
        nxlinkSock = -1;
    }
}

void userAppInit() {
    if (R_FAILED(socketInitializeDefault()))
        return;
    initNxLink();
    socketInit = true;
}

void userAppExit() {
    deinitNxLink();
    if (socketInit)
        socketExit();
}
#endif

void onMusicFinished() {
    com_thelogicmaster_switchgdx_SwitchAudio_onMusicFinished__(getThreadLocalData());
}

void onSoundFinished(int channel) {
    com_thelogicmaster_switchgdx_SwitchAudio_onSoundFinished___int(getThreadLocalData(), channel);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchApplication_init__(CODENAME_ONE_THREAD_STATE) {
    for (int i = 0; i < 16; i++)
        touches[i * 3] = -1;

#if defined(__WIN32__) || defined(__WINRT__)
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data))
        throwException(threadStateData, __NEW_INSTANCE_java_io_IOException(threadStateData));
#endif

#ifdef __SWITCH__
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
    padInitializeDefault(&pad);

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

    window = SDL_CreateWindow("SwitchGDX", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
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
    Mix_AllocateChannels(16);
    Mix_HookMusicFinished(onMusicFinished);
    Mix_ChannelFinished(onSoundFinished);

    curl_global_init(CURL_GLOBAL_ALL);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchApplication_dispose__(CODENAME_ONE_THREAD_STATE) {
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
            return 1;
        case SDL_SCANCODE_S:
            return 0x4 + 1;
        case SDL_SCANCODE_A:
            return 0x4 + 0;
        case SDL_SCANCODE_D:
            return 0;
        case SDL_SCANCODE_I:
            return 3;
        case SDL_SCANCODE_K:
            return 0x4 + 3;
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
#endif

JAVA_BOOLEAN com_thelogicmaster_switchgdx_SwitchApplication_update___R_boolean(CODENAME_ONE_THREAD_STATE) {
#ifdef __SWITCH__
    padUpdate(&pad);
    u64 kDown = padGetButtonsDown(&pad);
    if (kDown & HidNpadButton_Plus)
        return false;

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
                    joysticks[event.caxis.axis] = (float)(event.caxis.axis & 0x1 ? -1 : 1) * (float)event.caxis.value / 32768.f;
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

JAVA_OBJECT com_thelogicmaster_switchgdx_SwitchFiles_getLocalStoragePath___R_java_lang_String(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT  __cn1ThisObject) {
#ifdef __WINRT__
    auto path = getLocalPathUWP();
    return fromNativeString(threadStateData, path.c_str());
#else
    return fromNativeString(threadStateData, "data");
#endif
}

JAVA_BOOLEAN com_thelogicmaster_switchgdx_SwitchNet_openURI___java_lang_String_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT  __cn1ThisObject, JAVA_OBJECT urlObj) {
#ifdef __SWITCH__
    WebCommonConfig config;
    WebCommonReply reply;
    return !webPageCreate(&config, toNativeString(threadStateData, urlObj)) and !webConfigSetWhitelist(&config, "^http*") and !webConfigShow(&config, &reply);
#else
    std::string url(toNativeString(threadStateData, urlObj));
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

JAVA_OBJECT com_thelogicmaster_switchgdx_SwitchNet_sendRequest___java_lang_String_byte_1ARRAY_java_lang_String_1ARRAY_java_lang_String_long_com_thelogicmaster_switchgdx_SwitchHttpResponse_R_java_lang_String(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT urlObj, JAVA_OBJECT contentObj, JAVA_OBJECT headersObj, JAVA_OBJECT methodObj, JAVA_LONG timeout, JAVA_OBJECT responseObj) {
    char errorBuffer[CURL_ERROR_SIZE]{};
    CURL *curl = curl_easy_init();
    if (!curl)
        return JAVA_NULL;

    std::string responseData;
    curl_easy_setopt(curl, CURLOPT_URL, toNativeString(threadStateData, urlObj));
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "switchgdx-agent/1.0");
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);

    curl_slist *headers = nullptr;
    auto headersArray = (JAVA_ARRAY)headersObj;
    for (int i = 0; i < headersArray->length; i++)
        headers = curl_slist_append(headers, toNativeString(threadStateData, ((JAVA_OBJECT *)headersArray->data)[i]));
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    auto method = std::string(toNativeString(threadStateData, methodObj));
    if (method == "POST" or method == "PUT" or method == "PATCH") {
        auto contentArray = (JAVA_ARRAY) contentObj;
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
        return fromNativeString(threadStateData, strlen(errorBuffer) ? errorBuffer : curl_easy_strerror(res));

    auto httpResponse = (obj__com_thelogicmaster_switchgdx_SwitchHttpResponse *) responseObj;
    httpResponse->com_thelogicmaster_switchgdx_SwitchHttpResponse_status = (JAVA_INT)status;

    auto response = __NEW_ARRAY_JAVA_BYTE(threadStateData, (int)responseData.length());
    memcpy(((JAVA_ARRAY)response)->data, responseData.c_str(), responseData.length());
    httpResponse->com_thelogicmaster_switchgdx_SwitchHttpResponse_result = response;

    return JAVA_NULL;
}

void throwNativeSocketException(CODENAME_ONE_THREAD_STATE, bool inErrno = false) {
    auto exception = __NEW_java_io_IOException(threadStateData);
    JAVA_OBJECT error;
    if (errno == ETIMEDOUT)
        error = fromNativeString(threadStateData, "Timed out");
    else {
#if defined(__WIN32__)
        if (!inErrno)
            errno = WSAGetLastError();
        char buffer[256];
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK, nullptr, errno, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buffer, sizeof(buffer), nullptr);
        error = fromNativeString(threadStateData, buffer);
#elif defined(__WINRT__)
        error = fromNativeString(threadStateData, "Socket error");
#else
        error = fromNativeString(threadStateData, strerror(errno));
#endif
    }
    java_io_IOException___INIT_____java_lang_String(threadStateData, exception, error);
    throwException(threadStateData, exception);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchSocket_dispose__(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject) {
    auto switchSocket = (obj__com_thelogicmaster_switchgdx_SwitchSocket *) __cn1ThisObject;
    if (switchSocket->com_thelogicmaster_switchgdx_SwitchSocket_fd) {
#if defined(__WIN32__) || defined(__WINRT__)
        shutdown(switchSocket->com_thelogicmaster_switchgdx_SwitchSocket_fd, SD_SEND);
        closesocket(switchSocket->com_thelogicmaster_switchgdx_SwitchSocket_fd);
#else
        close(switchSocket->com_thelogicmaster_switchgdx_SwitchSocket_fd);
#endif
        switchSocket->com_thelogicmaster_switchgdx_SwitchSocket_fd = 0;
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

JAVA_INT com_thelogicmaster_switchgdx_SwitchSocket_create___java_lang_String_int_int_int_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT hostObj, JAVA_INT port, JAVA_INT connectTimeout, JAVA_INT timeout) {
    std::string host(hostObj ? toNativeString(threadStateData, hostObj) : "");
    const char *hostname = nullptr;
    if (hostObj)
        hostname = host.c_str();

    int fd = -1;

    addrinfo hints{};
    addrinfo *addrInfo = nullptr, *addrInfoIter = nullptr;
    in6_addr serverAddr{};
    hints.ai_flags = AI_NUMERICSERV;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    auto portString = std::to_string(port);

    if (hostname) {
        if (inet_pton(AF_INET, hostname, &serverAddr) == 1) {
            hints.ai_family = AF_INET;
            hints.ai_flags |= AI_NUMERICHOST;
        } else if (inet_pton(AF_INET6, hostname, &serverAddr) == 1) {
            hints.ai_family = AF_INET6;
            hints.ai_flags |= AI_NUMERICHOST;
        }
    }

    if (getaddrinfo(hostname, portString.c_str(), &hints, &addrInfo))
        goto error;

    for (addrInfoIter = addrInfo; addrInfoIter; addrInfoIter = addrInfoIter->ai_next) {
        fd = socket(addrInfoIter->ai_family, addrInfoIter->ai_socktype, addrInfoIter->ai_protocol);
        if (fd < 0)
            goto error;

#if defined(__WIN32__) || defined(__WINRT__)
        u_long nonblocking = 1;
        ioctlsocket(fd, FIONBIO, &nonblocking);
#else
        if (fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK) < 0)
            goto error;
#endif

        if (connect(fd, addrInfoIter->ai_addr, (int)addrInfoIter->ai_addrlen)) {
#if defined(__WIN32__) || defined(__WINRT__)
            if (WSAGetLastError() == WSAEWOULDBLOCK) {
#else
            if (errno == EWOULDBLOCK or errno == EINPROGRESS) {
#endif
                auto start = std::chrono::steady_clock::now();
                int remaining;
                while (true) {
                    remaining = connectTimeout - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
                    if (remaining <= 0) {
                        fd = -1;
                        errno = ETIMEDOUT;
                        break;
                    }
                    fd_set wr{}, ex{};
                    timeval t{};
                    FD_SET(fd, &wr);
                    FD_SET(fd, &ex);
                    t.tv_sec = remaining / 1000;
                    t.tv_usec = (remaining % 1000) * 1000;
                    int rc = select(fd + 1, nullptr, &wr, &ex, &t);
                    if (rc < 0 && errno == EINTR)
                        continue;
                    if (rc == 0 or FD_ISSET(fd, &ex))
                        fd = -1;
                    if (rc == 0)
                        errno = ETIMEDOUT;
                    break;
                }
                if (fd >= 0)
                    break;
            } else {
#if defined(__WIN32__) || defined(__WINRT__)
                shutdown(fd, SD_SEND);
                closesocket(fd);
#else
                close(fd);
#endif
                fd = -1;
            }
        } else
            break;
    }

    if (fd < 0)
        goto error;

#if defined(__WIN32__) || defined(__WINRT__)
    {
        u_long nonblocking = 0;
        ioctlsocket(fd, FIONBIO, &nonblocking);
    }
#else
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) & ~O_NONBLOCK);
#endif

    setSocketTimeout(fd, timeout);

    freeaddrinfo(addrInfo);
    return fd;

    error:
#if defined(__WIN32__) || defined(__WINRT__)
    errno = WSAGetLastError();
#endif

    if (fd > 0) {
#if defined(__WIN32__) || defined(__WINRT__)
        shutdown(fd, SD_SEND);
        closesocket(fd);
#else
        close(fd);
#endif
    }
    if (addrInfo)
        freeaddrinfo(addrInfo);
    throwNativeSocketException(threadStateData, true);
    return 0;
}

JAVA_INT com_thelogicmaster_switchgdx_SwitchSocket_read___R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject) {
    auto switchSocket = (obj__com_thelogicmaster_switchgdx_SwitchSocket *) __cn1ThisObject;
    signed char buffer;
    if (!switchSocket->com_thelogicmaster_switchgdx_SwitchSocket_fd)
        throwException(threadStateData, __NEW_INSTANCE_java_io_IOException(threadStateData));
    if (recv(switchSocket->com_thelogicmaster_switchgdx_SwitchSocket_fd, (char *)&buffer, 1, 0) != 1) {
#if defined(__WIN32__) || defined(__WINRT__)
        errno = WSAGetLastError();
#endif
        throwNativeSocketException(threadStateData, true);
    }
    return buffer;
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchSocket_write___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT value) {
    auto switchSocket = (obj__com_thelogicmaster_switchgdx_SwitchSocket *) __cn1ThisObject;
    auto buffer = (signed char) value;
    if (!switchSocket->com_thelogicmaster_switchgdx_SwitchSocket_fd)
        throwException(threadStateData, __NEW_INSTANCE_java_io_IOException(threadStateData));
    if (send(switchSocket->com_thelogicmaster_switchgdx_SwitchSocket_fd, (char *)&buffer, 1, 0) != 1) {
#if defined(__WIN32__) || defined(__WINRT__)
        errno = WSAGetLastError();
#endif
        throwNativeSocketException(threadStateData);
    }
}

JAVA_OBJECT com_thelogicmaster_switchgdx_SwitchSocket_getRemoteAddress___R_java_lang_String(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject) {
    auto switchSocket = (obj__com_thelogicmaster_switchgdx_SwitchSocket *) __cn1ThisObject;
    if (!switchSocket->com_thelogicmaster_switchgdx_SwitchSocket_fd)
        throwException(threadStateData, __NEW_INSTANCE_java_io_IOException(threadStateData));
    sockaddr_storage address{};
    socklen_t addrLen = sizeof(address);
    char addrStr[INET6_ADDRSTRLEN];
    if (getpeername(switchSocket->com_thelogicmaster_switchgdx_SwitchSocket_fd, (sockaddr *) &address, &addrLen))
        throwNativeSocketException(threadStateData);
    auto data = address.ss_family == AF_INET ? (void *)&((sockaddr_in *)&address)->sin_addr : (void *)&((sockaddr_in6 *)&address)->sin6_addr;
    if (!inet_ntop(address.ss_family, data, addrStr, sizeof(addrStr)))
        throwNativeSocketException(threadStateData);
    return fromNativeString(threadStateData, addrStr);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchServerSocket_dispose__(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject) {
    auto server = (obj__com_thelogicmaster_switchgdx_SwitchServerSocket *) __cn1ThisObject;
    if (server->com_thelogicmaster_switchgdx_SwitchServerSocket_fd) {
#if defined(__WIN32__) || defined(__WINRT__)
        shutdown(server->com_thelogicmaster_switchgdx_SwitchServerSocket_fd, SD_SEND);
        closesocket(server->com_thelogicmaster_switchgdx_SwitchServerSocket_fd);
#else
        close(server->com_thelogicmaster_switchgdx_SwitchServerSocket_fd);
#endif
        server->com_thelogicmaster_switchgdx_SwitchServerSocket_fd = 0;
    }
}

JAVA_INT com_thelogicmaster_switchgdx_SwitchServerSocket_create___int_boolean_R_int(CODENAME_ONE_THREAD_STATE, JAVA_INT port, JAVA_BOOLEAN reuseAddress) {
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;
    int fd;

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        goto error;

    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *) &reuseAddress, sizeof(int)) < 0)
        goto error;

#if defined(__WIN32__) || defined(__WINRT__)
    {
        u_long nonblocking = 1;
        ioctlsocket(fd, FIONBIO, &nonblocking);
    }
#else
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
#endif

    if (bind(fd, (sockaddr *) &address, sizeof(address)) < 0)
        goto error;

    if (listen(fd, 10) < 0)
        goto error;

    return fd;

    error:
#if defined(__WIN32__) || defined(__WINRT__)
    errno = WSAGetLastError();
#endif

    if (fd > 0) {
#if defined(__WIN32__) || defined(__WINRT__)
        shutdown(fd, SD_SEND);
        closesocket(fd);
#else
        close(fd);
#endif
    }
    throwNativeSocketException(threadStateData, true);
    return 0;
}

JAVA_INT com_thelogicmaster_switchgdx_SwitchServerSocket_accept___int_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT timeout) {
    auto server = (obj__com_thelogicmaster_switchgdx_SwitchServerSocket *) __cn1ThisObject;
    if (!server->com_thelogicmaster_switchgdx_SwitchServerSocket_fd)
        throwException(threadStateData, __NEW_INSTANCE_java_io_IOException(threadStateData));

    sockaddr_in6 address{};
    socklen_t addrLen = sizeof(address);
    if (getsockname(server->com_thelogicmaster_switchgdx_SwitchServerSocket_fd, (sockaddr *) &address, &addrLen))
        throwNativeSocketException(threadStateData);

    int fd = -1;
    auto start = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() < server->com_thelogicmaster_switchgdx_SwitchServerSocket_acceptTimeout) {
        fd = accept(server->com_thelogicmaster_switchgdx_SwitchServerSocket_fd, (sockaddr *) &address, &addrLen);
        if (fd >= 0)
            break;
#if defined(__WIN32__) || defined(__WINRT__)
        if (WSAGetLastError() != WSAEWOULDBLOCK)
#else
        if (errno != EAGAIN)
#endif
            throwNativeSocketException(threadStateData);
    }

    if (fd < 0) {
        auto error = __NEW_java_io_IOException(threadStateData);
        java_io_IOException___INIT_____java_lang_String(threadStateData, error, fromNativeString(threadStateData, "Accept timed out"));
        throwException(threadStateData, error);
    }

#if defined(__WIN32__) || defined(__WINRT__)
    {
        u_long nonblocking = 0;
        ioctlsocket(fd, FIONBIO, &nonblocking);
    }
#else
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) & ~O_NONBLOCK);
#endif
    setSocketTimeout(fd, timeout);
    return fd;
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchMusic_create___java_lang_String(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT  __cn1ThisObject, JAVA_OBJECT file) {
    auto music = Mix_LoadMUS(toNativeString(threadStateData, file));
    if (!music) {
        auto exception = __NEW_com_badlogic_gdx_utils_GdxRuntimeException(threadStateData);
        com_badlogic_gdx_utils_GdxRuntimeException___INIT____(threadStateData, exception);
        throwException(threadStateData, exception);
        return;
    }
    ((obj__com_thelogicmaster_switchgdx_SwitchMusic *)__cn1ThisObject)->com_thelogicmaster_switchgdx_SwitchMusic_handle = (JAVA_LONG)music;
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchMusic_start___boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT  __cn1ThisObject, JAVA_BOOLEAN looping) {
    Mix_PlayMusic((Mix_Music*)((obj__com_thelogicmaster_switchgdx_SwitchMusic*)__cn1ThisObject)->com_thelogicmaster_switchgdx_SwitchMusic_handle, looping ? -1 : 0);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchMusic_resume__(CODENAME_ONE_THREAD_STATE) {
    Mix_ResumeMusic();
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchMusic_pause0__(CODENAME_ONE_THREAD_STATE) {
    Mix_PauseMusic();
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchMusic_stop0__(CODENAME_ONE_THREAD_STATE) {
    Mix_HaltMusic();
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchMusic_setVolume0___float(CODENAME_ONE_THREAD_STATE, JAVA_FLOAT volume) {
    Mix_VolumeMusic((int)(volume * MIX_MAX_VOLUME));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchMusic_setPosition0___float(CODENAME_ONE_THREAD_STATE, JAVA_FLOAT position) {
    Mix_RewindMusic();
    Mix_SetMusicPosition(position);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchMusic_dispose0__(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT  __cn1ThisObject) {
    auto& handle = ((obj__com_thelogicmaster_switchgdx_SwitchMusic*)__cn1ThisObject)->com_thelogicmaster_switchgdx_SwitchMusic_handle;
    if (!handle)
        return;
    Mix_FreeMusic((Mix_Music *)handle);
    handle = 0;
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchSound_create___java_lang_String(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT  __cn1ThisObject, JAVA_OBJECT file) {
    auto sound = Mix_LoadWAV(toNativeString(threadStateData, file));
    if (!sound) {
        auto exception = __NEW_com_badlogic_gdx_utils_GdxRuntimeException(threadStateData);
        com_badlogic_gdx_utils_GdxRuntimeException___INIT____(threadStateData, exception);
        throwException(threadStateData, exception);
        return;
    }
    ((obj__com_thelogicmaster_switchgdx_SwitchSound *)__cn1ThisObject)->com_thelogicmaster_switchgdx_SwitchSound_handle = (JAVA_LONG)sound;
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchSound_dispose0__(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT  __cn1ThisObject) {
    auto &handle = ((obj__com_thelogicmaster_switchgdx_SwitchSound*)__cn1ThisObject)->com_thelogicmaster_switchgdx_SwitchSound_handle;
    if (!handle)
        return;
    Mix_FreeChunk((Mix_Chunk *)handle);
    handle = 0;
}

JAVA_INT com_thelogicmaster_switchgdx_SwitchSound_play0___boolean_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT  __cn1ThisObject, JAVA_BOOLEAN looping) {
    return Mix_PlayChannel(-1, (Mix_Chunk*)((obj__com_thelogicmaster_switchgdx_SwitchSound*)__cn1ThisObject)->com_thelogicmaster_switchgdx_SwitchSound_handle, looping ? -1 : 0);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchSound_stop0___int(CODENAME_ONE_THREAD_STATE, JAVA_INT channel) {
    Mix_HaltChannel(channel);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchSound_pause0___int(CODENAME_ONE_THREAD_STATE, JAVA_INT channel) {
    Mix_Pause(channel);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchSound_resume0___int(CODENAME_ONE_THREAD_STATE, JAVA_INT channel) {
    Mix_Resume(channel);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchSound_setPitch0___int_float(CODENAME_ONE_THREAD_STATE, JAVA_INT channel, JAVA_FLOAT pitch) {
    // Todo: Custom pitch changing effect based on: https://gist.github.com/hydren/ea794e65e95c7713c00c88f74b71f8b1
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchSound_setVolume0___int_float(CODENAME_ONE_THREAD_STATE, JAVA_INT channel, JAVA_FLOAT volume) {
    Mix_Volume(channel, (int)(volume * MIX_MAX_VOLUME));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchSound_setPan0___int_float(CODENAME_ONE_THREAD_STATE, JAVA_INT channel, JAVA_FLOAT pan) {
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

void *getBufferAddress(JAVA_OBJECT buffer) {
    if (buffer == JAVA_NULL)
        return nullptr;
    int typeSize;
    if (instanceofFunction(cn1_class_id_java_nio_ByteBuffer, buffer->__codenameOneParentClsReference->classId))
        typeSize = sizeof(JAVA_ARRAY_BYTE);
    else if (instanceofFunction(cn1_class_id_java_nio_ShortBuffer, buffer->__codenameOneParentClsReference->classId))
        typeSize = sizeof(JAVA_ARRAY_SHORT);
    else if (instanceofFunction(cn1_class_id_java_nio_IntBuffer, buffer->__codenameOneParentClsReference->classId))
        typeSize = sizeof(JAVA_ARRAY_INT);
    else if (instanceofFunction(cn1_class_id_java_nio_FloatBuffer, buffer->__codenameOneParentClsReference->classId))
        typeSize = sizeof(JAVA_ARRAY_FLOAT);
    else if (instanceofFunction(cn1_class_id_java_nio_LongBuffer, buffer->__codenameOneParentClsReference->classId))
        typeSize = sizeof(JAVA_ARRAY_LONG);
    else if (instanceofFunction(cn1_class_id_java_nio_DoubleBuffer, buffer->__codenameOneParentClsReference->classId))
        typeSize = sizeof(JAVA_ARRAY_DOUBLE);
    else
        typeSize = 1;
    return (char*)((obj__java_nio_Buffer *) buffer)->java_nio_Buffer_address + typeSize * ((obj__java_nio_Buffer *) buffer)->java_nio_Buffer_position;
}

JAVA_VOID com_badlogic_gdx_utils_BufferUtils_freeMemory___java_nio_ByteBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT buffer) {
    auto memory = (void *) ((obj__java_nio_ByteBuffer *) buffer)->java_nio_Buffer_address;
    if (memory) {
        free(memory);
        ((obj__java_nio_ByteBuffer *) buffer)->java_nio_Buffer_address = 0;
    }
}

JAVA_OBJECT com_badlogic_gdx_utils_BufferUtils_newDisposableByteBuffer___int_R_java_nio_ByteBuffer(CODENAME_ONE_THREAD_STATE, JAVA_INT __cn1Arg1) {
    return java_nio_ByteBuffer_allocateDirect___int_R_java_nio_ByteBuffer(threadStateData, __cn1Arg1);
}

JAVA_LONG com_badlogic_gdx_utils_BufferUtils_getBufferAddress___java_nio_Buffer_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT buffer) {
    return ((obj__java_nio_Buffer *) buffer)->java_nio_Buffer_address;
}

JAVA_VOID com_badlogic_gdx_utils_BufferUtils_clear___java_nio_ByteBuffer_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT buffer, JAVA_INT numBytes) {
    memset((void *) ((obj__java_nio_ByteBuffer *) buffer)->java_nio_Buffer_address, 0, numBytes);
}

JAVA_VOID com_badlogic_gdx_utils_BufferUtils_copyJni___float_1ARRAY_java_nio_Buffer_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT src, JAVA_OBJECT dst, JAVA_INT numFloats, JAVA_INT offset) {
    memcpy((float *) ((obj__java_nio_Buffer *) dst)->java_nio_Buffer_address, (float *) ((JAVA_ARRAY) src)->data + offset, numFloats << 2);
}

JAVA_VOID com_badlogic_gdx_utils_BufferUtils_copyJni___byte_1ARRAY_int_java_nio_Buffer_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT src, JAVA_INT srcOffset, JAVA_OBJECT dst, JAVA_INT dstOffset, JAVA_INT numBytes) {
    memcpy((char *) ((obj__java_nio_Buffer *) dst)->java_nio_Buffer_address + dstOffset, (JAVA_ARRAY_BYTE *) ((JAVA_ARRAY) src)->data + srcOffset, numBytes);
}

JAVA_VOID com_badlogic_gdx_utils_BufferUtils_copyJni___char_1ARRAY_int_java_nio_Buffer_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT src, JAVA_INT srcOffset, JAVA_OBJECT dst, JAVA_INT dstOffset, JAVA_INT numBytes) {
    memcpy((char *) ((obj__java_nio_Buffer *) dst)->java_nio_Buffer_address + dstOffset, (JAVA_ARRAY_CHAR *) ((JAVA_ARRAY) src)->data + srcOffset, numBytes);
}

JAVA_VOID com_badlogic_gdx_utils_BufferUtils_copyJni___short_1ARRAY_int_java_nio_Buffer_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT src, JAVA_INT srcOffset, JAVA_OBJECT dst, JAVA_INT dstOffset, JAVA_INT numBytes) {
    memcpy((char *) ((obj__java_nio_Buffer *) dst)->java_nio_Buffer_address + dstOffset, (JAVA_ARRAY_SHORT *) ((JAVA_ARRAY) src)->data + srcOffset, numBytes);
}

JAVA_VOID com_badlogic_gdx_utils_BufferUtils_copyJni___int_1ARRAY_int_java_nio_Buffer_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT src, JAVA_INT srcOffset, JAVA_OBJECT dst, JAVA_INT dstOffset, JAVA_INT numBytes) {
    memcpy((char *) ((obj__java_nio_Buffer *) dst)->java_nio_Buffer_address + dstOffset, (JAVA_ARRAY_INT *) ((JAVA_ARRAY) src)->data + srcOffset, numBytes);
}

JAVA_VOID com_badlogic_gdx_utils_BufferUtils_copyJni___long_1ARRAY_int_java_nio_Buffer_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT src, JAVA_INT srcOffset, JAVA_OBJECT dst, JAVA_INT dstOffset, JAVA_INT numBytes) {
    memcpy((char *) ((obj__java_nio_Buffer *) dst)->java_nio_Buffer_address + dstOffset, (JAVA_ARRAY_LONG *) ((JAVA_ARRAY) src)->data + srcOffset, numBytes);
}

JAVA_VOID com_badlogic_gdx_utils_BufferUtils_copyJni___float_1ARRAY_int_java_nio_Buffer_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT src, JAVA_INT srcOffset, JAVA_OBJECT dst, JAVA_INT dstOffset, JAVA_INT numBytes) {
    memcpy((char *) ((obj__java_nio_Buffer *) dst)->java_nio_Buffer_address + dstOffset, (JAVA_ARRAY_FLOAT *) ((JAVA_ARRAY) src)->data + srcOffset, numBytes);
}

JAVA_VOID com_badlogic_gdx_utils_BufferUtils_copyJni___double_1ARRAY_int_java_nio_Buffer_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT src, JAVA_INT srcOffset, JAVA_OBJECT dst, JAVA_INT dstOffset, JAVA_INT numBytes) {
    memcpy((char *) ((obj__java_nio_Buffer *) dst)->java_nio_Buffer_address + dstOffset, (JAVA_ARRAY_DOUBLE *) ((JAVA_ARRAY) src)->data + srcOffset, numBytes);
}

JAVA_VOID com_badlogic_gdx_utils_BufferUtils_copyJni___java_nio_Buffer_int_java_nio_Buffer_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT src, JAVA_INT srcOffset, JAVA_OBJECT dst, JAVA_INT dstOffset, JAVA_INT numBytes) {
    memcpy((char *) ((obj__java_nio_Buffer *) dst)->java_nio_Buffer_address + dstOffset, (char *) ((obj__java_nio_Buffer *) src)->java_nio_Buffer_address + srcOffset, numBytes);
}

JAVA_VOID com_badlogic_gdx_utils_BufferUtils_transformV4M4Jni___java_nio_Buffer_int_int_float_1ARRAY_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT data, JAVA_INT strideInBytes, JAVA_INT count, JAVA_OBJECT matrix, JAVA_INT offsetInBytes) {
    transform<4, 4>((float *) ((obj__java_nio_Buffer *) data)->java_nio_Buffer_address, strideInBytes / 4, count, (float *) ((JAVA_ARRAY) matrix)->data, offsetInBytes / 4);
}

JAVA_VOID com_badlogic_gdx_utils_BufferUtils_transformV4M4Jni___float_1ARRAY_int_int_float_1ARRAY_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT data, JAVA_INT strideInBytes, JAVA_INT count, JAVA_OBJECT matrix, JAVA_INT offsetInBytes) {
    transform<4, 4>((float *) ((JAVA_ARRAY) data)->data, strideInBytes / 4, count, (float *) ((JAVA_ARRAY) matrix)->data, offsetInBytes / 4);
}

JAVA_VOID com_badlogic_gdx_utils_BufferUtils_transformV3M4Jni___java_nio_Buffer_int_int_float_1ARRAY_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT data, JAVA_INT strideInBytes, JAVA_INT count, JAVA_OBJECT matrix, JAVA_INT offsetInBytes) {
    transform<3, 4>((float *) ((obj__java_nio_Buffer *) data)->java_nio_Buffer_address, strideInBytes / 4, count, (float *) ((JAVA_ARRAY) matrix)->data, offsetInBytes / 4);
}

JAVA_VOID com_badlogic_gdx_utils_BufferUtils_transformV3M4Jni___float_1ARRAY_int_int_float_1ARRAY_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT data, JAVA_INT strideInBytes, JAVA_INT count, JAVA_OBJECT matrix, JAVA_INT offsetInBytes) {
    transform<3, 4>((float *) ((JAVA_ARRAY) data)->data, strideInBytes / 4, count, (float *) ((JAVA_ARRAY) matrix)->data, offsetInBytes / 4);
}

JAVA_VOID com_badlogic_gdx_utils_BufferUtils_transformV2M4Jni___java_nio_Buffer_int_int_float_1ARRAY_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT data, JAVA_INT strideInBytes, JAVA_INT count, JAVA_OBJECT matrix, JAVA_INT offsetInBytes) {
    transform<2, 4>((float *) ((obj__java_nio_Buffer *) data)->java_nio_Buffer_address, strideInBytes / 4, count, (float *) ((JAVA_ARRAY) matrix)->data, offsetInBytes / 4);
}

JAVA_VOID com_badlogic_gdx_utils_BufferUtils_transformV2M4Jni___float_1ARRAY_int_int_float_1ARRAY_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT data, JAVA_INT strideInBytes, JAVA_INT count, JAVA_OBJECT matrix, JAVA_INT offsetInBytes) {
    transform<2, 4>((float *) ((JAVA_ARRAY) data)->data, strideInBytes / 4, count, (float *) ((JAVA_ARRAY) matrix)->data, offsetInBytes / 4);
}

JAVA_VOID com_badlogic_gdx_utils_BufferUtils_transformV3M3Jni___java_nio_Buffer_int_int_float_1ARRAY_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT data, JAVA_INT strideInBytes, JAVA_INT count, JAVA_OBJECT matrix, JAVA_INT offsetInBytes) {
    transform<3, 3>((float *) ((obj__java_nio_Buffer *) data)->java_nio_Buffer_address, strideInBytes / 4, count, (float *) ((JAVA_ARRAY) matrix)->data, offsetInBytes / 4);
}

JAVA_VOID com_badlogic_gdx_utils_BufferUtils_transformV3M3Jni___float_1ARRAY_int_int_float_1ARRAY_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT data, JAVA_INT strideInBytes, JAVA_INT count, JAVA_OBJECT matrix, JAVA_INT offsetInBytes) {
    transform<3, 3>((float *) ((JAVA_ARRAY) data)->data, strideInBytes / 4, count, (float *) ((JAVA_ARRAY) matrix)->data, offsetInBytes / 4);
}

JAVA_VOID com_badlogic_gdx_utils_BufferUtils_transformV2M3Jni___java_nio_Buffer_int_int_float_1ARRAY_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT data, JAVA_INT strideInBytes, JAVA_INT count, JAVA_OBJECT matrix, JAVA_INT offsetInBytes) {
    transform<2, 3>((float *) ((obj__java_nio_Buffer *) data)->java_nio_Buffer_address, strideInBytes / 4, count, (float *) ((JAVA_ARRAY) matrix)->data, offsetInBytes / 4);
}

JAVA_VOID com_badlogic_gdx_utils_BufferUtils_transformV2M3Jni___float_1ARRAY_int_int_float_1ARRAY_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT data, JAVA_INT strideInBytes, JAVA_INT count, JAVA_OBJECT matrix, JAVA_INT offsetInBytes) {
    transform<2, 3>((float *) ((JAVA_ARRAY) data)->data, strideInBytes / 4, count, (float *) ((JAVA_ARRAY) matrix)->data, offsetInBytes / 4);
}

JAVA_LONG com_badlogic_gdx_utils_BufferUtils_find___java_nio_Buffer_int_int_java_nio_Buffer_int_int_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT vertex, JAVA_INT vertexOffsetInBytes, JAVA_INT strideInBytes, JAVA_OBJECT vertices, JAVA_INT verticesOffsetInBytes, JAVA_INT numVertices) {
    return find(&((float *) ((obj__java_nio_Buffer *) vertex)->java_nio_Buffer_address)[vertexOffsetInBytes / 4], strideInBytes / 4, &((float *) ((obj__java_nio_Buffer *) vertices)->java_nio_Buffer_address)[verticesOffsetInBytes / 4], numVertices);
}

JAVA_LONG com_badlogic_gdx_utils_BufferUtils_find___float_1ARRAY_int_int_java_nio_Buffer_int_int_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT vertex, JAVA_INT vertexOffsetInBytes, JAVA_INT strideInBytes, JAVA_OBJECT vertices, JAVA_INT verticesOffsetInBytes, JAVA_INT numVertices) {
    return find(&((float *) ((JAVA_ARRAY) vertex)->data)[vertexOffsetInBytes / 4], strideInBytes / 4, &((float *) ((obj__java_nio_Buffer *) vertices)->java_nio_Buffer_address)[verticesOffsetInBytes / 4], numVertices);
}

JAVA_LONG com_badlogic_gdx_utils_BufferUtils_find___java_nio_Buffer_int_int_float_1ARRAY_int_int_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT vertex, JAVA_INT vertexOffsetInBytes, JAVA_INT strideInBytes, JAVA_OBJECT vertices, JAVA_INT verticesOffsetInBytes, JAVA_INT numVertices) {
    return find(&((float *) ((obj__java_nio_Buffer *) vertex)->java_nio_Buffer_address)[vertexOffsetInBytes / 4], strideInBytes / 4, &((float *) ((JAVA_ARRAY) vertices)->data)[verticesOffsetInBytes / 4], numVertices);
}

JAVA_LONG com_badlogic_gdx_utils_BufferUtils_find___float_1ARRAY_int_int_float_1ARRAY_int_int_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT vertex, JAVA_INT vertexOffsetInBytes, JAVA_INT strideInBytes, JAVA_OBJECT vertices, JAVA_INT verticesOffsetInBytes, JAVA_INT numVertices) {
    return find(&((float *) ((JAVA_ARRAY) vertex)->data)[vertexOffsetInBytes / 4], strideInBytes / 4, &((float *) ((JAVA_ARRAY) vertices)->data)[verticesOffsetInBytes / 4], numVertices);
}

JAVA_LONG com_badlogic_gdx_utils_BufferUtils_find___java_nio_Buffer_int_int_java_nio_Buffer_int_int_float_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT vertex, JAVA_INT vertexOffsetInBytes, JAVA_INT strideInBytes, JAVA_OBJECT vertices, JAVA_INT verticesOffsetInBytes, JAVA_INT numVertices, JAVA_FLOAT epsilon) {
    return find(&((float *) ((obj__java_nio_Buffer *) vertex)->java_nio_Buffer_address)[vertexOffsetInBytes / 4], strideInBytes / 4, &((float *) ((obj__java_nio_Buffer *) vertices)->java_nio_Buffer_address)[verticesOffsetInBytes / 4], numVertices, epsilon);
}

JAVA_LONG com_badlogic_gdx_utils_BufferUtils_find___float_1ARRAY_int_int_java_nio_Buffer_int_int_float_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT vertex, JAVA_INT vertexOffsetInBytes, JAVA_INT strideInBytes, JAVA_OBJECT vertices, JAVA_INT verticesOffsetInBytes, JAVA_INT numVertices, JAVA_FLOAT epsilon) {
    return find(&((float *) ((JAVA_ARRAY) vertex)->data)[vertexOffsetInBytes / 4], strideInBytes / 4, &((float *) ((obj__java_nio_Buffer *) vertices)->java_nio_Buffer_address)[verticesOffsetInBytes / 4], numVertices, epsilon);
}

JAVA_LONG com_badlogic_gdx_utils_BufferUtils_find___java_nio_Buffer_int_int_float_1ARRAY_int_int_float_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT vertex, JAVA_INT vertexOffsetInBytes, JAVA_INT strideInBytes, JAVA_OBJECT vertices, JAVA_INT verticesOffsetInBytes, JAVA_INT numVertices, JAVA_FLOAT epsilon) {
    return find(&((float *) ((obj__java_nio_Buffer *) vertex)->java_nio_Buffer_address)[vertexOffsetInBytes / 4], strideInBytes / 4, &((float *) ((JAVA_ARRAY) vertices)->data)[verticesOffsetInBytes / 4], numVertices, epsilon);
}

JAVA_LONG com_badlogic_gdx_utils_BufferUtils_find___float_1ARRAY_int_int_float_1ARRAY_int_int_float_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT vertex, JAVA_INT vertexOffsetInBytes, JAVA_INT strideInBytes, JAVA_OBJECT vertices, JAVA_INT verticesOffsetInBytes, JAVA_INT numVertices, JAVA_FLOAT epsilon) {
    return find(&((float *) ((JAVA_ARRAY) vertex)->data)[vertexOffsetInBytes / 4], strideInBytes / 4, &((float *) ((JAVA_ARRAY) vertices)->data)[verticesOffsetInBytes / 4], numVertices, epsilon);
}

JAVA_VOID com_badlogic_gdx_math_Matrix4_mulVec___float_1ARRAY_float_1ARRAY_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT mat, JAVA_OBJECT vecs, JAVA_INT offset, JAVA_INT numVecs, JAVA_INT stride) {
    auto vecPtr = (float *) ((JAVA_ARRAY) vecs)->data + offset;
    for (int i = 0; i < numVecs; i++) {
        matrix4_mulVec((float *) ((JAVA_ARRAY) mat)->data, vecPtr);
        vecPtr += stride;
    }
}

JAVA_VOID com_badlogic_gdx_math_Matrix4_prj___float_1ARRAY_float_1ARRAY_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT mat, JAVA_OBJECT vecs, JAVA_INT offset, JAVA_INT numVecs, JAVA_INT stride) {
    auto vecPtr = (float *) ((JAVA_ARRAY) vecs)->data + offset;
    for (int i = 0; i < numVecs; i++) {
        matrix4_proj((float *) ((JAVA_ARRAY) mat)->data, vecPtr);
        vecPtr += stride;
    }
}

JAVA_VOID com_badlogic_gdx_math_Matrix4_rot___float_1ARRAY_float_1ARRAY_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT mat, JAVA_OBJECT vecs, JAVA_INT offset, JAVA_INT numVecs, JAVA_INT stride) {
    auto vecPtr = (float *) ((JAVA_ARRAY) vecs)->data + offset;
    for (int i = 0; i < numVecs; i++) {
        matrix4_rot((float *) ((JAVA_ARRAY) mat)->data, vecPtr);
        vecPtr += stride;
    }
}

JAVA_OBJECT com_badlogic_gdx_graphics_g2d_Gdx2DPixmap_load___long_1ARRAY_byte_1ARRAY_int_int_R_java_nio_ByteBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT nativeData, JAVA_OBJECT buffer, JAVA_INT offset, JAVA_INT len) {
    auto pixmap = gdx2d_load((unsigned char *) ((JAVA_ARRAY) buffer)->data + offset, len);
    if (!pixmap)
        return nullptr;
    auto pixelBuffer = __NEW_java_nio_ByteBuffer(threadStateData);
    java_nio_ByteBuffer___INIT_____long_int_boolean(threadStateData, pixelBuffer, (JAVA_LONG) pixmap->pixels, (JAVA_INT) (pixmap->width * pixmap->height * gdx2d_bytes_per_pixel(pixmap->format)), false);
    auto nativeDataPtr = (JAVA_ARRAY_LONG *) ((JAVA_ARRAY) nativeData)->data;
    nativeDataPtr[0] = (JAVA_ARRAY_LONG) pixmap;
    nativeDataPtr[1] = pixmap->width;
    nativeDataPtr[2] = pixmap->height;
    nativeDataPtr[3] = pixmap->format;
    return pixelBuffer;
}

JAVA_OBJECT com_badlogic_gdx_graphics_g2d_Gdx2DPixmap_loadByteBuffer___long_1ARRAY_java_nio_ByteBuffer_int_int_R_java_nio_ByteBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT nativeData, JAVA_OBJECT buffer, JAVA_INT offset, JAVA_INT len) {
    auto pixmap = gdx2d_load((unsigned char *) ((obj__java_nio_ByteBuffer *) buffer)->java_nio_Buffer_address + offset, len);
    if (!pixmap)
        return nullptr;
    auto pixelBuffer = __NEW_java_nio_ByteBuffer(threadStateData);
    java_nio_ByteBuffer___INIT_____long_int_boolean(threadStateData, pixelBuffer, (JAVA_LONG) pixmap->pixels, (JAVA_INT) (pixmap->width * pixmap->height * gdx2d_bytes_per_pixel(pixmap->format)), false);
    auto nativeDataPtr = (JAVA_ARRAY_LONG *) ((JAVA_ARRAY) nativeData)->data;
    nativeDataPtr[0] = (JAVA_ARRAY_LONG) pixmap;
    nativeDataPtr[1] = pixmap->width;
    nativeDataPtr[2] = pixmap->height;
    nativeDataPtr[3] = pixmap->format;
    return pixelBuffer;
}

JAVA_OBJECT com_badlogic_gdx_graphics_g2d_Gdx2DPixmap_newPixmap___long_1ARRAY_int_int_int_R_java_nio_ByteBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT nativeData, JAVA_INT width, JAVA_INT height, JAVA_INT format) {
    auto pixmap = gdx2d_new(width, height, format);
    if (!pixmap)
        return nullptr;
    auto pixelBuffer = __NEW_java_nio_ByteBuffer(threadStateData);
    java_nio_ByteBuffer___INIT_____long_int_boolean(threadStateData, pixelBuffer, (JAVA_LONG) pixmap->pixels, (JAVA_INT) (pixmap->width * pixmap->height * gdx2d_bytes_per_pixel(pixmap->format)), false);
    auto nativeDataPtr = (JAVA_ARRAY_LONG *) ((JAVA_ARRAY) nativeData)->data;
    nativeDataPtr[0] = (JAVA_ARRAY_LONG) pixmap;
    nativeDataPtr[1] = pixmap->width;
    nativeDataPtr[2] = pixmap->height;
    nativeDataPtr[3] = pixmap->format;
    return pixelBuffer;
}

JAVA_VOID com_badlogic_gdx_graphics_g2d_Gdx2DPixmap_free___long(CODENAME_ONE_THREAD_STATE, JAVA_LONG pixmap) {
    gdx2d_free((gdx2d_pixmap *) pixmap);
}

JAVA_VOID com_badlogic_gdx_graphics_g2d_Gdx2DPixmap_clear___long_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG pixmap, JAVA_INT color) {
    gdx2d_clear((gdx2d_pixmap *) pixmap, color);
}

JAVA_VOID com_badlogic_gdx_graphics_g2d_Gdx2DPixmap_setPixel___long_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG pixmap, JAVA_INT x, JAVA_INT y, JAVA_INT color) {
    gdx2d_set_pixel((gdx2d_pixmap *) pixmap, x, y, color);
}

JAVA_INT com_badlogic_gdx_graphics_g2d_Gdx2DPixmap_getPixel___long_int_int_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG pixmap, JAVA_INT x, JAVA_INT y) {
    return (JAVA_INT) gdx2d_get_pixel((gdx2d_pixmap *) pixmap, x, y);
}

JAVA_VOID com_badlogic_gdx_graphics_g2d_Gdx2DPixmap_drawLine___long_int_int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG pixmap, JAVA_INT x, JAVA_INT y, JAVA_INT x2, JAVA_INT y2, JAVA_INT color) {
    gdx2d_draw_line((gdx2d_pixmap *) pixmap, x, y, x2, y2, color);
}

JAVA_VOID com_badlogic_gdx_graphics_g2d_Gdx2DPixmap_drawRect___long_int_int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG pixmap, JAVA_INT x, JAVA_INT y, JAVA_INT width, JAVA_INT height, JAVA_INT color) {
    gdx2d_draw_rect((gdx2d_pixmap *) pixmap, x, y, width, height, color);
}

JAVA_VOID com_badlogic_gdx_graphics_g2d_Gdx2DPixmap_drawCircle___long_int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG pixmap, JAVA_INT x, JAVA_INT y, JAVA_INT radius, JAVA_INT color) {
    gdx2d_draw_circle((gdx2d_pixmap *) pixmap, x, y, radius, color);
}

JAVA_VOID com_badlogic_gdx_graphics_g2d_Gdx2DPixmap_fillRect___long_int_int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG pixmap, JAVA_INT x, JAVA_INT y, JAVA_INT width, JAVA_INT height, JAVA_INT color) {
    gdx2d_fill_rect((gdx2d_pixmap *) pixmap, x, y, width, height, color);
}

JAVA_VOID com_badlogic_gdx_graphics_g2d_Gdx2DPixmap_fillCircle___long_int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG pixmap, JAVA_INT x, JAVA_INT y, JAVA_INT radius, JAVA_INT color) {
    gdx2d_fill_circle((gdx2d_pixmap *) pixmap, x, y, radius, color);
}

JAVA_VOID com_badlogic_gdx_graphics_g2d_Gdx2DPixmap_fillTriangle___long_int_int_int_int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG pixmap, JAVA_INT x1, JAVA_INT y1, JAVA_INT x2, JAVA_INT y2, JAVA_INT x3, JAVA_INT y3, JAVA_INT color) {
    gdx2d_fill_triangle((gdx2d_pixmap *) pixmap, x1, y1, x2, y2, x3, y3, color);
}

JAVA_VOID com_badlogic_gdx_graphics_g2d_Gdx2DPixmap_drawPixmap___long_long_int_int_int_int_int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG src, JAVA_LONG dst, JAVA_INT srcX, JAVA_INT srcY, JAVA_INT srcWidth, JAVA_INT srcHeight, JAVA_INT dstX, JAVA_INT dstY, JAVA_INT dstWidth, JAVA_INT dstHeight) {
    gdx2d_draw_pixmap((gdx2d_pixmap *) src, (gdx2d_pixmap *) dst, srcX, srcY, srcWidth, srcHeight, dstX, dstY, dstWidth, dstHeight);
}

JAVA_VOID com_badlogic_gdx_graphics_g2d_Gdx2DPixmap_setBlend___long_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG src, JAVA_INT blend) {
    gdx2d_set_blend((gdx2d_pixmap *) src, blend);
}

JAVA_VOID com_badlogic_gdx_graphics_g2d_Gdx2DPixmap_setScale___long_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG src, JAVA_INT scale) {
    gdx2d_set_scale((gdx2d_pixmap *) src, scale);
}

JAVA_OBJECT com_badlogic_gdx_graphics_g2d_Gdx2DPixmap_getFailureReason___R_java_lang_String(CODENAME_ONE_THREAD_STATE) {
    return fromNativeString(threadStateData, gdx2d_get_failure_reason());
}

JAVA_INT com_badlogic_gdx_graphics_glutils_ETC1_getCompressedDataSize___int_int_R_int(CODENAME_ONE_THREAD_STATE, JAVA_INT width, JAVA_INT height) {
    return (JAVA_INT) etc1_get_encoded_data_size(width, height);
}

JAVA_VOID com_badlogic_gdx_graphics_glutils_ETC1_formatHeader___java_nio_ByteBuffer_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT header, JAVA_INT offset, JAVA_INT width, JAVA_INT height) {
    etc1_pkm_format_header((etc1_byte *) ((obj__java_nio_ByteBuffer *) header)->java_nio_Buffer_address + offset, width, height);
}

JAVA_INT com_badlogic_gdx_graphics_glutils_ETC1_getWidthPKM___java_nio_ByteBuffer_int_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT header, JAVA_INT offset) {
    return (JAVA_INT) etc1_pkm_get_width((etc1_byte *) ((obj__java_nio_ByteBuffer *) header)->java_nio_Buffer_address + offset);
}

JAVA_INT com_badlogic_gdx_graphics_glutils_ETC1_getHeightPKM___java_nio_ByteBuffer_int_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT header, JAVA_INT offset) {
    return (JAVA_INT) etc1_pkm_get_height((etc1_byte *) ((obj__java_nio_ByteBuffer *) header)->java_nio_Buffer_address + offset);
}

JAVA_BOOLEAN com_badlogic_gdx_graphics_glutils_ETC1_isValidPKM___java_nio_ByteBuffer_int_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT header, JAVA_INT offset) {
    return etc1_pkm_is_valid((etc1_byte *) ((obj__java_nio_ByteBuffer *) header)->java_nio_Buffer_address + offset);
}

JAVA_VOID com_badlogic_gdx_graphics_glutils_ETC1_decodeImage___java_nio_ByteBuffer_int_java_nio_ByteBuffer_int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT compressedData, JAVA_INT offset, JAVA_OBJECT decodedData, JAVA_INT offsetDec, JAVA_INT width, JAVA_INT height, JAVA_INT pixelSize) {
    etc1_decode_image((etc1_byte *) ((obj__java_nio_ByteBuffer *) compressedData)->java_nio_Buffer_address + offset, (etc1_byte *) ((obj__java_nio_ByteBuffer *) decodedData)->java_nio_Buffer_address + offsetDec, width, height, pixelSize, width * pixelSize);
}

JAVA_OBJECT com_badlogic_gdx_graphics_glutils_ETC1_encodeImage___java_nio_ByteBuffer_int_int_int_int_R_java_nio_ByteBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT imageData, JAVA_INT offset, JAVA_INT width, JAVA_INT height, JAVA_INT pixelSize) {
    auto compressedSize = etc1_get_encoded_data_size(width, height);
    auto compressedData = (etc1_byte *) malloc(compressedSize);
    etc1_encode_image((etc1_byte *) ((obj__java_nio_ByteBuffer *) imageData)->java_nio_Buffer_address + offset, width, height, pixelSize, width * pixelSize, compressedData);
    auto pixelBuffer = __NEW_java_nio_ByteBuffer(threadStateData);
    java_nio_ByteBuffer___INIT_____long_int(threadStateData, pixelBuffer, (JAVA_LONG) compressedData, (JAVA_INT) compressedSize);
    return pixelBuffer;
}

JAVA_OBJECT com_badlogic_gdx_graphics_glutils_ETC1_encodeImagePKM___java_nio_ByteBuffer_int_int_int_int_R_java_nio_ByteBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT imageData, JAVA_INT offset, JAVA_INT width, JAVA_INT height, JAVA_INT pixelSize) {
    auto compressedSize = etc1_get_encoded_data_size(width, height);
    auto compressed = (etc1_byte *) malloc(compressedSize + ETC_PKM_HEADER_SIZE);
    etc1_pkm_format_header(compressed, width, height);
    etc1_encode_image((etc1_byte *) ((obj__java_nio_ByteBuffer *) imageData)->java_nio_Buffer_address + offset, width, height, pixelSize, width * pixelSize, compressed + ETC_PKM_HEADER_SIZE);
    auto pixelBuffer = __NEW_java_nio_ByteBuffer(threadStateData);
    java_nio_ByteBuffer___INIT_____long_int(threadStateData, pixelBuffer, (JAVA_LONG) compressed, (JAVA_INT) compressedSize);
    return pixelBuffer;
}

JAVA_INT com_thelogicmaster_switchgdx_SwitchGraphics_getWidth___R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject) {
    return 1280;
}

JAVA_INT com_thelogicmaster_switchgdx_SwitchGraphics_getHeight___R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject) {
    return 720;
}

JAVA_INT com_thelogicmaster_switchgdx_SwitchControllerManager_getButtons___R_int(CODENAME_ONE_THREAD_STATE) {
#ifdef __SWITCH__
    return padGetButtons(&pad);
#else
    return buttons;
#endif
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchControllerManager_getAxes___float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT axes) {
    auto array = (float *) ((JAVA_ARRAY) axes)->data;
#ifdef __SWITCH__
    auto stickLeft = padGetStickPos(&pad, 0);
    auto stickRight = padGetStickPos(&pad, 1);
    array[0] = (float)stickLeft.x / JOYSTICK_MAX;
    array[1] = (float)stickLeft.y / JOYSTICK_MAX;
    array[2] = (float)stickRight.x / JOYSTICK_MAX;
    array[3] = (float)stickRight.y / JOYSTICK_MAX;
#else
    memcpy(array, joysticks, sizeof(joysticks));
#endif
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchInput_getTouchData___int_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT touchData) {
    memcpy((void *) ((JAVA_ARRAY) touchData)->data, touches, sizeof(touches));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchInput_getTextInput___com_badlogic_gdx_Input_TextInputListener_java_lang_String_java_lang_String_java_lang_String_com_badlogic_gdx_Input_OnscreenKeyboardType(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_OBJECT listener, JAVA_OBJECT title, JAVA_OBJECT text, JAVA_OBJECT hint, JAVA_OBJECT type) {
#ifdef __SWITCH__
    Result rc;
    SwkbdConfig kbd;
    char buffer[256];
    rc = swkbdCreate(&kbd, 0);
    if (rc)
        goto failed;
    swkbdConfigMakePresetDefault(&kbd);
    swkbdConfigSetHeaderText(&kbd, toNativeString(threadStateData, title));
    swkbdConfigSetGuideText(&kbd, toNativeString(threadStateData, text));
    swkbdConfigSetInitialText(&kbd, toNativeString(threadStateData, hint));
    swkbdConfigSetStringLenMax(&kbd, sizeof(buffer) - 1);
    rc = swkbdShow(&kbd, buffer, sizeof(buffer));
    if (rc)
        goto failed;
    com_badlogic_gdx_Input_TextInputListener_input___java_lang_String(threadStateData, listener, fromNativeString(threadStateData, buffer));
    return;
#elif defined(__WINRT__)
    goto failed;
#else
    auto input = tinyfd_inputBox(toNativeString(threadStateData, title), toNativeString(threadStateData, text), "");
    if (!input)
        goto failed;
    com_badlogic_gdx_Input_TextInputListener_input___java_lang_String(threadStateData, listener, fromNativeString(threadStateData, input));
    return;
#endif
    failed:
    com_badlogic_gdx_Input_TextInputListener_canceled__(threadStateData, listener);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glActiveTexture___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT texture) {
    glActiveTexture(texture);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glBindTexture___int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT texture) {
    glBindTexture(target, texture);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glBlendFunc___int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT sfactor, JAVA_INT dfactor) {
    glBlendFunc(sfactor, dfactor);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glClear___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT mask) {
    glClear(mask);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glClearColor___float_float_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_FLOAT red, JAVA_FLOAT green, JAVA_FLOAT blue, JAVA_FLOAT alpha) {
    glClearColor(red, green, blue, alpha);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glClearDepthf___float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_FLOAT depth) {
    glClearDepthf(depth);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glClearStencil___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT s) {
    glClearStencil(s);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glColorMask___boolean_boolean_boolean_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_BOOLEAN red, JAVA_BOOLEAN green, JAVA_BOOLEAN blue, JAVA_BOOLEAN alpha) {
    glColorMask(red, green, blue, alpha);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glCompressedTexImage2D___int_int_int_int_int_int_int_java_nio_Buffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT level, JAVA_INT internalformat, JAVA_INT width, JAVA_INT height, JAVA_INT border, JAVA_INT imageSize, JAVA_OBJECT data) {
    glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, (void *) getBufferAddress(data));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glCompressedTexSubImage2D___int_int_int_int_int_int_int_int_java_nio_Buffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT level, JAVA_INT xoffset, JAVA_INT yoffset, JAVA_INT width, JAVA_INT height, JAVA_INT format, JAVA_INT imageSize, JAVA_OBJECT data) {
    glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, (void *) getBufferAddress(data));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glCopyTexImage2D___int_int_int_int_int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT level, JAVA_INT internalformat, JAVA_INT x, JAVA_INT y, JAVA_INT width, JAVA_INT height, JAVA_INT border) {
    glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glCopyTexSubImage2D___int_int_int_int_int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT level, JAVA_INT xoffset, JAVA_INT yoffset, JAVA_INT x, JAVA_INT y, JAVA_INT width, JAVA_INT height) {
    glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glCullFace___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT mode) {
    glCullFace(mode);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glDeleteTextures___int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT n, JAVA_OBJECT textures) {
    glDeleteTextures(n, (GLuint *) getBufferAddress(textures));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glDeleteTexture___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT texture) {
    glDeleteTextures(1, (GLuint *) &texture);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glDepthFunc___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT func) {
    glDepthFunc(func);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glDepthMask___boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_BOOLEAN flag) {
    glDepthMask(flag);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glDepthRangef___float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_FLOAT zNear, JAVA_FLOAT zFar) {
    glDepthRangef(zNear, zFar);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glDisable___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT cap) {
    glDisable(cap);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glDrawArrays___int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT mode, JAVA_INT first, JAVA_INT count) {
    glDrawArrays(mode, first, count);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glDrawElements___int_int_int_java_nio_Buffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT mode, JAVA_INT count, JAVA_INT type, JAVA_OBJECT indices) {
    glDrawElements(mode, count, type, (void *) getBufferAddress(indices));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glEnable___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT cap) {
    glEnable(cap);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glFinish__(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject) {
    glFinish();
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glFlush__(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject) {
    glFlush();
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glFrontFace___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT mode) {
    glFrontFace(mode);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGenTextures___int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT n, JAVA_OBJECT textures) {
    glGenTextures(n, (GLuint *) getBufferAddress(textures));
}

JAVA_INT com_thelogicmaster_switchgdx_SwitchGL_glGenTexture___R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject) {
    GLuint texture;
    glGenTextures(1, &texture);
    return (JAVA_INT) texture;
}

JAVA_INT com_thelogicmaster_switchgdx_SwitchGL_glGetError___R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject) {
    return (JAVA_INT) glGetError();
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGetIntegerv___int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT pname, JAVA_OBJECT params) {
    glGetIntegerv(pname, (GLint *) getBufferAddress(params));
}

JAVA_OBJECT com_thelogicmaster_switchgdx_SwitchGL_glGetString___int_R_java_lang_String(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT name) {
    return fromNativeString(threadStateData, (char *) glGetString(name));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glHint___int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT mode) {
    glHint(target, mode);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glLineWidth___float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_FLOAT width) {
    glLineWidth(width);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glPixelStorei___int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT pname, JAVA_INT param) {
    glPixelStorei(pname, param);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glPolygonOffset___float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_FLOAT factor, JAVA_FLOAT units) {
    glPolygonOffset(factor, units);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glReadPixels___int_int_int_int_int_int_java_nio_Buffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT x, JAVA_INT y, JAVA_INT width, JAVA_INT height, JAVA_INT format, JAVA_INT type, JAVA_OBJECT pixels) {
    glReadPixels(x, y, width, height, format, type, (void *) getBufferAddress(pixels));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glScissor___int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT x, JAVA_INT y, JAVA_INT width, JAVA_INT height) {
    glScissor(x, y, width, height);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glStencilFunc___int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT func, JAVA_INT ref, JAVA_INT mask) {
    glStencilFunc(func, ref, mask);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glStencilMask___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT mask) {
    glStencilMask(mask);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glStencilOp___int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT fail, JAVA_INT zfail, JAVA_INT zpass) {
    glStencilOp(fail, zfail, zpass);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glTexImage2D___int_int_int_int_int_int_int_int_java_nio_Buffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT level, JAVA_INT internalformat, JAVA_INT width, JAVA_INT height, JAVA_INT border, JAVA_INT format, JAVA_INT type, JAVA_OBJECT pixels) {
    glTexImage2D(target, level, internalformat, width, height, border, format, type, (void *) getBufferAddress(pixels));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glTexParameterf___int_int_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT pname, JAVA_FLOAT param) {
    glTexParameterf(target, pname, param);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glTexSubImage2D___int_int_int_int_int_int_int_int_java_nio_Buffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT level, JAVA_INT xoffset, JAVA_INT yoffset, JAVA_INT width, JAVA_INT height, JAVA_INT format, JAVA_INT type, JAVA_OBJECT pixels) {
    glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, (void *) getBufferAddress(pixels));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glViewport___int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT x, JAVA_INT y, JAVA_INT width, JAVA_INT height) {
    glViewport(x, y, width, height);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glAttachShader___int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT program, JAVA_INT shader) {
    glAttachShader(program, shader);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glBindAttribLocation___int_int_java_lang_String(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT program, JAVA_INT index, JAVA_OBJECT name) {
    glBindAttribLocation(program, index, toNativeString(threadStateData, name));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glBindBuffer___int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT buffer) {
    glBindBuffer(target, buffer);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glBindFramebuffer___int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT framebuffer) {
    glBindFramebuffer(target, framebuffer);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glBindRenderbuffer___int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT renderbuffer) {
    glBindRenderbuffer(target, renderbuffer);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glBlendColor___float_float_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_FLOAT red, JAVA_FLOAT green, JAVA_FLOAT blue, JAVA_FLOAT alpha) {
    glBlendColor(red, green, blue, alpha);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glBlendEquation___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT mode) {
    glBlendEquation(mode);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glBlendEquationSeparate___int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT modeRGB, JAVA_INT modeAlpha) {
    glBlendEquationSeparate(modeRGB, modeAlpha);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glBlendFuncSeparate___int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT srcRGB, JAVA_INT dstRGB, JAVA_INT srcAlpha, JAVA_INT dstAlpha) {
    glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glBufferData___int_int_java_nio_Buffer_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT size, JAVA_OBJECT buffer, JAVA_INT usage) {
    glBufferData(target, size, (void *) getBufferAddress(buffer), usage);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glBufferSubData___int_int_int_java_nio_Buffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT offset, JAVA_INT size, JAVA_OBJECT data) {
    glBufferSubData(target, offset, size, (void *) getBufferAddress(data));
}

JAVA_INT com_thelogicmaster_switchgdx_SwitchGL_glCheckFramebufferStatus___int_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target) {
    return (JAVA_INT) glCheckFramebufferStatus(target);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glCompileShader___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT shader) {
    glCompileShader(shader);
}

JAVA_INT com_thelogicmaster_switchgdx_SwitchGL_glCreateProgram___R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject) {
    return (int) glCreateProgram();
}

JAVA_INT com_thelogicmaster_switchgdx_SwitchGL_glCreateShader___int_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT type) {
    return (int) glCreateShader(type);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glDeleteBuffer___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT buffer) {
    glDeleteBuffers(1, (GLuint *) &buffer);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glDeleteBuffers___int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT n, JAVA_OBJECT buffers) {
    glDeleteBuffers(n, (GLuint *) getBufferAddress(buffers));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glDeleteFramebuffer___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT framebuffer) {
    glDeleteFramebuffers(1, (GLuint *) &framebuffer);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glDeleteFramebuffers___int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT n, JAVA_OBJECT framebuffers) {
    glDeleteFramebuffers(n, (GLuint *) getBufferAddress(framebuffers));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glDeleteProgram___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT program) {
    glDeleteProgram(program);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glDeleteRenderbuffer___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT renderbuffer) {
    glDeleteRenderbuffers(1, (GLuint *) &renderbuffer);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glDeleteRenderbuffers___int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT n, JAVA_OBJECT renderbuffers) {
    glDeleteRenderbuffers(n, (GLuint *) getBufferAddress(renderbuffers));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glDeleteShader___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT shader) {
    glDeleteShader(shader);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glDetachShader___int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT program, JAVA_INT shader) {
    glDetachShader(program, shader);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glDisableVertexAttribArray___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT index) {
    glDisableVertexAttribArray(index);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glDrawElements___int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT mode, JAVA_INT count, JAVA_INT type, JAVA_INT indices) {
    glDrawElements(mode, count, type, (void *) (JAVA_LONG) indices);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glEnableVertexAttribArray___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT index) {
    glEnableVertexAttribArray(index);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glFramebufferRenderbuffer___int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT attachment, JAVA_INT renderbuffertarget, JAVA_INT renderbuffer) {
    glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glFramebufferTexture2D___int_int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT attachment, JAVA_INT textarget, JAVA_INT texture, JAVA_INT level) {
    glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

JAVA_INT com_thelogicmaster_switchgdx_SwitchGL_glGenBuffer___R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    return (JAVA_INT) buffer;
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGenBuffers___int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT n, JAVA_OBJECT buffers) {
    glGenBuffers(n, (GLuint *) getBufferAddress(buffers));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGenerateMipmap___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target) {
    glGenerateMipmap(target);
}

JAVA_INT com_thelogicmaster_switchgdx_SwitchGL_glGenFramebuffer___R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject) {
    GLuint buffer;
    glGenFramebuffers(1, &buffer);
    return (JAVA_INT) buffer;
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGenFramebuffers___int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT n, JAVA_OBJECT framebuffers) {
    glGenFramebuffers(n, (GLuint *) getBufferAddress(framebuffers));
}

JAVA_INT com_thelogicmaster_switchgdx_SwitchGL_glGenRenderbuffer___R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject) {
    GLuint buffer;
    glGenRenderbuffers(1, &buffer);
    return (JAVA_INT) buffer;
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGenRenderbuffers___int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT n, JAVA_OBJECT renderbuffers) {
    glGenRenderbuffers(n, (GLuint *) getBufferAddress(renderbuffers));
}

JAVA_OBJECT com_thelogicmaster_switchgdx_SwitchGL_glGetActiveAttrib___int_int_java_nio_IntBuffer_java_nio_IntBuffer_R_java_lang_String(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT program, JAVA_INT index, JAVA_OBJECT size, JAVA_OBJECT type) {
    char buffer[64];
    glGetActiveAttrib(program, index, 63, nullptr, (GLint *) getBufferAddress(size), (GLenum *) getBufferAddress(type), buffer);
    return fromNativeString(threadStateData, buffer);
}

JAVA_OBJECT com_thelogicmaster_switchgdx_SwitchGL_glGetActiveUniform___int_int_java_nio_IntBuffer_java_nio_IntBuffer_R_java_lang_String(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT program, JAVA_INT index, JAVA_OBJECT size, JAVA_OBJECT type) {
    char buffer[64];
    glGetActiveUniform(program, index, 63, nullptr, (GLint *) getBufferAddress(size), (GLenum *) getBufferAddress(type), buffer);
    return fromNativeString(threadStateData, buffer);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGetAttachedShaders___int_int_java_nio_Buffer_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT program, JAVA_INT maxcount, JAVA_OBJECT count, JAVA_OBJECT shaders) {
    glGetAttachedShaders(program, maxcount, (GLsizei *) getBufferAddress(count), (GLuint *) getBufferAddress(shaders));
}

JAVA_INT com_thelogicmaster_switchgdx_SwitchGL_glGetAttribLocation___int_java_lang_String_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT program, JAVA_OBJECT name) {
    return glGetAttribLocation(program, toNativeString(threadStateData, name));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGetBooleanv___int_java_nio_Buffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT pname, JAVA_OBJECT params) {
    glGetBooleanv(pname, (GLboolean *) getBufferAddress(params));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGetBufferParameteriv___int_int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT pname, JAVA_OBJECT params) {
    glGetBufferParameteriv(target, pname, (GLint *) getBufferAddress(params));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGetFloatv___int_java_nio_FloatBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT pname, JAVA_OBJECT params) {
    glGetFloatv(pname, (GLfloat *) getBufferAddress(params));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGetFramebufferAttachmentParameteriv___int_int_int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT attachment, JAVA_INT pname, JAVA_OBJECT params) {
    glGetFramebufferAttachmentParameteriv(target, attachment, pname, (GLint *) getBufferAddress(params));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGetProgramiv___int_int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT program, JAVA_INT pname, JAVA_OBJECT params) {
    glGetProgramiv(program, pname, (GLint *) getBufferAddress(params));
}

JAVA_OBJECT com_thelogicmaster_switchgdx_SwitchGL_glGetProgramInfoLog___int_R_java_lang_String(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT program) {
    char buffer[128];
    glGetProgramInfoLog(program, 127, nullptr, buffer);
    return fromNativeString(threadStateData, buffer);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGetRenderbufferParameteriv___int_int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT pname, JAVA_OBJECT params) {
    glGetRenderbufferParameteriv(target, pname, (GLint *) getBufferAddress(params));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGetShaderiv___int_int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT shader, JAVA_INT pname, JAVA_OBJECT params) {
    glGetShaderiv(shader, pname, (GLint *) getBufferAddress(params));
}

JAVA_OBJECT com_thelogicmaster_switchgdx_SwitchGL_glGetShaderInfoLog___int_R_java_lang_String(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT program) {
    char buffer[128];
    glGetShaderInfoLog(program, 127, nullptr, buffer);
    return newStringFromCString(threadStateData, buffer);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGetShaderPrecisionFormat___int_int_java_nio_IntBuffer_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT shadertype, JAVA_INT precisiontype, JAVA_OBJECT range, JAVA_OBJECT precision) {
    glGetShaderPrecisionFormat(shadertype, precisiontype, (GLint *) getBufferAddress(range), (GLint *) getBufferAddress(precision));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGetTexParameterfv___int_int_java_nio_FloatBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT pname, JAVA_OBJECT params) {
    glGetTexParameterfv(target, pname, (GLfloat *) getBufferAddress(params));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGetTexParameteriv___int_int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT pname, JAVA_OBJECT params) {
    glGetTexParameteriv(target, pname, (GLint *) getBufferAddress(params));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGetUniformfv___int_int_java_nio_FloatBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT program, JAVA_INT location, JAVA_OBJECT params) {
    glGetUniformfv(program, location, (GLfloat *) getBufferAddress(params));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGetUniformiv___int_int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT program, JAVA_INT location, JAVA_OBJECT params) {
    glGetUniformiv(program, location, (GLint *) getBufferAddress(params));
}

JAVA_INT com_thelogicmaster_switchgdx_SwitchGL_glGetUniformLocation___int_java_lang_String_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT program, JAVA_OBJECT name) {
    return glGetUniformLocation(program, toNativeString(threadStateData, name));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGetVertexAttribfv___int_int_java_nio_FloatBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT index, JAVA_INT pname, JAVA_OBJECT params) {
    glGetVertexAttribfv(index, pname, (GLfloat *) getBufferAddress(params));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGetVertexAttribiv___int_int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT index, JAVA_INT pname, JAVA_OBJECT params) {
    glGetVertexAttribiv(index, pname, (GLint *) getBufferAddress(params));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glGetVertexAttribPointerv___int_int_java_nio_Buffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT index, JAVA_INT pname, JAVA_OBJECT pointer) {
    glGetVertexAttribPointerv(index, pname, (void **) getBufferAddress(pointer));
}

JAVA_BOOLEAN com_thelogicmaster_switchgdx_SwitchGL_glIsBuffer___int_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT buffer) {
    return glIsBuffer(buffer);
}

JAVA_BOOLEAN com_thelogicmaster_switchgdx_SwitchGL_glIsEnabled___int_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT cap) {
    return glIsEnabled(cap);
}

JAVA_BOOLEAN com_thelogicmaster_switchgdx_SwitchGL_glIsFramebuffer___int_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT framebuffer) {
    return glIsFramebuffer(framebuffer);
}

JAVA_BOOLEAN com_thelogicmaster_switchgdx_SwitchGL_glIsProgram___int_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT program) {
    return glIsProgram(program);
}

JAVA_BOOLEAN com_thelogicmaster_switchgdx_SwitchGL_glIsRenderbuffer___int_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT renderbuffer) {
    return glIsRenderbuffer(renderbuffer);
}

JAVA_BOOLEAN com_thelogicmaster_switchgdx_SwitchGL_glIsShader___int_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT shader) {
    return glIsShader(shader);
}

JAVA_BOOLEAN com_thelogicmaster_switchgdx_SwitchGL_glIsTexture___int_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT texture) {
    return glIsTexture(texture);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glLinkProgram___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT program) {
    glLinkProgram(program);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glReleaseShaderCompiler__(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject) {
    glReleaseShaderCompiler();
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glRenderbufferStorage___int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT internalformat, JAVA_INT width, JAVA_INT height) {
    glRenderbufferStorage(target, internalformat, width, height);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glSampleCoverage___float_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_FLOAT value, JAVA_BOOLEAN invert) {
    glSampleCoverage(value, invert);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glShaderBinary___int_java_nio_IntBuffer_int_java_nio_Buffer_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT n, JAVA_OBJECT shaders, JAVA_INT binaryformat, JAVA_OBJECT binary, JAVA_INT length) {
    glShaderBinary(n, (GLuint *) getBufferAddress(shaders), binaryformat, (void *) getBufferAddress(binary), length);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glShaderSource___int_java_lang_String(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT shader, JAVA_OBJECT sourceObject) {
    auto source = toNativeString(threadStateData, sourceObject);
    glShaderSource(shader, 1, &source, nullptr);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glStencilFuncSeparate___int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT face, JAVA_INT func, JAVA_INT ref, JAVA_INT mask) {
    glStencilFuncSeparate(face, func, ref, mask);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glStencilMaskSeparate___int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT face, JAVA_INT mask) {
    glStencilMaskSeparate(face, mask);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glStencilOpSeparate___int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT face, JAVA_INT fail, JAVA_INT zfail, JAVA_INT zpass) {
    glStencilOpSeparate(face, fail, zfail, zpass);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glTexParameterfv___int_int_java_nio_FloatBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT pname, JAVA_OBJECT params) {
    glTexParameterfv(target, pname, (GLfloat *) getBufferAddress(params));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glTexParameteri___int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT pname, JAVA_INT param) {
    glTexParameteri(target, pname, param);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glTexParameteriv___int_int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT target, JAVA_INT pname, JAVA_OBJECT params) {
    glTexParameteriv(target, pname, (GLint *) getBufferAddress(params));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform1f___int_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_FLOAT x) {
    glUniform1f(location, x);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform1fv___int_int_java_nio_FloatBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_OBJECT v) {
    glUniform1fv(location, count, (GLfloat *) getBufferAddress(v));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform1fv___int_int_float_1ARRAY_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_OBJECT v, JAVA_INT offset) {
    glUniform1fv(location, count, (GLfloat *) ((JAVA_ARRAY) v)->data + offset);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform1i___int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT x) {
    glUniform1i(location, x);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform1iv___int_int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_OBJECT v) {
    glUniform1iv(location, count, (GLint *) getBufferAddress(v));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform1iv___int_int_int_1ARRAY_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_OBJECT v, JAVA_INT offset) {
    glUniform1iv(location, count, (GLint *) ((JAVA_ARRAY) v)->data + offset);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform2f___int_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_FLOAT x, JAVA_FLOAT y) {
    glUniform2f(location, x, y);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform2fv___int_int_java_nio_FloatBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_OBJECT v) {
    glUniform2fv(location, count, (GLfloat *) getBufferAddress(v));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform2fv___int_int_float_1ARRAY_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_OBJECT v, JAVA_INT offset) {
    glUniform2fv(location, count, (GLfloat *) ((JAVA_ARRAY) v)->data + offset);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform2i___int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT x, JAVA_INT y) {
    glUniform2i(location, x, y);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform2iv___int_int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_OBJECT v) {
    glUniform2iv(location, count, (GLint *) getBufferAddress(v));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform2iv___int_int_int_1ARRAY_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_OBJECT v, JAVA_INT offset) {
    glUniform2iv(location, count, (GLint *) ((JAVA_ARRAY) v)->data + offset);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform3f___int_float_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_FLOAT x, JAVA_FLOAT y, JAVA_FLOAT z) {
    glUniform3f(location, x, y, z);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform3fv___int_int_java_nio_FloatBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_OBJECT v) {
    glUniform3fv(location, count, (GLfloat *) getBufferAddress(v));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform3fv___int_int_float_1ARRAY_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_OBJECT v, JAVA_INT offset) {
    glUniform3fv(location, count, (GLfloat *) ((JAVA_ARRAY) v)->data + offset);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform3i___int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT x, JAVA_INT y, JAVA_INT z) {
    glUniform3i(location, x, y, z);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform3iv___int_int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_OBJECT v) {
    glUniform3iv(location, count, (GLint *) getBufferAddress(v));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform3iv___int_int_int_1ARRAY_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_OBJECT v, JAVA_INT offset) {
    glUniform3iv(location, count, (GLint *) ((JAVA_ARRAY) v)->data + offset);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform4f___int_float_float_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_FLOAT x, JAVA_FLOAT y, JAVA_FLOAT z, JAVA_FLOAT w) {
    glUniform4f(location, x, y, z, w);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform4fv___int_int_java_nio_FloatBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_OBJECT v) {
    glUniform4fv(location, count, (GLfloat *) getBufferAddress(v));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform4fv___int_int_float_1ARRAY_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_OBJECT v, JAVA_INT offset) {
    glUniform4fv(location, count, (GLfloat *) ((JAVA_ARRAY) v)->data + offset);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform4i___int_int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT x, JAVA_INT y, JAVA_INT z, JAVA_INT w) {
    glUniform4i(location, x, y, z, w);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform4iv___int_int_java_nio_IntBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_OBJECT v) {
    glUniform4iv(location, count, (GLint *) getBufferAddress(v));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniform4iv___int_int_int_1ARRAY_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_OBJECT v, JAVA_INT offset) {
    glUniform4iv(location, count, (GLint *) ((JAVA_ARRAY) v)->data + offset);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniformMatrix2fv___int_int_boolean_java_nio_FloatBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_BOOLEAN transpose, JAVA_OBJECT value) {
    glUniformMatrix2fv(location, count, transpose, (GLfloat *) getBufferAddress(value));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniformMatrix2fv___int_int_boolean_float_1ARRAY_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_BOOLEAN transpose, JAVA_OBJECT value, JAVA_INT offset) {
    glUniformMatrix2fv(location, count, transpose, (GLfloat *) ((JAVA_ARRAY) value)->data + offset);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniformMatrix3fv___int_int_boolean_java_nio_FloatBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_BOOLEAN transpose, JAVA_OBJECT value) {
    glUniformMatrix3fv(location, count, transpose, (GLfloat *) getBufferAddress(value));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniformMatrix3fv___int_int_boolean_float_1ARRAY_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_BOOLEAN transpose, JAVA_OBJECT value, JAVA_INT offset) {
    glUniformMatrix3fv(location, count, transpose, (GLfloat *) ((JAVA_ARRAY) value)->data + offset);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniformMatrix4fv___int_int_boolean_java_nio_FloatBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_BOOLEAN transpose, JAVA_OBJECT value) {
    glUniformMatrix4fv(location, count, transpose, (GLfloat *) getBufferAddress(value));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUniformMatrix4fv___int_int_boolean_float_1ARRAY_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT location, JAVA_INT count, JAVA_BOOLEAN transpose, JAVA_OBJECT value, JAVA_INT offset) {
    glUniformMatrix4fv(location, count, transpose, (GLfloat *) ((JAVA_ARRAY) value)->data + offset);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glUseProgram___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT program) {
    glUseProgram(program);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glValidateProgram___int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT program) {
    glValidateProgram(program);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glVertexAttrib1f___int_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT indx, JAVA_FLOAT x) {
    glVertexAttrib1f(indx, x);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glVertexAttrib1fv___int_java_nio_FloatBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT indx, JAVA_OBJECT values) {
    glVertexAttrib1fv(indx, (GLfloat *) getBufferAddress(values));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glVertexAttrib2f___int_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT indx, JAVA_FLOAT x, JAVA_FLOAT y) {
    glVertexAttrib2f(indx, x, y);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glVertexAttrib2fv___int_java_nio_FloatBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT indx, JAVA_OBJECT values) {
    glVertexAttrib2fv(indx, (GLfloat *) getBufferAddress(values));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glVertexAttrib3f___int_float_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT indx, JAVA_FLOAT x, JAVA_FLOAT y, JAVA_FLOAT z) {
    glVertexAttrib3f(indx, x, y, z);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glVertexAttrib3fv___int_java_nio_FloatBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT indx, JAVA_OBJECT values) {
    glVertexAttrib3fv(indx, (GLfloat *) getBufferAddress(values));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glVertexAttrib4f___int_float_float_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT indx, JAVA_FLOAT x, JAVA_FLOAT y, JAVA_FLOAT z, JAVA_FLOAT w) {
    glVertexAttrib4f(indx, x, y, z, w);
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glVertexAttrib4fv___int_java_nio_FloatBuffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT indx, JAVA_OBJECT values) {
    glVertexAttrib4fv(indx, (GLfloat *) getBufferAddress(values));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glVertexAttribPointer___int_int_int_boolean_int_java_nio_Buffer(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT index, JAVA_INT size, JAVA_INT type, JAVA_BOOLEAN normalized, JAVA_INT stride, JAVA_OBJECT ptr) {
    glVertexAttribPointer(index, size, type, normalized, stride, getBufferAddress(ptr));
}

JAVA_VOID com_thelogicmaster_switchgdx_SwitchGL_glVertexAttribPointer___int_int_int_boolean_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT __cn1ThisObject, JAVA_INT index, JAVA_INT size, JAVA_INT type, JAVA_BOOLEAN normalized, JAVA_INT stride, JAVA_INT ptr) {
    glVertexAttribPointer(index, size, type, normalized, stride, (void *) (JAVA_LONG) ptr);
}
}