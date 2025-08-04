#include <QApplication>
#include <QWidget>

#if defined(Q_OS_WIN)
#include <windows.h>
#endif

// Define necessary structures and enums for the blur effect on Windows.
// These are typically not in the public headers.
enum ACCENT_STATE {
    ACCENT_DISABLED = 0,
    ACCENT_ENABLE_GRADIENT = 1,
    ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,
    ACCENT_ENABLE_BLURBEHIND = 3,
    ACCENT_ENABLE_ACRYLICBLURBEHIND = 4,
    ACCENT_INVALID_STATE = 5
};

struct ACCENT_POLICY {
    ACCENT_STATE AccentState;
    DWORD AccentFlags;
    DWORD GradientColor;
    DWORD AnimationId;
};

enum WINDOWCOMPOSITIONATTRIB {
    WCA_ACCENT_POLICY = 19
};

struct WINDOWCOMPOSITIONATTRIBDATA {
    WINDOWCOMPOSITIONATTRIB Attrib;
    PVOID pvData;
    SIZE_T cbData;
};

// Function pointer for SetWindowCompositionAttribute
typedef BOOL(WINAPI*pSetWindowCompositionAttribute)(HWND, WINDOWCOMPOSITIONATTRIBDATA*);

void setBlurEffect(QWidget *window) {
#if defined(Q_OS_WIN)
    HMODULE hUser32 = GetModuleHandle(L"user32.dll");
    if (hUser32) {
        pSetWindowCompositionAttribute setWindowCompositionAttribute = (pSetWindowCompositionAttribute)GetProcAddress(hUser32, "SetWindowCompositionAttribute");
        if (setWindowCompositionAttribute) {
            // The color format for the tint is AABBGGRR (Alpha, Blue, Green, Red).
            // 0x00000000 is fully transparent. For a 50% black tint, you could use 0x7F000000.
            ACCENT_POLICY accent = { ACCENT_ENABLE_ACRYLICBLURBEHIND, 0, 0x00000000, 0 };
            WINDOWCOMPOSITIONATTRIBDATA data;
            data.Attrib = WCA_ACCENT_POLICY;
            data.pvData = &accent;
            data.cbData = sizeof(accent);
            setWindowCompositionAttribute((HWND)window->winId(), &data);
        }
    }
#endif
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;
    window.setWindowIcon(QIcon(":/res/Quiet.png"));
    window.setWindowOpacity(0.97); // Slight opacity
    window.setStyleSheet("background-color: transparent;"); // Make background transparent
    window.resize(1338, 752);

#if defined(Q_OS_WIN)
    window.setAttribute(Qt::WA_TranslucentBackground);
#endif

    window.show();

    setBlurEffect(&window);

    return app.exec();
}
