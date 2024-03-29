
include_directories(
${CHOQOK_INCLUDES}
)

set(choqok_LIB_SRCS
application.cpp
plugin.cpp
shortener.cpp
uploader.cpp
account.cpp
microblog.cpp
pluginmanager.cpp
shortenmanager.cpp
accountmanager.cpp
passwordmanager.cpp
mediamanager.cpp
notifymanager.cpp
choqokuiglobal.cpp
choqokid.cpp
choqoktools.cpp
dbushandler.cpp
ui/microblogwidget.cpp
ui/editaccountwidget.cpp
ui/timelinewidget.cpp
ui/postwidget.cpp
ui/choqoktextedit.cpp
ui/composerwidget.cpp
ui/quickpost.cpp
ui/choqokmainwindow.cpp
ui/uploadmediadialog.cpp
ui/textbrowser.cpp
ui/choqoktabbar.cpp
ui/flickcharm.cpp
)

if(QtIndicate_FOUND)
    set(choqok_LIB_SRCS ${choqok_LIB_SRCS} indicatormanager.cpp)
    include_directories(${QTINDICATE_INCLUDE_DIRS})
    add_definitions(-DQTINDICATE_BUILD)
endif(QtIndicate_FOUND)

qt4_add_dbus_adaptor( choqok_LIB_SRCS org.kde.choqok.xml dbushandler.h Choqok::DbusHandler ChoqokAdaptor ) 

kde4_add_kcfg_files(choqok_LIB_SRCS
choqokbehaviorsettings.kcfgc
choqokappearancesettings.kcfgc
)

kde4_add_ui_files(choqok_LIB_SRCS ui/uploadmedia_base.ui)

kde4_add_library(choqok SHARED ${choqok_LIB_SRCS})

target_link_libraries(choqok ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${KDE4_KUTILS_LIBS})

if(QtIndicate_FOUND)
       add_definitions(-DXDG_APPS_INSTALL_DIR=${XDG_APPS_INSTALL_DIR})
       target_link_libraries(choqok ${QTINDICATE_LIBRARY})
endif(QtIndicate_FOUND)

set_target_properties(choqok PROPERTIES
VERSION 1.3.0
SOVERSION 1
)

if(MSVC)
    set_target_properties(choqok PROPERTIES
    OUTPUT_NAME libchoqok
    )
endif(MSVC)

install( FILES choqokbehaviorsettings.kcfg choqokappearancesettings.kcfg
         DESTINATION ${KCFG_INSTALL_DIR})

install(TARGETS choqok ${INSTALL_TARGETS_DEFAULT_ARGS})
install( FILES choqokplugin.desktop choqokshortenerplugin.desktop
               choqokuploaderplugin.desktop DESTINATION ${SERVICETYPES_INSTALL_DIR})

install( FILES
    ${CMAKE_CURRENT_BINARY_DIR}/choqokbehaviorsettings.h
    ${CMAKE_CURRENT_BINARY_DIR}/choqokappearancesettings.h
    application.h
    account.h
    accountmanager.h
    choqok_export.h
    choqokid.h
    choqoktypes.h
    choqokuiglobal.h
    mediamanager.h
    microblog.h
    notifymanager.h
    passwordmanager.h
    plugin.h
    pluginmanager.h
    shortener.h
    uploader.h
    shortenmanager.h
    dbushandler.h
    choqoktools.h
    ui/choqoktextedit.h
    ui/composerwidget.h
    ui/editaccountwidget.h
    ui/choqokmainwindow.h
    ui/microblogwidget.h
    ui/postwidget.h
    ui/quickpost.h
    ui/timelinewidget.h
    ui/uploadmediadialog.h
    ui/textbrowser.h
    ui/choqoktabbar.h
DESTINATION ${INCLUDE_INSTALL_DIR}/choqok COMPONENT Devel)
