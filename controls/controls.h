#ifndef CONTROLS_H
#define CONTROLS_H

#include "core/control.h"
#include "imagecontrol.h"
#include "videocontrol.h"
#include "strokecontrol.h"
#ifdef SHOWBOARD_QUICK
#else
#include "webcontrol.h"
#endif
#include "pptxcontrol.h"
#include "docxcontrol.h"
#include "textcontrol.h"
#include "audiocontrol.h"
#include "textinputcontrol.h"
#include "graphvizcontrol.h"

#include <qexport.h>

REGISTER_CONTROL(ImageControl, "image,bmp,gif,jpg,jpeg,png,svg")

REGISTER_CONTROL(VideoControl, "video,mp4,wmv,webm,ts,flv,m3u8,asf,avi,"
                                "rtsp,rtmp,rtp")
REGISTER_CONTROL(AudioControl, "audio,mp3,wma,wav,m4a,")
#ifdef QT_DEBUG
REGISTER_CONTROL(StrokeControl, "glstroke")
#endif
#ifdef SHOWBOARD_QUICK
#else
REGISTER_CONTROL(WebControl, "htm,html,http,https,chrome,swf")
#endif
REGISTER_CONTROL(TextControl, "text,txt,js,cpp,h,qss,css")
REGISTER_CONTROL(TextInputControl, "textinput")
REGISTER_CONTROL(GraphvizControl, "graphviz,dot")

#ifdef WIN32
REGISTER_CONTROL(PptxControl, "ppt,pptx")
# ifdef QT_DEBUG
REGISTER_CONTROL(DocxControl, "doc,docx")
# endif
#endif

#endif // CONTROLS_H
